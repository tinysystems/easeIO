#include <stdio.h>
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "PF_sim.h"
#include "DSPLib.h"
#include "conv1.h"
/*EASEIO Libs*/
#include "EASEIO.h"
#include <libalpaca/alpaca.h>
#include <libmsp/watchdog.h>

#define TEST_SIGNAL


#define MEM_SIZE 0x4
__nv uint8_t *data_src[MEM_SIZE];
__nv uint8_t *data_dest[MEM_SIZE];
__nv unsigned int data_size[MEM_SIZE];
/**global_variables*/

void clear_isDirty() {}
int DMA_copy(unsigned int from, unsigned int to, unsigned short size);

/*
 * IO Tasks
 */
void init();
void task_dma();

TASK(1,  task_dma)

__nv  uint64_t exe_number = 0;

/*TEST Vars */
__nv  uint64_t PF_number = 0;
__nv  uint64_t Re_exe_number = 0;


#define ARR_SIZE 3000
__nv int dma_data_src[ARR_SIZE] = {[0 ... ARR_SIZE - 1] = 1};
__nv int dma_data_dst[ARR_SIZE] = {[0 ... ARR_SIZE - 1] = 2};


void task_dma()
{
        while (exe_number<1000) {

            call_IO("Single", DMA_copy(&dma_data_dst[0], &dma_data_src[0], ARR_SIZE));

            for(int volatile i =0 ; i<300 ;i++){
                dma_data_src[i] = exe_number;

            }

            exe_number++;
            TRANSITION_TO(task_dma);
        }
        while(1);
}

static void init_hw()
{
  //  P3DIR = 0xFF;
    msp_watchdog_disable();
  //  PM5CTL0 &= ~LOCKLPM5;
}

void init()
{

    init_hw();
    __enable_interrupt();

}

int DMA_copy(unsigned int from, unsigned int to, unsigned short size)
{
    Re_exe_number++;
//    __data20_write_long((uintptr_t) &DMA0SA,(uintptr_t) from);
                                            // Source block address
//    __data20_write_long((uintptr_t) &DMA0DA,(uintptr_t) to);
                                              // Destination single address
//    DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
//    DMA0SZ = size;                          // Block size
//    DMA0CTL |= DMAEN + DMAREQ ;                         // Enable DMA0 + Trigger block transfer

}


ENTRY_TASK(task_dma)
INIT_FUNC(init)
