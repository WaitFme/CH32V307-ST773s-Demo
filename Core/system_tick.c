#include "system_tick.h"

static uint8_t p_us = 0;
static uint16_t p_ms = 0;

void SysTick_Init() {
    p_us = SystemCoreClock / 8000000;
    p_ms = (uint16_t)p_us * 1000;
}

void DelayUs(uint32_t n) {
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * p_us;

    SysTick->CMP = i;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0))
        ;
    SysTick->CTLR &= ~(1 << 0);
}

void Delay(uint32_t n) {
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * p_ms;

    SysTick->CMP = i;
    SysTick->CTLR |= (1 << 4);
    SysTick->CTLR |= (1 << 5) | (1 << 0);

    while ((SysTick->SR & (1 << 0)) != (1 << 0))
        ;
    SysTick->CTLR &= ~(1 << 0);
}

/*
static uint16_t UsNumber = 0;
static uint16_t MsNumber = 0;

void SysTick_Init() {
        RCC_ClocksTypeDef clocks;
        RCC_GetClocksFreq(&clocks);
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
        UsNumber = clocks.HCLK_Frequency / HSE_VALUE;
        MsNumber = UsNumber * 1000;
        SysTick -> CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
        SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_Us(uint16_t nus) {
    SysTick -> LOAD = UsNumber * nus;
    SysTick -> VAL = 0x00;
    SysTick -> CTRL = SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick -> CTRL = ~SysTick_CTRL_ENABLE_Msk;
}

void delay(uint16_t nms) {
    SysTick -> LOAD = MsNumber * nms;
    SysTick -> VAL = 0x00;
    SysTick -> CTRL = SysTick_CTRL_ENABLE_Msk;
    while(!(SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick -> CTRL = ~SysTick_CTRL_ENABLE_Msk;
}

void delay_S(uint16_t ns) {
    while(ns--) {
        delay(1000);
    }
} */
