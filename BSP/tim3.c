
#include "tim3.h"

volatile unsigned long long RunTimeCounterValue;

void Tim3_Init(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 		
	
	TIM_BaseInitStructure.TIM_Period = 50-1;
	TIM_BaseInitStructure.TIM_Prescaler = 48-1;
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); //清除溢出中断标志

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//TIM1开启
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		RunTimeCounterValue ++;
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

