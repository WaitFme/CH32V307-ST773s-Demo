#include "i2c.h"

void I2C1_Init(uint32_t clockSpeed) {
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = I2C1_PIN_SCL | I2C1_PIN_SDA;
    GPIO_Init(I2C1_Port, &GPIO_InitStructure);

    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = clockSpeed;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_Cmd(I2C1, ENABLE);
}

void I2C_WaitCheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
	uint32_t timeout = 10000;

	while (I2C_CheckEvent(I2Cx, I2C_EVENT) == NoREADY) {
		timeout--;
		if (timeout == 0) {
			break;
		}
	}
}
