
#ifndef __CLOCK_H
#define __CLOCK_H

#include "stm32f0xx_rcc.h"

#define IS_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE))

void Clk_Init(uint32_t SYSCLKSource);

//void Systick_Init(void);

#endif

