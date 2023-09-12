#ifndef __LED_H_
#define __LED_H_

#include "ch32v30x.h"

#define LED_Port        GPIOC
#define LED2_Pin        GPIO_Pin_1
#define LED1_Pin        GPIO_Pin_2

void LED_Init();
void led1(BitAction bitAction);
void led2(BitAction bitAction);

#endif
