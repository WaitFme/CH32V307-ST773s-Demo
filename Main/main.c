#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "ch32v30x_rng.h"
#include "rng.h"
#include "spi.h"
#include "st7735.h"

void initial() {
    SystemCoreClockUpdate();

    SysTick_Init();

    USART1_Init(115200);

    vPrintf("Initial Start\r\n");

    I2C1_Init(4000000);

    SPI2_Init();

    RNG_Init();

    LCD_Init();

    vPrintf("Initial SUCCESS!\r\n");
}

int main() {
    initial();

    LCD_Clear(BLACK);

    while (true) {
        vPrintf("randomNumber: %d\r\n", RNG_RangeRandomNumber(0, 100));

        Delay(1000);
    }
}
