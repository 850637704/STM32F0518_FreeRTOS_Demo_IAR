

#include "usart1.h"
#include "string.h"
#include "FreeRTOS.h"  
#include "task.h" 

uint8_t USART_RX_BUF[USART_REC_LEN];     										//���ڽ��ջ�����,����USART_REC_LEN���ֽ�

/* USART��ʼ�� */
void Usart1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  						//ʹ��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);						//ʹ��USART��ʱ��
	/* USART1�Ķ˿����� */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);						//����PA9�ɵڶ���������	TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);						//����PA10�ɵڶ���������  RX	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1�Ļ������� */
	USART_InitStructure.USART_BaudRate = 115200;              					//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           						//ʹ�ܽ����ж�
	USART_Cmd(USART1, ENABLE);                             						//ʹ��USART1
	
	/* USART1��NVIC�ж����� */
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x03;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);		
}

extern TaskHandle_t COM_TASK_HANDLER;											//COM   ���� ���
//ע�⣺һ��Ҫ����Ϣ�����������У�����ᵼ����Ϣ���ӣ�
//����״̬��
//bit15:������ɱ�־
//bit14:���յ�0x0d
//bit13~0:���յ�����Ч�ֽ���,���512�ֽ�
uint16_t USART_RX_STA = 0;														//����״̬���
void USART1_IRQHandler(void)
{
	uint8_t res;
	BaseType_t  xHigherPriorityTaskWoken = 0;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  						//���յ�����
	{
#if EN_USART1_RX																//���������1��������
		res = USART_ReceiveData(USART1);										//��ȡ���յ�������
		
		if((USART_RX_STA & 0x8000) == 0)										//���ջ�δ���
		{
			if(USART_RX_STA & 0x4000)											//���յ�0x0d
			{
				if(res != 0x0a)
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = 0x0d;					//���϶�ʧ��0x0d
					USART_RX_STA++;
					if(res == 0x0d)	USART_RX_STA |= 0x4000;
					else
					{
						USART_RX_BUF[USART_RX_STA & 0x3fff] = res;				//������������
						USART_RX_STA++;
						USART_RX_STA &= 0xbfff;									//���0x0d��־
					}
				}
				else
				{
					if(USART_RX_STA&0x3fff)										//�ѽ��յ��ǿ�����
					{
						USART_RX_STA |= 0x8000;									//�������
						USART_RX_BUF[(USART_RX_STA&0x3fff)] = '\0'; 			//printfֹͣ
						
						(void)xTaskNotifyFromISR((TaskHandle_t )COM_TASK_HANDLER,			//��ϢĿ������
												 (uint32_t     )&USART_RX_BUF,				//��Ϣ����ָ��
												 (eNotifyAction)eSetValueWithOverwrite,		//���Ƿ�ʽ
												 (BaseType_t  *)xHigherPriorityTaskWoken);	//�Ƿ���������л�
						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);			//�����Ҫ�Ļ�����һ�������л�
					}
					else	
					{
						USART_RX_STA = 0;										//û����Ϣ��ֻ�л��з�
						memset(USART_RX_BUF,0x00,(USART_REC_LEN+1));			//��մ��ڻ�����
					}
				}
			}
			else																//û���յ�0x0d
			{	
				if(res == 0x0d)	USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;
					USART_RX_STA++;
					if(USART_RX_STA > (USART_REC_LEN - 1))						//�������ݴ������¿�ʼ
					{
						USART_RX_STA = 0;
						memset(USART_RX_BUF,0x00,(USART_REC_LEN+1));			//��մ��ڻ�����
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



