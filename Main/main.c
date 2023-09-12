#include "main.h"
#include "usart.h"
#include "ch32v30x_rng.h"
#include "rng.h"
#include "spi.h"
#include "st7735.h"

void initial() {
    SystemCoreClockUpdate();

    SysTick_Init();

    USART1_Init(115200);

    vPrintf("Initial Start\r\n");

    SPI2_Init();

    RNG_Init();

    LCD_Init();

    vPrintf("Initial SUCCESS!\r\n");
}

int main() {
    initial();

    // LCD_Clear(BLACK);

    while (true) {
        vPrintf("randomNumber: %d\r\n", RNG_RangeRandomNumber(0, 100));

        Delay(1000);
    }
}
