
#include "DMA.h"
#include <msp430.h>
__nv DMA_Pramas DMA_Data = {.DMA_CheckLock[0 ... MAX_DMA_NUM-1] = 0, .DMA_Control[0 ... MAX_DMA_NUM-1] = 0, .DMA_Privatization[0 ... MAX_DMA_NUM-1] = false};
__nv uint8_t privatizationBuffer [MAX_PRIV_BUFFER];
uint64_t privatizationBufferPoint = 0;

uint8_t DMACounter = 1; // it should be start 1 to take private copies in region 0
extern uint64_t Re_exe_number;
extern uint64_t DMANumber;
bool CheckNVM(uint32_t startAdr, uint32_t size){

    //if (((startAdr >= FRAM_START)&((startAdr + size) <= FRAM_END))||((startAdr >= HIFRAM_START)&((startAdr + size)  <= HIFRAM_END)))
    if (startAdr >= FRAM_START)
        return true;
    else
        return  false;
}


void DMAControl(){

     //This function labels DMA functions whether there is WAR or not


        if(!CheckNVM(DMA0SA,DMA0SZ)){ // If source is volatile
            if(!CheckNVM(DMA0DA,DMA0SZ)){ // If dest is volatile
                DMA_Data.DMA_Control[DMACounter] = ALWAYS; // @annotated as @Always
            }else{ // If dest is non-volatile
                DMA_Data.DMA_Control[DMACounter] = SINGLE; // @annotated as @Single
            }
        }else{// If source is non-volatile
            if(!CheckNVM(DMA0DA,DMA0SZ)){// If dest is volatile
                DMA_Data.DMA_Control[DMACounter] = PRIVATE; // @annotated as @Always via priv_buffer
            }else{// If dest is non-volatile
                DMA_Data.DMA_Control[DMACounter] = SINGLE; // @annotated as @Single
            }
        }
    DMA_Data.DMA_CheckLock[DMACounter] = SET;
}

void EASEIO_DMA_copy(uint32_t from, uint32_t to, uint16_t size)
{
    //DMANumber++;
    //P3OUT ^=0x01;
    //P3OUT ^=0x01;
    //Re_exe_number++;
    __data16_write_addr((unsigned short)(&DMA0SA), from); // Source block address
    __data16_write_addr((unsigned short)(&DMA0DA), to);  // Destination single address
    DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;            // Rpt, inc
    DMA0SZ = size ;                                             // Block size

    // Compiler Should do following transformation //
    if(!(DMA_Data.DMA_CheckLock[DMACounter])){
        DMAControl();
    }
    if((DMA_Data.DMA_Control[DMACounter] == ALWAYS)){
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
    }else if(!(DMA_Data.DMA_Privatization[DMACounter])&(DMA_Data.DMA_Control[DMACounter]  == SINGLE)){//and if DMA_private_copyflage is not set
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
    }else if (DMA_Data.DMA_Control[DMACounter]  == PRIVATE){
        privatizationBufferPoint = 0;
        for(int j = 0; j<DMACounter; j++){
            privatizationBufferPoint = privatizationBufferPoint + DMA_Data.privatizationBufferCounter[j];
        }
        DMA_Data.privatizationBufferCounter[DMACounter] = size;
        if(!(DMA_Data.DMA_Privatization[DMACounter])){
            //__data16_write_addr((unsigned short)(&DMA0SA), from); // Source block address
            __data16_write_addr((unsigned short)(&DMA0DA), &privatizationBuffer[2*privatizationBufferPoint]);  // Destination single address
            //DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;                // Rpt, inc
            //DMA0SZ = size;           // Block size
            DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
            DMA_Data.DMA_Privatization[DMACounter] = COMPLETED;
        }
        __data16_write_addr((unsigned short)(&DMA0SA), &privatizationBuffer[2*privatizationBufferPoint]); // Source block address
        __data16_write_addr((unsigned short)(&DMA0DA), to);  // Destination single address
        DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;            // Rpt, inc
        //DMA0SZ = size ;
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer

    }
    DMACounter++;
}

/*
void EASEIO_DMA_copy(unsigned int from, unsigned int to, unsigned short size)
{
//    P3OUT ^=0x01;
//    P3OUT ^=0x01;
    Re_exe_number++;
    __data20_write_long((uintptr_t) &DMA0SA,(uintptr_t) from);
                                              // Source block address
      __data20_write_long((uintptr_t) &DMA0DA,(uintptr_t) to);
    DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;            // Rpt, inc
    DMA0SZ = size ;                                             // Block size

    // Compiler Should do following transformation //
    if(!(DMA_Data.DMA_CheckLock[DMACounter])){
        DMAControl();
    }
    if((DMA_Data.DMA_Control[DMACounter] == ALWAYS)){
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
    }else if(!(DMA_Data.DMA_Privatization[DMACounter])&(DMA_Data.DMA_Control[DMACounter]  == SINGLE)){//and if DMA_private_copyflage is not set
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
    }else if (DMA_Data.DMA_Control[DMACounter]  == PRIVATE){
        privatizationBufferPoint = 0;
        for(int j = 0; j<DMACounter; j++){
            privatizationBufferPoint = privatizationBufferPoint + DMA_Data.privatizationBufferCounter[j];
        }
        DMA_Data.privatizationBufferCounter[DMACounter] = size;
        if(!(DMA_Data.DMA_Privatization[DMACounter])){
            //__data16_write_addr((unsigned short)(&DMA0SA), from); // Source block address
            //__data16_write_addr((unsigned short)(&DMA0DA), &privatizationBuffer[2*privatizationBufferPoint]);

              __data20_write_long((uintptr_t) &DMA0DA,(uintptr_t) &privatizationBuffer[2*privatizationBufferPoint]);// Destination single address
            //DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;                // Rpt, inc
            //DMA0SZ = size;           // Block size
            DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer
            DMA_Data.DMA_Privatization[DMACounter] = COMPLETED;
        }
        __data20_write_long((uintptr_t) &DMA0DA,(uintptr_t) to);// Destination single address
        __data20_write_long((uintptr_t) &DMA0SA,(uintptr_t) &privatizationBuffer[2*privatizationBufferPoint]);// Destination single address

        DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3;            // Rpt, inc
        //DMA0SZ = size ;
        DMA0CTL |= DMAEN + DMAREQ;                                      // Enable DMA0 + Trigger block transfer

    }
    DMACounter++;
}*/
void Clean_DMA_Scratch(){
    /*
     * Clean DMA data structure before next task
     */
    int i=0;
    while(i<MAX_DMA_NUM){

        DMA_Data.DMA_Control[i] = RESET;
        DMA_Data.DMA_CheckLock[i] = RESET;
        DMA_Data.DMA_Privatization[i] = RESET;
        DMA_Data.privatizationBufferCounter[i] = RESET;
        i++;
    }
    DMACounter = 1;
    privatizationBufferPoint = 0;
}
/*
void DMA_copy(uint32_t from, uint32_t to, uint16_t size)
{
    Re_exe_number++;

    __data16_write_addr((unsigned short)(&DMA0SA), from); // Source block address
    __data16_write_addr((unsigned short)(&DMA0DA), to);  // Destination single address
    DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA0SZ = size;                          // Block size
    DMA0CTL |= DMAEN + DMAREQ ;                         // Enable DMA0 + Trigger block transfer

}*/

/*void DMA_copy(unsigned int from, unsigned int to, unsigned short size)
{
//    Re_exe_number++;
    __data20_write_long((uintptr_t) &DMA0SA,(uintptr_t) from);
                                            // Source block address
    __data20_write_long((uintptr_t) &DMA0DA,(uintptr_t) to);
                                              // Destination single address
    DMA0CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA0SZ = size;                          // Block size
    DMA0CTL |= DMAEN + DMAREQ ;                         // Enable DMA0 + Trigger block transfer

}*/

