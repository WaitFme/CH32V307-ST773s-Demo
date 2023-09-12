#include "rng.h"
#include "system_tick.h"

static uint8_t rng_status = NO_INITIAL;

uint8_t RNG_GetFlagStatusTimeout(uint8_t RNG_FLAG, uint16_t timeout);

uint8_t RNG_Init() {
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);

    RNG_Cmd(ENABLE);

    rng_status = RNG_GetFlagStatusTimeout(RNG_FLAG_DRDY, 200);

    return rng_status;
}

uint8_t RNG_GetStatus() {
    return rng_status;
}

uint8_t RNG_GetFlagStatusTimeout(uint8_t RNG_FLAG, uint16_t timeout) {
    uint16_t entry = 0;

    while (RNG->SR & RNG_FLAG) {
        entry++;

        Delay(1);

        if (entry >= timeout) {
            return INITIAL_FAIL;
        }
    }

    return INITIAL_SUCCESS;
}

uint32_t RNG_RandomNumber() {
	if (rng_status == 1) {
    	return RNG->DR;
	} else {
        return INITIAL_FAIL;
    }
}

uint32_t RNG_RangeRandomNumber(uint32_t min, uint32_t max) {
   return RNG_RandomNumber() % (max - min + 1) + min;
}
