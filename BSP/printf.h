/*
 *********************************************************************************************************
 *
 * ģ������ : printfģ��
* �ļ����� : bsp_printf.c
 * ��    �� : V2.0
 * ˵    �� : ʵ��printf��scanf�����ض��򵽴���2����֧��printf��Ϣ��UART2
 *    ʵ���ض���ֻ��Ҫ���2������:
 *    int fputc(int ch, FILE *f);
 *    int fgetc(FILE *f);
 *
 *    ���cģ���޶�Ӧ��h�ļ���
 *    �����ҪӦ�ó���֧�� printf ������ֻ�ý� bsp_printf.c ����ļ���ӵ����̼��ɡ�
 *
 * �޸ļ�¼ :
 *  �汾��  ����       ����    ˵��
 *  v1.0    2012-10-12 armfly  ST�̼���汾 V2.1.0
 *
 * Copyright (C), 2012-2013, ���������� www.armfly.com
 *
 *********************************************************************************************************
 */
#ifndef __PRINTF_H
#define __PRINTF_H

#include <stdio.h>
#include "usart1.h"
   
/*------------------------------------DEBUG-----------------------------------*/
//#define MPU_DEBUG_DEFINE

/*
  ���ڲ�ͬ�ı����� putcha �� getchar �βκͷ���ֵ���в�ͬ��
 ��˴˴����ú궨��ķ�ʽ����

 _RAISONANCE_ �� _COSMIC_ ��2�������ɱ������Զ���ӵ�Ԥ�����
*/
 #ifdef _RAISONANCE_
  #define PUTCHAR_PROTOTYPE int putchar (char c)
  #define GETCHAR_PROTOTYPE int getchar (void)
 #elif defined (_COSMIC_)
  #define PUTCHAR_PROTOTYPE char putchar (char c)
  #define GETCHAR_PROTOTYPE char getchar (void)
 #else /* _IAR_ */
  #define PUTCHAR_PROTOTYPE int putchar (int c)
  #define GETCHAR_PROTOTYPE int getchar (void)
 #endif /* _RAISONANCE_ */

#endif
