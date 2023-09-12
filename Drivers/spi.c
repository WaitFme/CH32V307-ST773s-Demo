#include "spi.h"

void SPI2_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SPI2_PIN_SCLK | SPI2_PIN_MOSI;
    GPIO_Init(SPI2_Port, &GPIO_InitStructure);

	GPIO_SetBits(SPI2_Port, SPI2_PIN_SCLK | SPI2_PIN_MOSI);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);
}

void SPI2_Transmit(uint8_t transmitData) {
	uint8_t retry = 0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) {
		retry++;
		if (retry > 200) {
			return;
		}
	}
	SPI_I2S_SendData(SPI2, transmitData);
}

uint8_t SPI2_Receive() {
	uint8_t retry = 0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) {
		retry++;
		if (retry > 200) {
			return 0;
		}
	}
	return SPI_I2S_ReceiveData(SPI2);
}

uint8_t SPI2_TransmitReceive(uint8_t value) {
	SPI2_Transmit(value);
	return SPI2_Receive();
}
