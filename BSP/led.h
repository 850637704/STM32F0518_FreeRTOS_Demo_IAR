

#ifndef __LED_H
#define __LED_H

#include "stm32f0xx_gpio.h"

#define led0	0x00
#define led1	0x01

#define Px13 (1<<13)
#define Px14 (1<<14)
#define LED0(x) GPIOC->ODR=(GPIOC->ODR&~Px13)|(x ? Px13:0)//PC13
#define LED1(x) GPIOC->ODR=(GPIOC->ODR&~Px14)|(x ? Px14:0)//PC14

void Led_Init(void);

void Led_On(uint8_t n);

void Led_Off(uint8_t n);

#endif
