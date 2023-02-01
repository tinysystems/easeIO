/*
 * libPF.c
 *
 *  Created on: Jun 15, 2022
 *      Author: erenyildiz
 */


#include <msp430.h>
#include "libmsp/mem.h"
#include <stdlib.h>
#include <stdint.h>
/**
 * main.c
 */
#define PF_SIMULATION
#ifdef PF_SIMULATION
__nv int timer_count = 500;
__nv int timer_array[30] = {750, 900, 800, 980, 1020, 670, 830, 1050, 1024, 920,
                              1058, 720, 930, 855, 1087, 687, 596, 800, 400, 550,
                              690, 410, 615, 310, 796, 600, 409, 381, 636, 583};
/*__nv int timer_array[30] = {450, 600, 500, 480, 620, 570, 630, 450, 1024, 320,
                              658, 420, 630, 555, 587, 487, 496, 500, 400, 350,
                              390, 310, 615, 210, 596, 400, 409, 381, 636, 283};*/
extern  uint64_t PF_number;
__nv int count_t = 0;
void Reset() {
//   PF_number++;
    PMMCTL0 = 0x0008;
}
#endif




static int Timer_A0_set(){

    TA0CCR0 = timer_count;//max 65535
    TA0CTL = TASSEL__ACLK + MC_1;  //set the max period for 16bit timer operation
    TA0CCTL0 = CCIE;  //enable compare reg 0
    _BIS_SR( GIE); //ENABLE GLOBAL INTERRRUPTS

}
volatile int *a;

void PF_sim_start()
{
    Timer_A0_set();
}

// Timer A0 interrupt service routine
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
{
    //PF_number++;
    if (count_t == 30)
      count_t = 0;
    timer_count = timer_array[count_t]*2;
    count_t++;

//    P3OUT ^= 0x02;
//    P3OUT ^= 0x02;
    Reset();

}


