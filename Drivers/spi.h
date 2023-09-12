#ifndef __SPI_H_
#define __SPI_H_

#include "ch32v30x.h"

#define SPI2_Port		GPIOB
#define SPI2_PIN_CS		GPIO_Pin_12
#define SPI2_PIN_SCLK	GPIO_Pin_13//
#define SPI2_PIN_MISO	GPIO_Pin_14
#define SPI2_PIN_MOSI	GPIO_Pin_15

void SPI2_Init();
void SPI2_Transmit(uint8_t transmitData);
uint8_t SPI2_Receive();
uint8_t SPI2_TransmitReceive(uint8_t value);

#endif
