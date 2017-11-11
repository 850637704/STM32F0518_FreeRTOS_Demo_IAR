
#include "clock.h"
#include "FreeRTOS.h"						  
#include "task.h" 

void Clk_Init(uint32_t SYSCLKSource)									//初始化SYSCLK为48M
{
	assert_param(IS_SYSCLK_SOURCE(SYSCLKSource));						//参数检查 RCC_SYSCLKSource_HSI Or RCC_SYSCLKSource_HSE
	
	RCC_DeInit();														//复位RCC相关寄存器
	RCC_HSICmd(ENABLE);													//HSI使能输出
	if(SYSCLKSource == RCC_SYSCLKSource_HSI)
	{
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);			//HSI/2的12倍频作为PLLCLK输入
	}
	else if(SYSCLKSource == RCC_SYSCLKSource_HSE)
	{
		RCC_HSEConfig(RCC_HSE_ON);										//HSE使能输出
		RCC_PREDIV1Config(RCC_PREDIV1_Div1);							//PREDIV 1 分频
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);				//PREDIV1的6倍频作为PLLCLK输入
		while(SUCCESS != RCC_WaitForHSEStartUp());						//等待HSE稳定
		RCC_HSICmd(DISABLE);											//关闭HSI
	}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);							//PLLCLK作为SYSCLK输入
	RCC_PLLCmd(ENABLE);													//PLL使能输出
}

//void Systick_Init(void)													//初始化SysTick时钟频率
//{
//	uint32_t reload;
//	
//	RCC_HCLKConfig(RCC_SYSCLK_Div1);									//HCLK = SYSCLK = 48M
//	
//	reload = SystemCoreClock/1000000;									//每秒钟的计数次数 单位为M
//	reload *= 1000000/configTICK_RATE_HZ;								//根据configTICK_RATE_HZ设置溢出时间
//
//	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   						//开启SYSTICK中断
//	SysTick->LOAD = reload; 											//每1/configTICK_RATE_HZ秒中断一次
//	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   						//开启SYSTICK  
//}

