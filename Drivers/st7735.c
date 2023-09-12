#include "st7735.h"
#include "spi.h"
#include "system_tick.h"
#include "lcdfont.h"
#include "dma.h"

void LCD_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LCD_RST_Pin | LCD_CS_Pin | LCD_DC_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_Port, &GPIO_InitStructure);

 	GPIO_SetBits(LCD_Port, LCD_CS_Pin | LCD_DC_Pin | LCD_RST_Pin);

    // RESET
	LCD_RST_WB(0);
    Delay(100);
	LCD_RST_WB(1);
    Delay(100);

    // SLPOUT
    LCD_WriteCMD(0x11);
    Delay(120);

    //------------------------------------ST7735S Frame Rate-----------------------------------------//
	LCD_WriteCMD(0xB1);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x3C);
	LCD_WriteCMD(0xB2);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x3C);
	LCD_WriteCMD(0xB3);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x05);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x3C);
	//------------------------------------End ST7735S Frame Rate---------------------------------//
	LCD_WriteCMD(0xB4); //Dot inversion
	LCD_WriteData(0x03);
	//------------------------------------ST7735S Power Sequence---------------------------------//
	LCD_WriteCMD(0xC0);
	LCD_WriteData(0x28);
	LCD_WriteData(0x08);
	LCD_WriteData(0x04);
	LCD_WriteCMD(0xC1);
	LCD_WriteData(0XC0);
	LCD_WriteCMD(0xC2);
	LCD_WriteData(0x0D);
	LCD_WriteData(0x00);
	LCD_WriteCMD(0xC3);
	LCD_WriteData(0x8D);
	LCD_WriteData(0x2A);
	LCD_WriteCMD(0xC4);
	LCD_WriteData(0x8D);
	LCD_WriteData(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	LCD_WriteCMD(0xC5); //VCOM
	LCD_WriteData(0x1A);
	LCD_WriteCMD(0x36); //MX, MY, RGB mode
	if (USE_HORIZONTAL == 0) {
		LCD_WriteData(0x00);
	} else if (USE_HORIZONTAL == 1) {
		LCD_WriteData(0xC0);
	} else if (USE_HORIZONTAL == 2) {
		LCD_WriteData(0x70);
	} else {
		LCD_WriteData(0xA0);
	}
	//------------------------------------ST7735S Gamma Sequence---------------------------------//
	LCD_WriteCMD(0xE0);
	LCD_WriteData(0x04);
	LCD_WriteData(0x22);
	LCD_WriteData(0x07);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x2E);
	LCD_WriteData(0x30);
	LCD_WriteData(0x25);
	LCD_WriteData(0x2A);
	LCD_WriteData(0x28);
	LCD_WriteData(0x26);
	LCD_WriteData(0x2E);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x03);
	LCD_WriteData(0x13);
	LCD_WriteCMD(0xE1);
	LCD_WriteData(0x04);
	LCD_WriteData(0x16);
	LCD_WriteData(0x06);
	LCD_WriteData(0x0D);
	LCD_WriteData(0x2D);
	LCD_WriteData(0x26);
	LCD_WriteData(0x23);
	LCD_WriteData(0x27);
	LCD_WriteData(0x27);
	LCD_WriteData(0x25);
	LCD_WriteData(0x2D);
	LCD_WriteData(0x3B);
	LCD_WriteData(0x00);
	LCD_WriteData(0x01);
	LCD_WriteData(0x04);
	LCD_WriteData(0x13);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------//
	LCD_WriteCMD(0x3A); //65k mode
	LCD_WriteData(0x05);
	LCD_WriteCMD(0x29); //Display on
}

void LCD_WriteData(u8 data) {
    LCD_CS_WB(0);
    SPI2_Transmit(data);
    LCD_CS_WB(1);
}

void LCD_WriteData_16Bit(u16 data) {
	LCD_CS_WB(0);
	SPI2_Transmit(data >> 8);
	SPI2_Transmit((u8) data);
	LCD_CS_WB(1);
}

void LCD_WriteCMD(u8 cmd) {
	LCD_CS_WB(0);
	LCD_DC_WB(0);
	SPI2_Transmit(cmd);
	LCD_DC_WB(1);
	LCD_CS_WB(1);
}

void LCD_Address_Set(u16 x_start,u16 y_start,u16 x_end,u16 y_end) {
	if(USE_HORIZONTAL == 0) {
		LCD_WriteCMD(0x2a);
		LCD_WriteData_16Bit(x_start+2);
		LCD_WriteData_16Bit(x_end+2);
		LCD_WriteCMD(0x2b);
		LCD_WriteData_16Bit(y_start+1);
		LCD_WriteData_16Bit(y_end+1);
		LCD_WriteCMD(0x2c);
	} else if(USE_HORIZONTAL == 1) {
		LCD_WriteCMD(0x2a);
		LCD_WriteData_16Bit(x_start);
		LCD_WriteData_16Bit(x_end);
		LCD_WriteCMD(0x2b);
		LCD_WriteData_16Bit(y_start);
		LCD_WriteData_16Bit(y_end);
		LCD_WriteCMD(0x2c);
	} else if(USE_HORIZONTAL == 2) {
		LCD_WriteCMD(0x2a);
		LCD_WriteData_16Bit(x_start+1);
		LCD_WriteData_16Bit(x_end+1);
		LCD_WriteCMD(0x2b);
		LCD_WriteData_16Bit(y_start+2);
		LCD_WriteData_16Bit(y_end+2);
		LCD_WriteCMD(0x2c);
	} else {
		LCD_WriteCMD(0x2a);
		LCD_WriteData_16Bit(x_start+1);
		LCD_WriteData_16Bit(x_end+1);
		LCD_WriteCMD(0x2b);
		LCD_WriteData_16Bit(y_start+2);
		LCD_WriteData_16Bit(y_end+2);
		LCD_WriteCMD(0x2c);
	}
}

void LCD_Fill(u16 x_start, u16 y_start, u16 x_end, u16 y_end, u16 color) {
	// LCD_Address_Set(x_start, y_start, x_end - 1, y_end - 1);
	LCD_Address_Set(x_start, y_start, x_end, y_end);
	for(uint16_t i = y_start; i < y_end; i++) {
		for(uint16_t j = x_start; j < x_end; j++) {
			LCD_WriteData_16Bit(color);
		}
	}
}

void LCD_Fill_DMA(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color) {
	u16 color1[1];
	u16 num;
	color1[0] = color;
	num = (xend - xsta) * (yend - ysta);
	LCD_Address_Set(xsta, ysta, xend - 1, yend - 1);

	LCD_CS_WB(0);

	SPI2 -> CTLR1 |= 1 << 11;
	SPI_Cmd(SPI2, ENABLE);

	DMA1_Init((uint32_t) &SPI2 -> DATAR, (uint32_t) color1, num);

	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

	DMA1_Transmit();

	while(1) {
		if(DMA_GetFlagStatus(DMA1_FLAG_TC3) != RESET) {
			DMA_ClearFlag(DMA1_FLAG_TC3);
			break;
		}
	}

	LCD_CS_WB(1);

	SPI2 -> CTLR1 = ~SPI2 -> CTLR1;
	SPI2 -> CTLR1 |= 1 << 11;
	SPI2 -> CTLR1 = ~SPI2 -> CTLR1;
	SPI_Cmd(SPI2, ENABLE);
}

void LCD_Clear(uint16_t color) {
	LCD_Fill_DMA(0, 0, LCD_W, LCD_H, color);
}

void LCD_DrawPoint(u16 x,u16 y,u16 color) {
	LCD_Address_Set(x, y, x, y);
	LCD_WriteData_16Bit(color);
}

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;

	// 计算坐标增量
	delta_x = x2 - x1;
	delta_y = y2 - y1;

	// 画线起点坐标
	uRow = x1;
	uCol = y1;

	if(delta_x > 0) {
		// 设置单步方向
		incx = 1;
	} else if (delta_x == 0) {
		// 垂直线
		incx = 0;
	} else {
		incx = -1;
		delta_x = -delta_x;
	}

	if (delta_y > 0) {
		incy = 1;
	} else if (delta_y == 0) {
		// 水平线
		incy = 0;
	} else {
		incy = -1;
		delta_y = -delta_y;
	}

	if (delta_x > delta_y) {
		// 选取基本增量坐标轴
		distance = delta_x;
	} else {
		distance = delta_y;
	}

	for(u16 t = 0; t < distance + 1; t++) {
		// 画点
		LCD_DrawPoint((u16)uRow, (u16)uCol, color);

		xerr += delta_x;
		yerr += delta_y;

		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}

		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color) {
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}

void LCD_DrawCircle(u16 x0, u16 y0, u8 r, u16 color) {
	//int a = 0, b = r;
	u16 a = 0, b = r;

	while(a <= b) {
		LCD_DrawPoint(x0 - b, y0 - a, color);
		LCD_DrawPoint(x0 + b, y0 - a, color);
		LCD_DrawPoint(x0 - a, y0 + b, color);
		LCD_DrawPoint(x0 - a, y0 - b, color);
		LCD_DrawPoint(x0 + b, y0 + a, color);
		LCD_DrawPoint(x0 + a, y0 - b, color);
		LCD_DrawPoint(x0 + a, y0 + b, color);
		LCD_DrawPoint(x0 - b, y0 + a, color);

		a++;

		if((a * a + b * b) > (r * r)) {
			b--;
		}
	}
}

void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode) {
	u8 temp, sizex, m = 0;
	u16 TypefaceNum;
	u16 x0 = x;
	sizex = sizey / 2;
	TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
	num = num - ' ';

	LCD_Address_Set(x, y, x + sizex - 1, y+sizey - 1);

	for (u16 i = 0; i < TypefaceNum; i++) {
		if (sizey == 12) {
			temp = ascii_1206[num][i];
		} else if (sizey == 16) {
			temp = ascii_1608[num][i];
		} else if (sizey == 24) {
			temp = ascii_2412[num][i];
		} else if (sizey == 32) {
			temp = ascii_3216[num][i];
		} else {
			return;
		}

		for (u16 t = 0; t < 8; t++) {
			if (!mode) {
				if (temp & (0x01 << t)) {
					LCD_WriteData_16Bit(fc);
				} else {
					LCD_WriteData_16Bit(bc);
				}

				m++;

				if(m % sizex == 0) {
					m=0;
					break;
				}
			} else {
				if (temp & (0x01 << t)) {
					LCD_DrawPoint(x, y, fc);
				}

				x++;

				if ((x - x0) == sizex) {
					x = x0;
					y++;
					break;
				}
			}
		}
	}
}

void LCD_ShowString(u16 x, u16 y, const u8 *data, u16 fc, u16 bc, u8 sizey, u8 mode) {
	while(*data != '\0') {
		LCD_ShowChar(x, y, *data, fc, bc, sizey, mode);
		x += sizey / 2;
		data++;
	}
}

u32 mypow(u8 m, u8 n) {
	u32 result = 1;

	while(n--) {
		result *= m;
	}

	return result;
}

void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey) {
	u8 t, temp;
	u8 enshow = 0;
	u8 sizex = sizey / 2;
	for (t = 0; t < len; t++) {
		temp = (num / mypow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
				continue;
			} else {
				enshow = 1;
			}
		}
	 	LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

void LCD_ShowFloatNum(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey) {
	u8 t, temp, sizex;
	u16 num1;
	sizex = sizey / 2;
	num1 = num * 100;
	for(t=0;t<len;t++) {
		temp=(num1 / mypow(10, len - t - 1)) % 10;
		if(t == (len - 2)) {
			LCD_ShowChar(x + (len - 2) * sizex, y, '.', fc, bc, sizey, 0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
	}
}

