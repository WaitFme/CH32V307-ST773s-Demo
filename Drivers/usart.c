#include "usart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void USART1_Init(uint32_t baudRate) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_Struct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = USART1_PIN_TX;
    GPIO_Init(USART1_Port, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = USART1_PIN_RX;
    GPIO_Init(USART1_Port, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudRate;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_Struct);

    USART_Cmd(USART1, ENABLE);
}

void vPrintf(char *fmt, ...) {
    uint8_t UsartPrintfBuf[296];
    va_list ap;
    uint8_t *pStr = UsartPrintfBuf;

    va_start(ap, fmt);
    vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);
    va_end(ap);

    if (!(USART1->STATR & USART_FLAG_TC)) {
		USART_ClearFlag(USART1, USART_FLAG_TC);
	}

    while (*pStr != 0) {
        USART_SendData(USART1, *pStr++);
        while (!(USART1->STATR & USART_FLAG_TC));
        // while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}
