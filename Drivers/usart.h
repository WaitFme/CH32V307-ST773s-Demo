#ifndef __USART_H_
#define __USART_H_

#include "ch32v30x.h"

#define USART1_Port		GPIOA
#define USART1_PIN_TX	GPIO_Pin_9
#define USART1_PIN_RX	GPIO_Pin_10

void USART1_Init(uint32_t baudRate);
void vPrintf(char *fmt, ...);

#endif
