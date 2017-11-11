
#include "bsp.h"
#include "FreeRTOSConfig.h"

void BspInit(void)
{ 
	Clk_Init(RCC_SYSCLKSource_HSE);										//��ʼ�� CLOCK	
	Usart1_Init();														//��ʼ�� USART
	Led_Init();															//��ʼ�� LED
#if configGENERATE_RUN_TIME_STATS == 1
	Tim3_Init();														//��ʼ�� TIM3
#endif /* configGENERATE_RUN_TIME_STATS */
}

