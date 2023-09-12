#include "system_clk.h"

void SystemClock_Config() {
	// 复位RCC寄存器
    RCC_DeInit();
	// 使能HSE
    RCC_HSEConfig(RCC_HSE_ON);
	// 等待HSE就绪
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
	// 关闭PLL
    RCC_PLLCmd(DISABLE);
    // 配置PLL, 8*x=8xMHz, 8*27=216MHz
    // RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3_EXTEN);
    // 使能PLL
    RCC_PLLCmd(ENABLE);
	// 等待PLL就绪
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	// 选择PLL作为系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	// 配置AHB时钟
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	// 配置APB1时钟
	RCC_PCLK1Config(RCC_HCLK_Div2);
	// 配置APB2时钟
	RCC_PCLK2Config(RCC_HCLK_Div1);

	// 使能内部低速时钟
	RCC_LSICmd(ENABLE);
	// 等待LSI就绪
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	//使能内部高速时钟
	RCC_HSICmd(ENABLE);
	// 等待HSI就绪
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
}
