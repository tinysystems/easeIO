#include <stdio.h>
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "libPF/PF_sim.h"
#include "DSPLib.h"
#include "inputs/conv1.h"
/*EASEIO Libs*/
#include "libEaseIO/EASEIO.h"
#include <libalpaca/alpaca.h>
#include <libmsp/watchdog.h>

//#define INTERMITTENT  uncomment to run intermittently

#define MEM_SIZE 0x4
__nv uint8_t *data_src[MEM_SIZE];
__nv uint8_t *data_dest[MEM_SIZE];
__nv unsigned int data_size[MEM_SIZE];
__nv bool op_TS[2];

__nv bool flag[2];

__nv uint64_t sample_priv;
__nv volatile uint16_t avg_temp_priv;
__nv int expire_count_priv;
__nv int [30] expiration_array_priv;


void clear_isDirty() {}

void task_temp();

TASK(1,  task_temp)


/*APP vars*/
__nv volatile uint16_t avg_temp = 0;
__nv  uint64_t sample = 0;

/*TEST Variables */
__nv  uint64_t PF_number = 0;
__nv  uint64_t Re_exe_number = 0;
__nv int expire_count =0;
__nv int expiration_array [30] = {1, 0, 1, 0, 0, 1, 0, 0, 1, 0,
                                  1, 0, 0, 0, 1, 0, 0, 1, 0, 1,
                                  0, 1, 0, 1, 0, 0, 1, 0, 0, 1};

#define EXPIRE_TIME 100000
uint32_t GetTime();


void task_temp()
{
#
	if(!DMA_Data.DMA_Privatization[DMACounter-1])
	{
	
	sample_priv = sample;
	avg_temp_priv = avg_temp; 
	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
	}
	 else {
	
	sample = sample_priv;
	avg_temp = avg_temp_priv;
	}
	 ifdef INTERMITTENT
     P1OUT = 0x01;
#endif
    int temp;

    while(sample < 1000){

       

        	if(!flag[0] && (GetTime() - op_TS[0]) < 10000) {
        	 temp = msp_sample_temperature();
        	 op_TS[0] = GetTime();
        	 temp_priv = temp;
        	 flag[0] = SET;
        	}
        	 else { 
        	 temp = temp_priv;
        	 }
        avg_temp = avg_temp*sample + temp;
        sample ++;
        avg_temp /= sample;
        TRANSITION_TO(task_temp);
    }
#ifdef INTERMITTENT
     P1OUT = 0x02;
#endif
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
#ifdef INTERMITTENT
    PF_sim_start();
#endif
    __enable_interrupt();

}

ENTRY_TASK(task_temp)
INIT_FUNC(init)


uint32_t GetTime()
{
 
    	if(!DMA_Data.DMA_Privatization[DMACounter-1])
    	{
    	
    	expire_count_priv = expire_count;
    	expiration_array_priv = expiration_array; 
    	 DMA_Data.DMA_Privatization[DMACounter-1] = COMPLETED;
    	}
    	 else {
    	
    	expire_count = expire_count_priv;
    	expiration_array = expiration_array_priv;
    	}
    	    if (expire_count == 30)
        expire_count = 0;
    expire_count++;
    return expiration_array[expire_count];
}
