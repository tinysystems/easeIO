#include <EASEIO.h>
#include <stdio.h>
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <libalpaca/alpaca.h>
#include <libmsp/watchdog.h>
#include "libPF/PF_sim.h"
#include "DSPLib.h"
#include "msp430.h"
#include "libmsp/mem.h"
#include "inputs/dnnHeaders.h"
//#define TEST_SIGNAL


#define MEM_SIZE 0x4
__nv uint8_t *data_src[MEM_SIZE];
__nv uint8_t *data_dest[MEM_SIZE];
__nv unsigned int data_size[MEM_SIZE];

__nv bool op_TS[2];

__nv bool flag[6];

__nv int temperature_priv;__nv volatile int humidity_priv;
__nv int filter_priv;
__nv int filters_priv;
__nv msp_status status_priv;
__nv int relu_divider_priv;
__nv int relu_counter_priv;
__nv int fc_parse_priv;
__nv int fc_parses_priv;
__nv int fc_part_priv;
__nv uint64_t exe_number_priv;

void Clean_flags(){  flag[0] = FALSE;flag[1] = FALSE;flag[2] = FALSE;flag[3] = FALSE;flag[4] = FALSE;flag[5] = FALSE; }


void clear_isDirty() {}


/* DNN variables  */
#define CONFIG_LAYER_BUF_SIZE 0x3000
#define IMAGE_LENGTH 784 // 28x28
__nv int filters = 2;
__nv int filter=0;
__nv int layers = 2;
__nv int layer=0;
__nv int fc_parses = 10;
__nv int fc_parse=0;
__nv int fc_part=0;
__hifram _q15 layer_buffers[3][CONFIG_LAYER_BUF_SIZE];
__nv _q15 temp;
__nv _q15* tempBuffer;
__nv _q15* inputBuffer;
__nv _q15* outputBuffer;
__nv int relu_divider=0;
__nv int relu_counter =4;
__nv volatile int temperature, humidity;

/* Define example coefficients if no DSPLib GUI header is provided. */
#ifndef FILTER_COEFFS_EX1
/* 15th-order low pass filter coefficients (Fs=8192, Fc=1200) */
const _q15 FILTER_COEFFS_EX1[16] = {
    _Q15(+0.001962), _Q15(-0.001728), _Q15(-0.012558), _Q15(-0.023557),
    _Q15(-0.004239), _Q15(+0.072656), _Q15(+0.189060), _Q15(+0.278404),
    _Q15(+0.278404), _Q15(+0.189060), _Q15(+0.072656), _Q15(-0.004239),
    _Q15(-0.023557), _Q15(-0.012558), _Q15(-0.001728), _Q15(+0.001962)
};
#endif


#define COEFF_LENTH     16//sizeof(FILTER_COEFFS_EX1)/sizeof(FILTER_COEFFS_EX1[0])

/*
 * Circular buffer of size 2*FIR_LENGTH, aligned to 4*FIR_LENGTH in order to
 * use the circular buffer feature.
 */
DSPLIB_DATA(biasBuffer,4)
_q15 biasBuffer[IMAGE_LENGTH/2];

/* Filter coefficients */
DSPLIB_DATA(filterCoeffs,4)
_q15 filterCoeffs[COEFF_LENTH];

/* Generated input signal */
DSPLIB_DATA(input_lea,4)
_q15 input_lea[IMAGE_LENGTH/2];

/* Filter result */
DSPLIB_DATA(result,4)
_q15 result[IMAGE_LENGTH/2];

msp_status status;
int capture();
bool GetTime();
/*
 * IO Tasks
 */
void init();
void task_init();
void task_sense();
void task_dnn_init();
void task_convol();
void task_convol_mul();
void task_relu();
void task_relu_div();
void task_fc();
void task_fc_mul();
void task_inference();
void task_send();
TASK(1,  task_init)
TASK(2,  task_sense)
TASK(3,  task_dnn_init)
TASK(4,  task_convol)
TASK(5,  task_convol_mul)
TASK(6,  task_relu)
TASK(7,  task_relu_div)
TASK(8,  task_fc)
TASK(9,  task_fc_mul)
TASK(10,  task_inference)
TASK(11,  task_send)

/* TEST Vars */
__nv  uint64_t exe_number = 0;
__nv  uint64_t PF_number = 0;
__nv  uint64_t Re_exe_number = 0;
__nv  uint64_t correctExecution = 0;
__nv  uint64_t incorrectExecution = 0;
__nv  uint64_t DMANumber = 0;
__nv  uint64_t ExculdeNumber = 0;
__nv  uint64_t pfSet = 0;


void task_init()
{

    TRANSITION_TO(task_sense);
}

void task_sense()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	temperature_priv = temperature;
	humidity_priv = humidity; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	temperature = temperature_priv;
	humidity = humidity_priv;
	}
	 
   
	if(!flag[0]) { 
    	capture();
    	 flag[0] = SET;
    	}
   

    	if(!flag[1]) { 

		if(!flag[2] && (GetTime() - op_TS[0]) < 10000) {
		 temperature = msp_sample_temperature();
		 op_TS[0] = GetTime();
		 temperature_priv = temperature;
		 flag[2] = SET;
		}
		 else { 
		 temperature = temperature_priv;
		 }       

        	humidity = msp_sample_temperature();
        	   

    	flag[1] = SET;
    	}
    TRANSITION_TO(task_dnn_init);
}

void task_dnn_init()
{

    inputBuffer = &layer_buffers[0];
    outputBuffer = &layer_buffers[1];
    tempBuffer = &layer_buffers[2];

    EASEIO_DMA_copy((uint32_t)(&input), (uint32_t)(inputBuffer) , IMAGE_LENGTH);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
    TRANSITION_TO(task_convol);
}

void task_convol()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	filter_priv = filter;
	filters_priv = filters; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	filter = filter_priv;
	filters = filters_priv;
	}
	 

    /* set the filter coff. and order. if all filters are done goto relu */
    if(filter < filters){
        filter++;
        TRANSITION_TO(task_convol_mul);
    }

    filter = 0;
    TRANSITION_TO(task_relu_div);
}

void task_convol_mul()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	filter_priv = filter;
	status_priv = status; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	filter = filter_priv;
	status = status_priv;
	}
	 

    msp_fir_q15_params firParams;
    msp_fill_q15_params fillParams;
    msp_copy_q15_params copyParams;

   

    	if(!flag[3]) { 
       EASEIO_DMA_copy((uint32_t)(inputBuffer+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
       EASEIO_DMA_copy( (uint32_t) &FILTER_COEFFS_EX1, (uint32_t) &filterCoeffs, sizeof(filterCoeffs));

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
       firParams.length = IMAGE_LENGTH;
       firParams.tapLength = COEFF_LENTH;
       firParams.coeffs = filterCoeffs;
       firParams.enableCircularBuffer = false;

      

       	humidity = msp_sample_temperature();
       	       msp_checkStatus(status);

       EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (tempBuffer+ (filter-1)*(IMAGE_LENGTH/2)), IMAGE_LENGTH/2);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
   

    	flag[3] = SET;
    	}

   

    	if(!flag[4]) { 
       msp_matrix_add_q15_params addParams;

       EASEIO_DMA_copy((uint32_t)(tempBuffer+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
       EASEIO_DMA_copy((uint32_t)(&conv2_wm+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &biasBuffer, IMAGE_LENGTH/2); 
       	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
       	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
       	} 
       	 else {}
       	 // used conv2_mv as bias

       addParams.cols = IMAGE_LENGTH/2;
       addParams.rows = 1;
      

       	humidity = msp_sample_temperature();
       	       msp_checkStatus(status);

       EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (outputBuffer+ (filter-1)*(IMAGE_LENGTH/2)), IMAGE_LENGTH/2);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
   

    	flag[4] = SET;
    	}
    TRANSITION_TO(task_convol);
}


void task_relu_div()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	relu_divider_priv = relu_divider;
	relu_counter_priv = relu_counter; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	relu_divider = relu_divider_priv;
	relu_counter = relu_counter_priv;
	}
	 

    if(relu_divider < relu_counter){
        relu_divider++;
        TRANSITION_TO(task_relu);
    }
    relu_divider=0;
    TRANSITION_TO(task_fc);

}

void task_relu()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	relu_divider_priv = relu_divider; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	relu_divider = relu_divider_priv;
	}
	 

    for( int jj = 0; jj < IMAGE_LENGTH/4; jj++) {

        _q15 max = outputBuffer[jj + (relu_divider - 1)*(IMAGE_LENGTH/4)];
        outputBuffer[jj] = (F_LT(max, _Q15(0.0))) ? _Q15(0.0) : max;

    }

    TRANSITION_TO(task_relu_div);

}

void task_fc()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	fc_parse_priv = fc_parse;
	fc_parses_priv = fc_parses;
	fc_part_priv = fc_part; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	fc_parse = fc_parse_priv;
	fc_parses = fc_parses_priv;
	fc_part = fc_part_priv;
	}
	 

    if(fc_parse < fc_parses){

        fc_part++;

        TRANSITION_TO(task_fc_mul);
    }
    fc_parse = 0;
    TRANSITION_TO(task_inference);
}

void task_fc_mul()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	fc_part_priv = fc_part;
	fc_parse_priv = fc_parse;
	status_priv = status; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	fc_part = fc_part_priv;
	fc_parse = fc_parse_priv;
	status = status_priv;
	}
	 

    msp_matrix_mpy_q15_params mpyParams;

    mpyParams.srcACols = IMAGE_LENGTH/2;
    mpyParams.srcARows = 1;
    mpyParams.srcBCols = 1;
    mpyParams.srcBRows = IMAGE_LENGTH/2;

    EASEIO_DMA_copy((uint32_t)(outputBuffer + (fc_part-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
    EASEIO_DMA_copy((uint32_t)(&fc2_w + (fc_parse)*IMAGE_LENGTH + (fc_part-1)*(IMAGE_LENGTH/2)), (uint32_t) &biasBuffer, IMAGE_LENGTH/2); 
    	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
    	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
    	} 
    	 else {}
    	 // used conv2_mv as bias

   

    	humidity = msp_sample_temperature();
    	
    msp_checkStatus(status);



    if(fc_part < 1){
      EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (temp), 1);

	if(!DMA_Data.DMA_Privatization[DMACounter-1]){ 
	DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	} 
	 else {}
	 
    }else{
        inputBuffer[fc_parse] = result[0] + temp;
        fc_part = 0;
        fc_parse++;
    }
    TRANSITION_TO(task_fc);
}


void task_inference()
{

    TRANSITION_TO(task_send);
}

void task_send()
{
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	exe_number_priv = exe_number; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	exe_number = exe_number_priv;
	}
	 

    for(int volatile j =0; j<1000; j++){

     }

    while(exe_number<100){
   TRANSITION_TO(task_init);
    }
    while(1);
}
static void init_hw()
{
    //P3DIR = 0xFF;
    msp_watchdog_disable();
    //PM5CTL0 &= ~LOCKLPM5;
}

void init()
{

    init_hw();

    __enable_interrupt();

}

int capture() {

    for(int volatile j =0; j<1000; j++){

    }
    return 0;
}

bool GetTime()
{

    return false;
}


ENTRY_TASK(task_init)
INIT_FUNC(init)
