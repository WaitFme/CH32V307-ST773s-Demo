#ifndef __DMA_H
#define __DMA_H

#include "ch32v30x.h"

void DMA1_Init(uint32_t addr0, uint32_t addr1, uint16_t size);
void DMA1_Transmit(void);

#endif
