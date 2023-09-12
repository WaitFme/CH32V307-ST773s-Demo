#ifndef __ST7735_H
#define __ST7735_H

#include "ch32v30x.h"

#define USE_HORIZONTAL 1

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
	#define LCD_W 128
	#define LCD_H 160
#else
	#define LCD_W 160
	#define LCD_H 128
#endif

#define WHITE				0xFFFF
#define BLACK				0x0000
#define BLUE				0x001F
#define BRED				0XF81F
#define GRED				0XFFE0
#define GBLUE				0X07FF
#define RED					0xF800
#define MAGENTA				0xF81F
#define GREEN				0x07E0
#define CYAN				0x7FFF
#define YELLOW				0xFFE0
#define BROWN				0XBC40
#define BRRED				0XFC07
#define GRAY				0X8430
#define DARKBLUE			0X01CF
#define LIGHTBLUE			0X7D7C
#define GRAYBLUE			0X5458
#define LIGHTGREEN 			0X841F
#define LGRAY				0XC618
#define LGRAYBLUE			0XA651
#define LBBLUE				0X2B12

#define LCD_Port			GPIOB
#define LCD_DC_Pin			GPIO_Pin_0		// PA2
#define LCD_CS_Pin			GPIO_Pin_1		// PA3
#define LCD_RST_Pin			GPIO_Pin_12		// PA4

#define LCD_DC_WB(x)		GPIO_WriteBit(LCD_Port, LCD_DC_Pin, (BitAction)(x))
#define LCD_CS_WB(x)		GPIO_WriteBit(LCD_Port, LCD_CS_Pin, (BitAction)(x))
#define LCD_RST_WB(x)		GPIO_WriteBit(LCD_Port, LCD_RST_Pin, (BitAction)(x))

void LCD_Init(void);
void LCD_WriteData(u8 data);
void LCD_WriteData_16Bit(u16 data);
void LCD_WriteCMD(u8 cmd);
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void LCD_Fill_DMA(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);
void LCD_Clear(uint16_t color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_DrawCircle(u16 x0, u16 y0, u8 r, u16 color);
void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode);
void LCD_ShowString(u16 x, u16 y, const u8 *data, u16 fc, u16 bc, u8 sizey, u8 mode);
u32 mypow(u8 m, u8 n);
void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey);
void LCD_ShowFloatNum(u16 x, u16 y, float num, u8 len, u16 fc, u16 bc, u8 sizey);

#endif
