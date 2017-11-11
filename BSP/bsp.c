
#include "bsp.h"
#include "FreeRTOSConfig.h"

void BspInit(void)
{ 
	Clk_Init(RCC_SYSCLKSource_HSE);										//初始化 CLOCK	
	Usart1_Init();														//初始化 USART
	Led_Init();															//初始化 LED
#if configGENERATE_RUN_TIME_STATS == 1
	Tim3_Init();														//初始化 TIM3
#endif /* configGENERATE_RUN_TIME_STATS */
}

