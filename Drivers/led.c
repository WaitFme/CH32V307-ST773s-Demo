#include "led.h"

void LED_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED1_Pin | LED2_Pin;
    GPIO_Init(LED_Port, &GPIO_InitStructure);
}

void led1(BitAction bitAction) {
    GPIO_WriteBit(LED_Port, LED1_Pin, bitAction);
}

void led2(BitAction bitAction) {
    GPIO_WriteBit(LED_Port, LED2_Pin, bitAction);
}
