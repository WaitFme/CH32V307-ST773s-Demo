#ifndef __I2C_H_
#define __I2C_H_

#include "ch32v30x.h"

#define I2C1_Port		GPIOB
#define I2C1_PIN_SCL	GPIO_Pin_6
#define I2C1_PIN_SDA	GPIO_Pin_7

void I2C1_Init(uint32_t clockSpeed);
void I2C_WaitCheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

#endif
