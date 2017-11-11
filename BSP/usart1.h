
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

#define USART_REC_LEN  			30  											//���ڽ��ջ��������� 30  ���˹��� ����ᵼ�½��մ�������ʱϵͳ����
#define EN_USART1_RX 			1												//���ڽ���ʹ�� (1)/ʹ�� (0)/ʧ��
	  	
//extern uint8_t  USART_RX_BUF[USART_REC_LEN]; 									//���ڽ��ջ�����,��ʾUSART_REC_LEN���ֽ�
extern uint16_t USART_RX_STA;         											//���ڽ��ձ�־	
  
void Usart1_Init(void);

#endif