/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#ifdef __ICCARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
	extern volatile unsigned long long RunTimeCounterValue;
#endif
/******************************************************************************/
/*                        FreeRTOS��������ѡ��                                */
/******************************************************************************/   
#define configUSE_PREEMPTION						1							// 1��ʹ����ռʽ�ںˣ�0��ʹ��Э��
#define configUSE_TIME_SLICING						1							// 1��ʱ��Ƭ����
#define configUSE_PORT_OPTIMISED_TASK_SELECTION		0							// 1���������ⷽ����ѡ����һ��Ҫ���е�����
																				// һ����Ӳ������Ǩ����ָ������ʹ�õ�
																				// MCU û����ЩӲ��ָ��Ļ��˺�Ӧ������Ϊ 0
#define configUSE_16_BIT_TICKS						0							// ϵͳ���ļ�������������
																				// 1����ʾ 16 λ�޷������� 0����ʾ 32 λ�޷�������
#define configIDLE_SHOULD_YIELD						0							// 1������������� CPU ʹ��Ȩ������ͬ���ȼ����û�����

#define configUSE_MUTEXES							0							// �������ź���
#define configUSE_RECURSIVE_MUTEXES					0							// ʹ�õݹ黥���ź���
#define configUSE_APPLICATION_TASK_TAG				0							//
#define configUSE_COUNTING_SEMAPHORES				0							// ʹ�ü������ź���

#define configENABLE_BACKWARD_COMPATIBILITY 		0							// Ϊ���ݰ汾 V8.0.0 ֮ǰ�Ĵ���ĺ�������������
/******************************************************************************/
/*                        FreeRTOS���Ӻ����������	           			      */
/******************************************************************************/
#define configUSE_IDLE_HOOK							0							// 1��ʹ�ÿ���������;0����ʹ�ÿ���������
#define configUSE_TICK_HOOK							0							// 1��ʹ��ʱ��Ƭ����;0����ʹ��ʱ��Ƭ����
/******************************************************************************/
/*                        FreeRTOS�͹����������		           		      */
/******************************************************************************/
#define configUSE_TICKLESS_IDLE						0                       	// 1�����õ͹���ģʽ
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP   	2                      		// ����͹��ĵ���С������

#define configUSE_QUEUE_SETS						0                       	// ���ö���
#define configQUEUE_REGISTRY_SIZE					8							// ��Ϊ 0 ʱ��ʾ���ö��м�¼�������ֵ�ǿ��Լ�¼�Ķ��к��ź��������ֵ

#define configCPU_CLOCK_HZ							( SystemCoreClock )			// CPU Ƶ��
#define configTICK_RATE_HZ							( ( TickType_t ) 1000 )		// ʱ�ӽ���Ƶ��
#define configMAX_PRIORITIES						( 10 )						// ��ʹ�õ�������ȼ�
#define configMINIMAL_STACK_SIZE					( ( unsigned short ) 60 )	// ��������ʹ�õĶ�ջ��С
#define configMAX_TASK_NAME_LEN						( 8 )						// �������Ƴ���
/******************************************************************************/
/*                          FreeRTOS�ڴ������������                       	  */
/******************************************************************************/
#define configSUPPORT_STATIC_ALLOCATION				0							// ֧�־�̬�ڴ�����
#define configSUPPORT_DYNAMIC_ALLOCATION        	1                       	// ֧�ֶ�̬�ڴ�����
#define configTOTAL_HEAP_SIZE						( ( size_t ) (4 * 1024 ) )	// ϵͳ��ջ��С
#define configUSE_MALLOC_FAILED_HOOK				1							// ʹ���ڴ�����ʧ�ܹ��Ӻ���
/******************************************************************************/
/*                         FreeRTOSЭ���������		                  		  */
/******************************************************************************/
#define configUSE_CO_ROUTINES 						0							// ����Э�̣�����Э���Ժ��������ļ� croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES 			2							// Э�̵���Ч���ȼ���Ŀ
/******************************************************************************/
/*                       FreeRTOS�����ʱ���������		                  	  */
/******************************************************************************/
#define configUSE_TIMERS							0							// ���������ʱ��
#define configTIMER_TASK_PRIORITY					2							// �����ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH					5							// �����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH				80							// �����ʱ����ջ��С
/******************************************************************************/
/*                        FreeRTOS���Ը����������	           			      */
/******************************************************************************/
#define configGENERATE_RUN_TIME_STATS				1							// ϵͳ����ʱ�����
	
#if ( configGENERATE_RUN_TIME_STATS == 1 )
#define portGET_RUN_TIME_COUNTER_VALUE() 			RunTimeCounterValue
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 	( RunTimeCounterValue = 0UL )
#endif /* configGENERATE_RUN_TIME_STATS */
	
#define configUSE_STATS_FORMATTING_FUNCTIONS		1							// ���� vTaskList() �� vTaskGetRunTimeStats() ����
#define configUSE_TRACE_FACILITY					1							// ���ӻ����ٵ��ԣ���ջ������0xa5�����
#define configCHECK_FOR_STACK_OVERFLOW				1							// ���� 0 ʱ���ö�ջ�����⹦�ܣ����ʹ�ô˹���
																				// �û������ṩһ��ջ������Ӻ��������ʹ�õĻ�
																				// ��ֵ����Ϊ 1 �� 2����Ϊ�����ּ�ⷽ��
/******************************************************************************/
/*                       FreeRTOS��ѡ�����������		                  	  */
/******************************************************************************/
#define INCLUDE_xTaskGetSchedulerState          	1 
#define INCLUDE_vTaskPrioritySet					0
#define INCLUDE_uxTaskPriorityGet					0
#define INCLUDE_vTaskDelete							1
#define INCLUDE_vTaskCleanUpResources				1
#define INCLUDE_vTaskSuspend						1
#define INCLUDE_vTaskDelayUntil						1
#define INCLUDE_vTaskDelay							1
#define INCLUDE_eTaskGetState			        	0
#define INCLUDE_xTimerPendFunctionCall	        	0  
/******************************************************************************/
/*                          FreeRTOS and STM32 STD����			              */
/******************************************************************************/
#if ( USE_FULL_ASSERT != 0 )                                            		// USE_FULL_ASSERT �� stm32f0xx_conf.h �ж���
	#define configASSERT(x) assert_param(x)										// FreeRTOS ʹ�� ST ��׼������ļ�
#endif /* USE_FULL_ASSERT */
/******************************************************************************/
/*                       FreeRTOS�жϷ������������                         */
/******************************************************************************/
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define vPortSVCHandler 							SVC_Handler
#define xPortPendSVHandler 							PendSV_Handler
#define xPortSysTickHandler 						SysTick_Handler
/******************************************************************************/
/*                        FreeRTOS�͹��Ĺ����������              	    	  */
/******************************************************************************/
//extern void PreSleepProcessing(uint32_t ulExpectedIdleTime);
//extern void PostSleepProcessing(uint32_t ulExpectedIdleTime);
//
//#define configPRE_SLEEP_PROCESSING				PreSleepProcessing				//����͹���ģʽǰҪ���Ĵ���
//#define configPOST_SLEEP_PROCESSING				PostSleepProcessing				//�˳��͹���ģʽǰҪ���Ĵ���

#endif /* FREERTOS_CONFIG_H */

