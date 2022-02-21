/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   FreeRTOS V9.0.0  + STM32 �̼�������
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 ȫϵ�п����� 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* ������Ӳ��bspͷ�ļ� */
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_modbus_usart.h"
#include "bsp_key.h"
#include "ff.h"
#include "./FatFs_Test/FatFs_test.h"

/* ��׼��ͷ�ļ� */
#include <string.h>
/**************************** ������ ********************************/
/* 
 * ��������һ��ָ�룬����ָ��һ�����񣬵����񴴽���֮�����;�����һ��������
 * �Ժ�����Ҫ��������������Ҫͨ�������������������������������Լ�����ô
 * ����������ΪNULL��
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* ���������� */
static TaskHandle_t Test_Task_Handle = NULL;/* LED������ */
static TaskHandle_t MODBUS_Task_Handle = NULL;/* KEY������ */
static TaskHandle_t Uart_Task_Handle = NULL;/* KEY������ */

/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */
SemaphoreHandle_t DEBUG_BinarySem_Handle =NULL;
SemaphoreHandle_t MODBUS_BinarySem_Handle =NULL;


/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
 
extern char Debug_Usart_Rx_Buf[DEBUG_USART_RBUFF_SIZE];
extern char MODBUS1_Usart_Rx_Buf[MODBUS1_USART_RBUFF_SIZE];

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);/* ���ڴ������� */

static void Test_Task(void* pvParameters);/* Test_Task����ʵ�� */
static void MODBUS_Task(void* pvParameters);/* MODBUS_Task����ʵ�� */
static void Uart_Task(void* pvParameters);/* KEY_Task����ʵ�� */

static void BSP_Init(void);/* ���ڳ�ʼ�����������Դ */

/*****************************************************************
  * @brief  ������
  * @param  ��
  * @retval ��
  * @note   ��һ����������Ӳ����ʼ�� 
            �ڶ���������APPӦ������
            ������������FreeRTOS����ʼ���������
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
  /* ������Ӳ����ʼ�� */
  BSP_Init();
  
  printf("RTOS_Init\n\n");
  
   /* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
}


/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */

	taskENTER_CRITICAL();           //�����ٽ���
  
	  /* ���� DEBUG_BinarySem_Handle */
	DEBUG_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != DEBUG_BinarySem_Handle)
	printf("DEBUG_BinarySem_Handle��ֵ�ź��������ɹ�!\n");
  
	  /* ���� BinarySem */
	MODBUS_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != MODBUS_BinarySem_Handle)
	printf("MODBUS_BinarySem_Handle��ֵ�ź��������ɹ�!\n");
	
  /* ����Test_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Test_Task, /* ������ں��� */
						(const char*    )"Test_Task",/* �������� */
						(uint16_t       )512,   /* ����ջ��С */
						(void*          )NULL,	/* ������ں������� */
						(UBaseType_t    )2,	    /* ��������ȼ� */
						(TaskHandle_t*  )&Test_Task_Handle);/* ������ƿ�ָ�� */
	if(pdPASS == xReturn)
	printf("����Test_Task����ɹ�!\r\n");
	/* ����Uart_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Uart_Task,  /* ������ں��� */
						(const char*    )"Uart_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )3, /* ��������ȼ� */
						(TaskHandle_t*  )&Uart_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����Uart_Task����ɹ�!\r\n");
	/* ����MODBUS_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )MODBUS_Task,  /* ������ں��� */
						(const char*    )"MODBUS_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )4, /* ��������ȼ� */
						(TaskHandle_t*  )&MODBUS_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����MODBUS_Task����ɹ�!\r\n");

	vTaskDelete(AppTaskCreate_Handle); //ɾ��AppTaskCreate����

	taskEXIT_CRITICAL();            //�˳��ٽ���
}



/**********************************************************************
  * @ ������  �� Test_Task
  * @ ����˵���� Test_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Test_Task(void* parameter)
{	 
	/* �ļ�ϵͳ��ʼ�� */
	FileSystem_Init();
  /* �ļ�ϵͳ��д���� */
  FileSystem_Test();
  while (1)
  {
    LED1_ON;
    //printf("Test_Task Running,LED1_ON\r\n");
    vTaskDelay(500);   /* ��ʱ500��tick */
    FileSystem_Test();
    LED1_OFF;     
    //printf("Test_Task Running,LED1_OFF\r\n");
    vTaskDelay(500);   /* ��ʱ500��tick */
  }
}

/**********************************************************************
  * @ ������  �� LED_Task
  * @ ����˵���� LED_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void Uart_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	while (1)
	{
		//��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(DEBUG_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		if(pdPASS == xReturn)
		{
			LED2_TOGGLE;
			printf("�յ�����:%s\n",Debug_Usart_Rx_Buf);
			
			
			
			
			memset(Debug_Usart_Rx_Buf,0,DEBUG_USART_RBUFF_SIZE);/* ���� */
		}
	}
}

/**********************************************************************
  * @ ������  �� Test_Task
  * @ ����˵���� Test_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void MODBUS_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  while (1)
  {
    //��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(MODBUS_BinarySem_Handle,/* ��ֵ�ź������ */
                              portMAX_DELAY); /* �ȴ�ʱ�� */
    if(pdPASS == xReturn)
    {
      LED3_TOGGLE;
      printf("�յ�����:%s\n",MODBUS1_Usart_Rx_Buf);
      memset(MODBUS1_Usart_Rx_Buf,0,DEBUG_USART_RBUFF_SIZE);/* ���� */
    }
  }
}


/***********************************************************************
  * @ ������  �� BSP_Init
  * @ ����˵���� �弶�����ʼ�������а����ϵĳ�ʼ�����ɷ��������������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  *********************************************************************/
static void BSP_Init(void)
{
	/*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��������ȼ����飬ǧ��Ҫ�ٷ��飬�мɡ�
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* LED ��ʼ�� */
	LED_GPIO_Config();

	/* DMA��ʼ��	*/
	Debug_DMA_Config();
	/* ���ڳ�ʼ��	*/
	Debug_USART_Config();
  
	/* DMA��ʼ��	*/
	MODBUS1_DMA_Config();
	/* ���ڳ�ʼ��	*/
	MODBUS1_USART_Config();
  
	/* ������ʼ��	*/
	Key_GPIO_Config();

	printf("Init finish\r\n");
}

/********************************END OF FILE****************************/
