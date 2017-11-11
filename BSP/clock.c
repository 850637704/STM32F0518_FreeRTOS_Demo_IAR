
#include "clock.h"
#include "FreeRTOS.h"						  
#include "task.h" 

void Clk_Init(uint32_t SYSCLKSource)									//��ʼ��SYSCLKΪ48M
{
	assert_param(IS_SYSCLK_SOURCE(SYSCLKSource));						//������� RCC_SYSCLKSource_HSI Or RCC_SYSCLKSource_HSE
	
	RCC_DeInit();														//��λRCC��ؼĴ���
	RCC_HSICmd(ENABLE);													//HSIʹ�����
	if(SYSCLKSource == RCC_SYSCLKSource_HSI)
	{
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);			//HSI/2��12��Ƶ��ΪPLLCLK����
	}
	else if(SYSCLKSource == RCC_SYSCLKSource_HSE)
	{
		RCC_HSEConfig(RCC_HSE_ON);										//HSEʹ�����
		RCC_PREDIV1Config(RCC_PREDIV1_Div1);							//PREDIV 1 ��Ƶ
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);				//PREDIV1��6��Ƶ��ΪPLLCLK����
		while(SUCCESS != RCC_WaitForHSEStartUp());						//�ȴ�HSE�ȶ�
		RCC_HSICmd(DISABLE);											//�ر�HSI
	}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);							//PLLCLK��ΪSYSCLK����
	RCC_PLLCmd(ENABLE);													//PLLʹ�����
}

//void Systick_Init(void)													//��ʼ��SysTickʱ��Ƶ��
//{
//	uint32_t reload;
//	
//	RCC_HCLKConfig(RCC_SYSCLK_Div1);									//HCLK = SYSCLK = 48M
//	
//	reload = SystemCoreClock/1000000;									//ÿ���ӵļ������� ��λΪM
//	reload *= 1000000/configTICK_RATE_HZ;								//����configTICK_RATE_HZ�������ʱ��
//
//	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   						//����SYSTICK�ж�
//	SysTick->LOAD = reload; 											//ÿ1/configTICK_RATE_HZ���ж�һ��
//	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   						//����SYSTICK  
//}

