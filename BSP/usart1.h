
#ifndef __USART1_H
#define __USART1_H

#include "stm32f0xx.h"
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#define USART_REC_LEN  			30  											//串口接收缓存区长度 30  不宜过长 否则会导致接收串口数据时系统崩溃
#define EN_USART1_RX 			1												//串口接收使能 (1)/使能 (0)/失能
	  	
//extern uint8_t  USART_RX_BUF[USART_REC_LEN]; 									//串口接收缓存区,表示USART_REC_LEN个字节
extern uint16_t USART_RX_STA;         											//串口接收标志	
  
void Usart1_Init(void);

#endif