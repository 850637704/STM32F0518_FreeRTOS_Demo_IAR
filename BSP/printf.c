

#include "printf.h"
/*
 *******************************************************************************
 * 函 数 名: putchar
 * 功能说明: 重定义 putchar 函数， 这样可以使用printf函数从串口2打印输出
 * 形    参: 等待发送的字符
 * 返 回 值: 返回已发送的字符
 *******************************************************************************
 */
PUTCHAR_PROTOTYPE
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}

/*
 *******************************************************************************
 * 函 数 名: getchar
 * 功能说明: 重定义C库中的 getchar 函数,这样可以使用scanff函数从串口1输入数据
* 形    参: 无
* 返 回 值: 返回已读到的字符
********************************************************************************
 */
GETCHAR_PROTOTYPE
{
	#ifdef _COSMIC_
		char c = 0;
	#else
		int c = 0;
	#endif

	/* 等待新数据到达  */
	while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);

	/* 读取数据寄存器 */
	c = UART1_ReceiveData8();

	return (c);
}

/****************** 安富莱电子 www.armfly.com (END OF FILE) *******************/
