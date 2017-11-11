
#ifndef __APP_CFG_H
#define __APP_CFG_H

/*------------------------------------------------------------
                          �������ȼ�
------------------------------------------------------------*/
#define START_TASK_PRIO						0x00								//START ���� ���ȼ�
#define COM_TASK_PRIO						0x03								//COM   ���� ���ȼ�
#define RUN_TIME_TASK_PRIO              	0x04								//LIST  ���� ���ȼ�
#define TASK_LIST_TASK_PRIO             	0x05
#define LED_TASK_PRIO						0x06								//LED   ���� ���ȼ� 
#define KEY_TASK_PRIO						0x07 								//KEY   ���� ���ȼ�

/*------------------------------------------------------------
                         �����ջ����
------------------------------------------------------------*/
#define START_TASK_STK_SIZE					80									//START ���� ��ջ����
#define COM_TASK_STK_SIZE					100									//COM   ���� ��ջ����
#define LED_TASK_STK_SIZE					30									//LED   ���� ��ջ����
#define KEY_TASK_STK_SIZE					50									//KEY  ���� ��ջ����
#define RUN_TIME_TASK_STK_SIZE				100									//LIST   ���� ��ջ����
#define TASK_LIST_TASK_STK_SIZE				100
#define OLED_TASK_STK_SIZE					150

/*------------------------------------------------------------
                            ������
------------------------------------------------------------*/
//TaskHandle_t START_TASK_HANDLER = NULL;											//START ���� ���
TaskHandle_t COM_TASK_HANDLER = NULL;											//COM   ���� ���
TaskHandle_t RUN_TIME_TASK_HANDLER = NULL;										//KEY   ���� ���
TaskHandle_t TASK_LIST_TASK_HANDLER = NULL;
TaskHandle_t QUEUE_SEND_TASK_HANDLER = NULL;
TaskHandle_t QUEUE_RECEIVE_TASK_HANDLER = NULL;

/*------------------------------------------------------------
                        ֧�־�̬����
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


