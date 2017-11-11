

#include "usart1.h"
#include "string.h"
#include "FreeRTOS.h"  
#include "task.h" 

uint8_t USART_RX_BUF[USART_REC_LEN];     										//串口接收缓存区,长度USART_REC_LEN个字节

/* USART初始化 */
void Usart1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  						//使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);						//使能USART的时钟
	/* USART1的端口配置 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);						//配置PA9成第二功能引脚	TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);						//配置PA10成第二功能引脚  RX	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1的基本配置 */
	USART_InitStructure.USART_BaudRate = 115200;              					//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           						//使能接收中断
	USART_Cmd(USART1, ENABLE);                             						//使能USART1
	
	/* USART1的NVIC中断配置 */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x03;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);		
}

extern TaskHandle_t COM_TASK_HANDLER;											//COM   任务 句柄
//注意：一定要在消息的最后加上新行，否则会导致信息叠加！
//接收状态：
//bit15:接收完成标志
//bit14:接收到0x0d
//bit13~0:接收到的有效字节数,最大512字节
uint16_t USART_RX_STA = 0;														//接收状态标记
void USART1_IRQHandler(void)
{
	uint8_t res;
	BaseType_t  xHigherPriorityTaskWoken = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  						//接收到数据
	{
#if EN_USART1_RX																//如果允许串口1接收数据
		res = USART_ReceiveData(USART1);										//读取接收到的数据
		
		if((USART_RX_STA & 0x8000) == 0)										//接收还未完成
		{
			if(USART_RX_STA & 0x4000)											//接收到0x0d
			{
				if(res != 0x0a)
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = 0x0d;					//补上丢失的0x0d
					USART_RX_STA++;
					if(res == 0x0d)	USART_RX_STA |= 0x4000;
					else
					{
						USART_RX_BUF[USART_RX_STA & 0x3fff] = res;				//继续接收数据
						USART_RX_STA++;
						USART_RX_STA &= 0xbfff;									//清除0x0d标志
					}
				}
				else
				{
					if(USART_RX_STA&0x3fff)										//已接收到非空数据
					{
						USART_RX_STA |= 0x8000;									//接收完成
						USART_RX_BUF[(USART_RX_STA&0x3fff)] = '\0'; 			//printf停止
						
						(void)xTaskNotifyFromISR((TaskHandle_t )COM_TASK_HANDLER,			//消息目的任务
												 (uint32_t     )&USART_RX_BUF,				//消息邮箱指针
												 (eNotifyAction)eSetValueWithOverwrite,		//覆盖方式
												 (BaseType_t  *)xHigherPriorityTaskWoken);	//是否进行任务切换
						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);			//如果需要的话进行一次任务切换
					}
					else	
					{
						USART_RX_STA = 0;										//没有消息、只有换行符
						memset(USART_RX_BUF,0x00,(USART_REC_LEN+1));			//清空串口缓存区
					}
				}
			}
			else																//没接收到0x0d
			{	
				if(res == 0x0d)	USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;
					USART_RX_STA++;
					if(USART_RX_STA > (USART_REC_LEN - 1))						//接收数据错误，重新开始
					{
						USART_RX_STA = 0;
						memset(USART_RX_BUF,0x00,(USART_REC_LEN+1));			//清空串口缓存区
					}
				}
			}
		}
#endif /* EN_USART1_RX */
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	}
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}



