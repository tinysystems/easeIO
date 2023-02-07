#include <stdio.h>
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <libalpaca/alpaca.h>
#include <libmsp/watchdog.h>
#include "EASEIO.h"
#include "libPF/PF_sim.h"
#include "DSPLib.h"
#include "msp430.h"
#include <math.h>
#include "libmsp/mem.h"
#include "inputs/conv2.h"


#define MEM_SIZE 0x4
__nv uint8_t *data_src[MEM_SIZE];
__nv uint8_t *data_dest[MEM_SIZE];
__nv unsigned int data_size[MEM_SIZE];

/**global_variables*/

void clear_isDirty() {}

/*---APP VARS----*/

/* Input signal parameters */
#define FS                  8192
#define SIGNAL_LENGTH       256
#define SIGNAL_FREQUENCY1   200
#define SIGNAL_AMPLITUDE1   0.6
#define SIGNAL_FREQUENCY2   2100
#define SIGNAL_AMPLITUDE2   0.15
#define __MSP430_HAS_PMM__
/* Constants */
#define PI                  3.1415926536

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

/* Filter parameters */
#define FIR_LENGTH      64
#define COEFF_LENTH     sizeof(FILTER_COEFFS_EX1)/sizeof(FILTER_COEFFS_EX1[0])

/*
 * Circular buffer of size 2*FIR_LENGTH, aligned to 4*FIR_LENGTH in order to
 * use the circular buffer feature.
 */
DSPLIB_DATA(circularBuffer,MSP_ALIGN_FIR_Q15(FIR_LENGTH))
_q15 circularBuffer[2*FIR_LENGTH];

/* Filter coefficients */
DSPLIB_DATA(filterCoeffs,4)
_q15 filterCoeffs[COEFF_LENTH];

/* Generated input signal */
DSPLIB_DATA(input_lea,4)
_q15 input_lea[SIGNAL_LENGTH];

/* Temporary data array for processing */
DSPLIB_DATA(temp,4)
_q15 temp[SIGNAL_LENGTH];

/* Filter result */
DSPLIB_DATA(result,4)
_q15 result[SIGNAL_LENGTH];

__nv _q15 signalBuffer[SIGNAL_LENGTH];
__nv _q15 signalBuffer_output[SIGNAL_LENGTH];
/* Benchmark cycle counts */
volatile uint32_t cycleCount = 0;

/*
 * IO Tasks
 */
void init();
void task_init();
void task_signal();
void task_filter();
void task_done();

TASK(1,  task_init)
TASK(2,  task_signal)
TASK(3,  task_filter)
TASK(4,  task_done)



/*TEST Variables */
__nv  uint64_t exe_number = 0;
__nv  uint64_t PF_number = 0;
__nv  uint64_t Re_exe_number = 0;
__nv  uint64_t correctExecution = 0;
__nv  uint64_t incorrectExecution = 0;


#define ARR_SIZE 3000
__nv int dma_data_src[ARR_SIZE] = {[0 ... ARR_SIZE - 1] = 1};
__nv int dma_data_dst[ARR_SIZE] = {[0 ... ARR_SIZE - 1] = 2};


void task_init()
{

    exe_number++;

    TRANSITION_TO(task_signal);
}

void task_signal()
{
    EASEIO_DMA_copy((uint32_t)(&conv2_wm), (uint32_t)(&signalBuffer) , SIGNAL_LENGTH);

    TRANSITION_TO(task_filter);
}


void task_filter()
{
    uint16_t samples;
    uint16_t copyindex;
    uint16_t filterIndex;
    msp_status status;
    msp_fir_q15_params firParams;
    msp_fill_q15_params fillParams;
    msp_copy_q15_params copyParams;

   EASEIO_DMA_copy((uint32_t)(&signalBuffer),(uint32_t)(&input_lea), SIGNAL_LENGTH);

   EASEIO_DMA_copy((uint32_t)(&FILTER_COEFFS_EX1), (uint32_t)(&filterCoeffs), sizeof(filterCoeffs));


   fillParams.length = FIR_LENGTH*2;
   fillParams.value = 0;
   status = msp_fill_q15(&fillParams, circularBuffer);
   msp_checkStatus(status);


   copyParams.length = FIR_LENGTH;


   firParams.length = FIR_LENGTH;
   firParams.tapLength = COEFF_LENTH;
   firParams.coeffs = filterCoeffs;
   firParams.enableCircularBuffer = true;


   samples = 0;
   copyindex = 0;
   filterIndex = 2*FIR_LENGTH - COEFF_LENTH;


   while (samples < SIGNAL_LENGTH) {


       status = call_IO("Always", msp_copy_q15(&copyParams, &input_lea[samples], &circularBuffer[copyindex]));
       status = call_IO("Always", msp_fir_q15(&firParams, &circularBuffer[filterIndex], &result[samples]));

       copyindex ^= FIR_LENGTH;
       filterIndex ^= FIR_LENGTH;
       samples += FIR_LENGTH;
  }
   EASEIO_DMA_copy( (uint32_t)(&result),(uint32_t)(&signalBuffer), SIGNAL_LENGTH);

    TRANSITION_TO(task_done);
}


void task_done()
{

    while(exe_number<1000){
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

ENTRY_TASK(task_init)
INIT_FUNC(init)
