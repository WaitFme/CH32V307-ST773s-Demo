#ifndef __RNG_H_
#define __RNG_H_

#include "ch32v30x.h"
#include "ch32v30x_rng.h"

#define NO_INITIAL			0
#define INITIAL_SUCCESS		1
#define INITIAL_FAIL		-1

uint8_t RNG_Init();
uint8_t RNG_GetStatus();
uint32_t RNG_RandomNumber();
uint32_t RNG_RangeRandomNumber(uint32_t min, uint32_t max);

#endif
