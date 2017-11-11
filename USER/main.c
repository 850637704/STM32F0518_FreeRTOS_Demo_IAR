
#include "includes.h"
/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void start_task(void *p_arg);
static void com_task(void *p_arg);
static void Queue_Send_Task( void *p_arg );
static void Queue_Receive_Task( void *p_arg );
#if (configGENERATE_RUN_TIME_STATS  == 1)
static void task_list_task(void *p_arg);
static void run_time_state_task(void *p_arg);
#endif /* configGENERATE_RUN_TIME_STATS */

/*-----------------------------------------------------------*/

static QueueHandle_t xQueue = NULL;												/* The queue used by both tasks. */
/*-----------------------------------------------------------*/

int main( void )
{
  	BspInit();
	
	xQueue = xQueueCreate( 1, sizeof( unsigned long ) );						/* Create the queue. */
	if( xQueue != NULL )
	{
		xTaskCreate((TaskFunction_t )start_task,            					/* The function that implements the task. */
					(const char    *)"Start",          							/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					(uint16_t       )START_TASK_STK_SIZE,        				/* The size of the stack to allocate to the task. */
					(void          *)NULL,                  					/* The parameter passed to the task - just to check the functionality. */
					(UBaseType_t    )START_TASK_PRIO,       					/* The priority assigned to the task. */
					(TaskHandle_t  *)NULL );   									/* The task handle is not required, so NULL is passed. */
		vTaskStartScheduler();													/* Start the tasks and timer running. */
	}
	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void start_task(void *p_arg)
{
	(void) p_arg;
	
    taskENTER_CRITICAL();
	{
		xTaskCreate((TaskFunction_t )com_task,
					(const char    *)"Com",
					(uint16_t       )COM_TASK_STK_SIZE,
					(void          *)NULL,
					(UBaseType_t    )COM_TASK_PRIO,
					(TaskHandle_t  *)&COM_TASK_HANDLER );
		xTaskCreate((TaskFunction_t )Queue_Receive_Task,
					(const char    *)"Rx",
					(uint16_t 	    )configMINIMAL_STACK_SIZE,
					(void		   *)NULL,
					(UBaseType_t	)tskIDLE_PRIORITY+2,
					(TaskHandle_t	)NULL);
		xTaskCreate((TaskFunction_t )Queue_Send_Task,
					(const char *	)"Tx",
					(uint16_t 		)configMINIMAL_STACK_SIZE,
					(void *			)NULL,
					(UBaseType_t	)tskIDLE_PRIORITY+1,
					(TaskHandle_t	)NULL);
#if configGENERATE_RUN_TIME_STATS  == 1
		xTaskCreate((TaskFunction_t )run_time_state_task,
					(const char *	)"Time",
					(uint16_t 		)RUN_TIME_TASK_STK_SIZE,
					(void *			)NULL,
					(UBaseType_t	)RUN_TIME_TASK_PRIO,
					(TaskHandle_t	)&RUN_TIME_TASK_HANDLER);
		xTaskCreate((TaskFunction_t )task_list_task,								
					(const char *	)"State",
					(uint16_t 		)TASK_LIST_TASK_STK_SIZE,
					(void *			)NULL,
					(UBaseType_t	)TASK_LIST_TASK_PRIO,
					(TaskHandle_t	)&TASK_LIST_TASK_HANDLER);
		
		vTaskSuspend(RUN_TIME_TASK_HANDLER);									// π“∆»ŒŒÒ
		vTaskSuspend(TASK_LIST_TASK_HANDLER);									// π“∆»ŒŒÒ
#endif /* configGENERATE_RUN_TIME_STATS */
		vTaskDelete(NULL);														// …æ≥˝»ŒŒÒ
	}	
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void com_task(void *p_arg)
{
	BaseType_t err;
	uint32_t Msg;
	(void) p_arg;
	
	for(;;)
	{																	
		err = xTaskNotifyWait((uint32_t   ) 0x00,
							  (uint32_t   ) ULONG_MAX,
							  (uint32_t  *) &Msg,
							  (TickType_t ) portMAX_DELAY);
		if(err == pdTRUE)
		{
			taskENTER_CRITICAL();
			{	
#if (configGENERATE_RUN_TIME_STATS  == 1)
				if(((char *)Msg)[0] == 0x31&&(USART_RX_STA&0x3fff) == 1)
					vTaskResume(RUN_TIME_TASK_HANDLER);
				else if(((char *)Msg)[0] == 0x32&&(USART_RX_STA&0x3fff) == 1)
					vTaskResume(TASK_LIST_TASK_HANDLER);
				else
#endif /* configGENERATE_RUN_TIME_STATS */
				  printf("%s\r\n",(uint8_t *)Msg);
			}
			taskEXIT_CRITICAL();
			USART_RX_STA = (uint16_t)0;
		}
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
/*-----------------------------------------------------------*/

#if (configGENERATE_RUN_TIME_STATS  == 1)

	static void run_time_state_task(void *p_arg)
	{
		char * pStatsMsg = NULL;
		(void) p_arg;
		
		for(;;)
		{	
			taskENTER_CRITICAL();
			{
				pStatsMsg = pvPortMalloc( uxTaskGetNumberOfTasks() * sizeof( TaskStatus_t ) );
				if(pStatsMsg != NULL)
				{
					vTaskGetRunTimeStats(pStatsMsg);
					printf("Name\tAbs Time\t%%Time\r\n");
					printf("%s\r\n",(char *)pStatsMsg);
					vPortFree(pStatsMsg);
				}
				else
					printf("run_time_state_task…Í«Îƒ⁄¥Ê ß∞‹\r\n");
			}
			taskEXIT_CRITICAL();
			vTaskSuspend(RUN_TIME_TASK_HANDLER);
		}
	}

#endif /* configGENERATE_RUN_TIME_STATS */
/*-----------------------------------------------------------*/

#if (configGENERATE_RUN_TIME_STATS  == 1)

	static void task_list_task(void *p_arg)
	{
		char * pStatsMsg  = NULL ;
		(void) p_arg;
		
		for(;;)
		{
			taskENTER_CRITICAL();
			{
				pStatsMsg = pvPortMalloc(uxTaskGetNumberOfTasks() * sizeof( TaskStatus_t ) );
				if(pStatsMsg != NULL)
				{
					vTaskList(pStatsMsg);
					printf("Name\tState\tPrio\tStack\tNum\r\n");
					printf("%s\r\n",(char *)pStatsMsg);
//					printf("»ŒŒÒ◊¥Ã¨:r-‘À––\tR-æÕ–˜\tB-◊Ë»˚\tS-π“∆\tD-…æ≥˝\r\n");
					vPortFree(pStatsMsg);
				}
				else
					printf("task_list_task…Í«Îƒ⁄¥Ê ß∞‹\r\n");
			}
			taskEXIT_CRITICAL();
			vTaskSuspend(TASK_LIST_TASK_HANDLER);
		}
	}

#endif /* configGENERATE_RUN_TIME_STATS */
/*-----------------------------------------------------------*/

static void Queue_Receive_Task( void *p_arg )
{
	TickType_t xNextWakeTime;
	const unsigned long ulValueToSend = 100UL;
	(void) p_arg;
	
	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, 250 / portTICK_PERIOD_MS );
		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */
		xQueueSend( xQueue, &ulValueToSend, 0U );
	}
}
/*-----------------------------------------------------------*/

static void Queue_Send_Task( void *p_arg )
{
	unsigned long ulReceivedValue;
	(void) p_arg;
	
	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

		/*  To get here something must have been received from the queue, but
		is it the expected value?  If it is, toggle the LED. */
		if( ulReceivedValue == 100UL )
		{
			taskENTER_CRITICAL();
			{
				GPIOC->ODR ^= GPIO_Pin_13;
			}
			taskEXIT_CRITICAL();
			ulReceivedValue = 0U;
		}
	}
}
/*-----------------------------------------------------------*/

#if (configUSE_MALLOC_FAILED_HOOK == 1)

	void vApplicationMallocFailedHook( void )
	{
		/* vApplicationMallocFailedHook() will only be called if
		configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
		function that will get called if a call to pvPortMalloc() fails.
		pvPortMalloc() is called internally by the kernel whenever a task, queue,
		timer or semaphore is created.  It is also called by various parts of the
		demo application.  If heap_1.c or heap_2.c are used, then the size of the
		heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
		FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
		to query the size of free heap space that remains (although it does not
		provide information on how the remaining heap might be fragmented). */
		taskDISABLE_INTERRUPTS();
		printf("ƒ⁄¥Ê…Í«Î ß∞‹\r\n");
		for( ;; );
	}

#endif /* configUSE_MALLOC_FAILED_HOOK */
/*-----------------------------------------------------------*/

#if (configCHECK_FOR_STACK_OVERFLOW == 1)

	void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
	{
		( void ) pcTaskName;
		( void ) pxTask;

		/* Run time stack overflow checking is performed if
		configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
		function is called if a stack overflow is detected. */
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}

#endif
/*-----------------------------------------------------------*/

#if (configUSE_TICK_HOOK == 1)

	void vApplicationTickHook( void )
	{
		/* This function will be called by each tick interrupt if
		configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
		added here, but the tick hook is called from an interrupt context, so
		code must not attempt to block, and only the interrupt safe FreeRTOS API
		functions can be used (those that end in FromISR()). */
	}

#endif /* configUSE_TICK_HOOK */
/*-----------------------------------------------------------*/

#if (configUSE_IDLE_HOOK == 1)

	void vApplicationIdleHook( void )
	{
		/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
		to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
		task.  It is essential that code added to this hook function never attempts
		to block in any way (for example, call xQueueReceive() with a block time
		specified, or call vTaskDelay()).  If the application makes use of the
		vTaskDelete() API function (as this demo application does) then it is also
		important that vApplicationIdleHook() is permitted to return to its calling
		function, because it is the responsibility of the idle task to clean up
		memory allocated by the kernel to any task that has since been deleted. */
	}

#endif /* configUSE_IDLE_HOOK */
/*-----------------------------------------------------------*/

#ifdef USE_FULL_ASSERT 

	void assert_failed(uint8_t* file, uint32_t line)
	{ 
		printf("parameters error: file %s on line %d\r\n", file, line);
		for(;;);
	}

#endif /* USE_FULL_ASSERT */
/*-----------------------------------------------------------*/

