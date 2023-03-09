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

/**global_variables*/


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
    call_IO("Single", capture());

    IO_Block_begin("Single");
	call_IO("Timely", 10000, temperature, msp_sample_temperature());
        call_IO("Always", humidity, msp_sample_temperature());
    IO_Block_end();

    TRANSITION_TO(task_dnn_init);
}

void task_dnn_init()
{

    inputBuffer = &layer_buffers[0];
    outputBuffer = &layer_buffers[1];
    tempBuffer = &layer_buffers[2];

    EASEIO_DMA_copy((uint32_t)(&input), (uint32_t)(inputBuffer) , IMAGE_LENGTH);

    TRANSITION_TO(task_convol);
}

void task_convol()
{

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

    msp_fir_q15_params firParams;
    msp_fill_q15_params fillParams;
    msp_copy_q15_params copyParams;

    IO_Block_begin("Single");

       EASEIO_DMA_copy((uint32_t)(inputBuffer+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

       EASEIO_DMA_copy( (uint32_t) &FILTER_COEFFS_EX1, (uint32_t) &filterCoeffs, sizeof(filterCoeffs));

       firParams.length = IMAGE_LENGTH;
       firParams.tapLength = COEFF_LENTH;
       firParams.coeffs = filterCoeffs;
       firParams.enableCircularBuffer = false;

       call_IO("Always", status, msp_fir_q15(&firParams, &input_lea, &result));
       msp_checkStatus(status);

       EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (tempBuffer+ (filter-1)*(IMAGE_LENGTH/2)), IMAGE_LENGTH/2);

    IO_Block_end();


    IO_Block_begin("Single");

       msp_matrix_add_q15_params addParams;

       EASEIO_DMA_copy((uint32_t)(tempBuffer+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

       EASEIO_DMA_copy((uint32_t)(&conv2_wm+ (filter-1)*(IMAGE_LENGTH/2)), (uint32_t) &biasBuffer, IMAGE_LENGTH/2); // used conv2_mv as bias

       addParams.cols = IMAGE_LENGTH/2;
       addParams.rows = 1;
       call_IO("Always", status, msp_matrix_add_q15(&addParams, &input_lea, &biasBuffer, &result));
       msp_checkStatus(status);

       EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (outputBuffer+ (filter-1)*(IMAGE_LENGTH/2)), IMAGE_LENGTH/2);

    IO_Block_end();

    TRANSITION_TO(task_convol);
}


void task_relu_div()
{

    if(relu_divider < relu_counter){
        relu_divider++;
        TRANSITION_TO(task_relu);
    }
    relu_divider=0;
    TRANSITION_TO(task_fc);

}

void task_relu()
{

    for( int jj = 0; jj < IMAGE_LENGTH/4; jj++) {

        _q15 max = outputBuffer[jj + (relu_divider - 1)*(IMAGE_LENGTH/4)];
        outputBuffer[jj] = (F_LT(max, _Q15(0.0))) ? _Q15(0.0) : max;

    }

    TRANSITION_TO(task_relu_div);

}

void task_fc()
{

    if(fc_parse < fc_parses){

        fc_part++;

        TRANSITION_TO(task_fc_mul);
    }
    fc_parse = 0;
    TRANSITION_TO(task_inference);
}

void task_fc_mul()
{

    msp_matrix_mpy_q15_params mpyParams;

    mpyParams.srcACols = IMAGE_LENGTH/2;
    mpyParams.srcARows = 1;
    mpyParams.srcBCols = 1;
    mpyParams.srcBRows = IMAGE_LENGTH/2;

    EASEIO_DMA_copy((uint32_t)(outputBuffer + (fc_part-1)*(IMAGE_LENGTH/2)), (uint32_t) &input_lea, IMAGE_LENGTH/2);

    EASEIO_DMA_copy((uint32_t)(&fc2_w + (fc_parse)*IMAGE_LENGTH + (fc_part-1)*(IMAGE_LENGTH/2)), (uint32_t) &biasBuffer, IMAGE_LENGTH/2); // used conv2_mv as bias

    call_IO("Always", status, msp_matrix_mpy_q15(&mpyParams, &input_lea, &biasBuffer, &result));

    msp_checkStatus(status);



    if(fc_part < 1){
      EASEIO_DMA_copy( (uint32_t) &result,(uint32_t) (temp), 1);

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
