/*
 *********************************************************************************************************
 *
 * 模块名称 : printf模块
* 文件名称 : bsp_printf.c
 * 版    本 : V2.0
 * 说    明 : 实现printf和scanf函数重定向到串口2，即支持printf信息到UART2
 *    实现重定向，只需要添加2个函数:
 *    int fputc(int ch, FILE *f);
 *    int fgetc(FILE *f);
 *
 *    这个c模块无对应的h文件。
 *    如果需要应用程序支持 printf 函数，只用将 bsp_printf.c 这个文件添加到工程即可。
 *
 * 修改记录 :
 *  版本号  日期       作者    说明
 *  v1.0    2012-10-12 armfly  ST固件库版本 V2.1.0
 *
 * Copyright (C), 2012-2013, 安富莱电子 www.armfly.com
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
  由于不同的编译器 putcha 和 getchar 形参和返回值略有不同。
 因此此处采用宏定义的方式区别。

 _RAISONANCE_ 和 _COSMIC_ 这2个宏是由编译器自动添加的预编译宏
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
