
#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>
#include <stdbool.h>
#include "mem.h"

#define FRAM_START 0x4000
#define FRAM_END 0xFF7F
#define HIFRAM_START 0x00010000
#define HIFRAM_END 0x00043FF7

#define ALWAYS 0
#define SINGLE 1
#define PRIVATE 2
#define COMPLETED true
#define TRUE true
#define FALSE false
#define SET 1
#define RESET 0

#ifndef MAX_DMA_NUM
#define MAX_DMA_NUM 10
#endif

#ifndef MAX_PRIV_BUFFER
#define MAX_PRIV_BUFFER 4000
#endif

typedef struct{
    /*volatile uint16_t *DMA_SrcBuf[MAX_DMA_NUM]; //TODO : fix the variable type for HIFRAM-20bit addresses
    volatile uint16_t *DMA_DstBuf[MAX_DMA_NUM];
    volatile uint16_t DMA_SizeBuf[MAX_DMA_NUM];*/
    volatile uint8_t DMA_Control[MAX_DMA_NUM];
    volatile bool DMA_CheckLock[MAX_DMA_NUM];
    volatile bool DMA_Privatization[MAX_DMA_NUM];
    volatile uint64_t privatizationBufferCounter[MAX_DMA_NUM];
}DMA_Pramas;


extern DMA_Pramas DMA_Data;
extern char DMA_flag;
extern uint8_t privatizationBuffer [MAX_PRIV_BUFFER];
extern uint8_t DMACounter;

bool CheckNVM(uint32_t startAdr, uint32_t size);
//void SaveDMAData(uint16_t srcAdr, int16_t dstAdr, uint16_t size);
//bool CheckDMAWar();
void Clean_DMA_Scratch();

#endif /* DMA_H_ */
