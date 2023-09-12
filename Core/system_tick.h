#ifndef __SYSTEM_TICK_H_
#define __SYSTEM_TICK_H_

#include "ch32v30x.h"

void SysTick_Init();
void DelayUs(uint32_t n);
void Delay(uint32_t n);

/*
void SysTick_Init();
void delay_Us(uint16_t nus);
void delay(uint16_t nms);
void delay_S(uint16_t ns); */

#endif
