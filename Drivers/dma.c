#include "dma.h"

static uint16_t DMA1_MEM_LEN;

void DMA1_Init(uint32_t addr0, uint32_t addr1, uint16_t size) {
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA1_MEM_LEN = size;

	DMA_InitStructure.DMA_PeripheralBaseAddr = addr0;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = addr1;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_BufferSize = size;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

	DMA_Init(DMA1_Channel5, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel5, ENABLE);
}

void DMA1_Transmit() {
	DMA_Cmd(DMA1_Channel5, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel5, DMA1_MEM_LEN);
	DMA_Cmd(DMA1_Channel5, ENABLE);
}
