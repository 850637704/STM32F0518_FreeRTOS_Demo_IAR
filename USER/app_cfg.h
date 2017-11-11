
#ifndef __APP_CFG_H
#define __APP_CFG_H

/*------------------------------------------------------------
                          任务优先级
------------------------------------------------------------*/
#define START_TASK_PRIO						0x00								//START 任务 优先级
#define COM_TASK_PRIO						0x03								//COM   任务 优先级
#define RUN_TIME_TASK_PRIO              	0x04								//LIST  任务 优先级
#define TASK_LIST_TASK_PRIO             	0x05
#define LED_TASK_PRIO						0x06								//LED   任务 优先级 
#define KEY_TASK_PRIO						0x07 								//KEY   任务 优先级

/*------------------------------------------------------------
                         任务堆栈长度
------------------------------------------------------------*/
#define START_TASK_STK_SIZE					80									//START 任务 堆栈长度
#define COM_TASK_STK_SIZE					100									//COM   任务 堆栈长度
#define LED_TASK_STK_SIZE					30									//LED   任务 堆栈长度
#define KEY_TASK_STK_SIZE					50									//KEY  任务 堆栈长度
#define RUN_TIME_TASK_STK_SIZE				100									//LIST   任务 堆栈长度
#define TASK_LIST_TASK_STK_SIZE				100
#define OLED_TASK_STK_SIZE					150

/*------------------------------------------------------------
                            任务句柄
------------------------------------------------------------*/
//TaskHandle_t START_TASK_HANDLER = NULL;											//START 任务 句柄
TaskHandle_t COM_TASK_HANDLER = NULL;											//COM   任务 句柄
TaskHandle_t RUN_TIME_TASK_HANDLER = NULL;										//KEY   任务 句柄
TaskHandle_t TASK_LIST_TASK_HANDLER = NULL;
TaskHandle_t QUEUE_SEND_TASK_HANDLER = NULL;
TaskHandle_t QUEUE_RECEIVE_TASK_HANDLER = NULL;

/*------------------------------------------------------------
                        支持静态创建
------------------------------------------------------------*/
#if configSUPPORT_STATIC_ALLOCATION == 1
	static StaticTask_t Idle_Task_Tcb;
	static StackType_t idle_task_stk[configMINIMAL_STACK_SIZE];
	void vApplicationGetIdleTaskMemory(StaticTask_t **xIDLTaskTcb, StackType_t ** IDLTaskStk, uint32_t *IDLTaskStkSize);
	static StaticTask_t Timer_Task_Tcb;
	static StackType_t timer_task_stk[configTIMER_TASK_STACK_DEPTH];
	void vApplicationGetTimerTaskMemory(StaticTask_t **xTIMERTaskTcb, StackType_t ** TIMERTaskStk, uint32_t *TIMERTaskStkSize);
#endif

#endif


