

#include "led.h"

void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* ʹ��GPIOBʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	/* ����LED��Ӧ����PB1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*------------------------------------------------
					LED����
------------------------------------------------*/
void Led_On(uint8_t n)
{
	switch(n)
	{
		case 0: LED0(1);  break;
		case 1: LED1(1);  break;
		default:{};break;
	}
}
/*------------------------------------------------
					LEDϨ��
------------------------------------------------*/
void Led_Off(uint8_t n)
{
	switch(n)
	{
		case 0: LED0(0);  break;
		case 1: LED1(0);  break;
		default:{};break;
	}
}





