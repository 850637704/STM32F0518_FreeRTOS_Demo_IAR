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
/*                        FreeRTOS基础配置选项                                */
/******************************************************************************/   
#define configUSE_PREEMPTION						1							// 1、使用抢占式内核，0、使用协程
#define configUSE_TIME_SLICING						1							// 1、时间片调度
#define configUSE_PORT_OPTIMISED_TASK_SELECTION		0							// 1、启用特殊方法来选择下一个要运行的任务
																				// 一般是硬件计算迁到零指令，如果所使用的
																				// MCU 没有这些硬件指令的话此宏应该设置为 0
#define configUSE_16_BIT_TICKS						0							// 系统节拍计数器变量类型
																				// 1、表示 16 位无符号整型 0、表示 32 位无符号整型
#define configIDLE_SHOULD_YIELD						0							// 1、空闲任务放弃 CPU 使用权给其他同优先级的用户任务

#define configUSE_MUTEXES							0							// 互斥型信号量
#define configUSE_RECURSIVE_MUTEXES					0							// 使用递归互斥信号量
#define configUSE_APPLICATION_TASK_TAG				0							//
#define configUSE_COUNTING_SEMAPHORES				0							// 使用计数器信号量

#define configENABLE_BACKWARD_COMPATIBILITY 		0							// 为兼容版本 V8.0.0 之前的代码的函数、变量名称
/******************************************************************************/
/*                        FreeRTOS钩子函数相关配置	           			      */
/******************************************************************************/
#define configUSE_IDLE_HOOK							0							// 1、使用空闲任务钩子;0、不使用空闲任务钩子
#define configUSE_TICK_HOOK							0							// 1、使用时间片钩子;0、不使用时间片钩子
/******************************************************************************/
/*                        FreeRTOS低功耗相关配置		           		      */
/******************************************************************************/
#define configUSE_TICKLESS_IDLE						0                       	// 1、启用低功耗模式
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP   	2                      		// 进入低功耗的最小节拍数

#define configUSE_QUEUE_SETS						0                       	// 启用队列
#define configQUEUE_REGISTRY_SIZE					8							// 不为 0 时表示启用队列记录，具体的值是可以记录的队列和信号量的最大值

#define configCPU_CLOCK_HZ							( SystemCoreClock )			// CPU 频率
#define configTICK_RATE_HZ							( ( TickType_t ) 1000 )		// 时钟节拍频率
#define configMAX_PRIORITIES						( 10 )						// 可使用的最大优先级
#define configMINIMAL_STACK_SIZE					( ( unsigned short ) 60 )	// 空闲任务使用的堆栈大小
#define configMAX_TASK_NAME_LEN						( 8 )						// 任务名称长度
/******************************************************************************/
/*                          FreeRTOS内存申请相关配置                       	  */
/******************************************************************************/
#define configSUPPORT_STATIC_ALLOCATION				0							// 支持静态内存申请
#define configSUPPORT_DYNAMIC_ALLOCATION        	1                       	// 支持动态内存申请
#define configTOTAL_HEAP_SIZE						( ( size_t ) (4 * 1024 ) )	// 系统堆栈大小
#define configUSE_MALLOC_FAILED_HOOK				1							// 使用内存申请失败钩子函数
/******************************************************************************/
/*                         FreeRTOS协程相关配置		                  		  */
/******************************************************************************/
#define configUSE_CO_ROUTINES 						0							// 启用协程，启用协程以后必须添加文件 croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES 			2							// 协程的有效优先级数目
/******************************************************************************/
/*                       FreeRTOS软件定时器相关配置		                  	  */
/******************************************************************************/
#define configUSE_TIMERS							0							// 启用软件定时器
#define configTIMER_TASK_PRIORITY					2							// 软件定时器优先级
#define configTIMER_QUEUE_LENGTH					5							// 软件定时器队列长度
#define configTIMER_TASK_STACK_DEPTH				80							// 软件定时器堆栈大小
/******************************************************************************/
/*                        FreeRTOS调试跟踪相关配置	           			      */
/******************************************************************************/
#define configGENERATE_RUN_TIME_STATS				1							// 系统运行时间相关
	
#if ( configGENERATE_RUN_TIME_STATS == 1 )
#define portGET_RUN_TIME_COUNTER_VALUE() 			RunTimeCounterValue
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 	( RunTimeCounterValue = 0UL )
#endif /* configGENERATE_RUN_TIME_STATS */
	
#define configUSE_STATS_FORMATTING_FUNCTIONS		1							// 编译 vTaskList() 和 vTaskGetRunTimeStats() 函数
#define configUSE_TRACE_FACILITY					1							// 可视化跟踪调试，堆栈将被‘0xa5’填充
#define configCHECK_FOR_STACK_OVERFLOW				1							// 大于 0 时启用堆栈溢出检测功能，如果使用此功能
																				// 用户必须提供一个栈溢出钩子函数，如果使用的话
																				// 此值可以为 1 或 2，因为有两种检测方法
/******************************************************************************/
/*                       FreeRTOS可选函数相关配置		                  	  */
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
/*                          FreeRTOS and STM32 STD断言			              */
/******************************************************************************/
#if ( USE_FULL_ASSERT != 0 )                                            		// USE_FULL_ASSERT 在 stm32f0xx_conf.h 中定义
	#define configASSERT(x) assert_param(x)										// FreeRTOS 使用 ST 标准库断言文件
#endif /* USE_FULL_ASSERT */
/******************************************************************************/
/*                       FreeRTOS中断服务函数相关配置                         */
/******************************************************************************/
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define vPortSVCHandler 							SVC_Handler
#define xPortPendSVHandler 							PendSV_Handler
#define xPortSysTickHandler 						SysTick_Handler
/******************************************************************************/
/*                        FreeRTOS低功耗管理相关配置              	    	  */
/******************************************************************************/
//extern void PreSleepProcessing(uint32_t ulExpectedIdleTime);
//extern void PostSleepProcessing(uint32_t ulExpectedIdleTime);
//
//#define configPRE_SLEEP_PROCESSING				PreSleepProcessing				//进入低功耗模式前要做的处理
//#define configPOST_SLEEP_PROCESSING				PostSleepProcessing				//退出低功耗模式前要做的处理

#endif /* FREERTOS_CONFIG_H */

