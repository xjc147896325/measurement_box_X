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
#include "bsp_hmi_usart.h"
#include "bsp_key.h"
#include "ff.h"
#include "./FatFs_Test/FatFs_test.h"

/* ��׼��ͷ�ļ� */
#include <string.h>
#include <stdio.h>

/* CRC-16 MODBUS */
#include "CRC16.h"
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
static TaskHandle_t HMI_Task_Handle = NULL;/* KEY������ */

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
SemaphoreHandle_t DEBUG_BinarySem_Handle = NULL;
SemaphoreHandle_t MODBUS_BinarySem_Handle = NULL;
SemaphoreHandle_t SD_BinarySem_Handle = NULL;
SemaphoreHandle_t HMI_BinarySem_Handle = NULL;
SemaphoreHandle_t START_BinarySem_Handle = NULL;

/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */
 
extern uint8_t Debug_Usart_Rx_Buf[DEBUG_USART_RBUFF_SIZE];
extern uint8_t MODBUS1_Usart_Rx_Buf[MODBUS1_USART_RBUFF_SIZE];
extern uint8_t HMI_Usart_Rx_Buf[HMI_USART_RBUFF_SIZE];

uint8_t MODBUS1[8][8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A,
						 0x01, 0x03, 0x00, 0x00, 0x01, 0x01, 0x85, 0x9A,
						 0x01, 0x03, 0x00, 0x00, 0x02, 0x01, 0x85, 0x6A,
						 0x01, 0x03, 0x00, 0x00, 0x03, 0x01, 0x84, 0xFA,
						 0x01, 0x03, 0x00, 0x00, 0x04, 0x01, 0x86, 0xCA,
						 0x01, 0x03, 0x00, 0x00, 0x05, 0x01, 0x87, 0x5A,
						 0x01, 0x03, 0x00, 0x00, 0x06, 0x01, 0x87, 0xAA,
						 0x01, 0x03, 0x00, 0x00, 0x07, 0x01, 0x86, 0x3A}; //վ�� 01 ������ 03 ��ʼ��ַ 0000 �Ĵ������� 0001 CRC 840A

/*---------------- ------------------*/
uint8_t MODBUS2[8][8] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39,
						 0x02, 0x03, 0x00, 0x00, 0x01, 0x01, 0x85, 0xA9,
						 0x02, 0x03, 0x00, 0x00, 0x02, 0x01, 0x85, 0x59,
						 0x02, 0x03, 0x00, 0x00, 0x03, 0x01, 0x84, 0xC9,
						 0x02, 0x03, 0x00, 0x00, 0x04, 0x01, 0x86, 0xF9,
						 0x02, 0x03, 0x00, 0x00, 0x05, 0x01, 0x87, 0xC8,
						 0x02, 0x03, 0x00, 0x00, 0x06, 0x01, 0x87, 0x99,
						 0x02, 0x03, 0x00, 0x00, 0x07, 0x01, 0x86, 0x09}; //վ�� 02 ������ 03 ��ʼ��ַ 0000 �Ĵ������� 0001 CRC 840A

uint8_t MODBUS3[8][8] = {0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x85, 0xE8,
						 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x84, 0x78,
						 0x03, 0x03, 0x00, 0x00, 0x02, 0x01, 0x84, 0x88,
						 0x03, 0x03, 0x00, 0x00, 0x03, 0x01, 0x85, 0x18,
						 0x03, 0x03, 0x00, 0x00, 0x04, 0x01, 0x87, 0x28,
						 0x03, 0x03, 0x00, 0x00, 0x05, 0x01, 0x86, 0xB8,
						 0x03, 0x03, 0x00, 0x00, 0x06, 0x01, 0x86, 0x48,
						 0x03, 0x03, 0x00, 0x00, 0x07, 0x01, 0x87, 0xD8}; //վ�� 03 ������ 03 ��ʼ��ַ 0000 �Ĵ������� 0001 CRC 840A
/*-------------------------------*/
uint16_t channel_data_buf[3][50] = {0};
char ascii_buf[100] = {0};
char file_name[100] = {0};
char text1[] = "\r\n��һ�飺\r\n";
char text2[] = "\r\n�ڶ��飺\r\n";
char text3[] = "\r\n�����飺\r\n";

int8_t channel_num = 0;
uint8_t display = 0;
uint8_t save_flag = 0;
uint8_t file_num = 0;
						 
/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void AppTaskCreate(void);/* ���ڴ������� */

static void Test_Task(void* pvParameters);/* Test_Task����ʵ�� */
static void MODBUS_Task(void* pvParameters);/* MODBUS_Task����ʵ�� */
static void Uart_Task(void* pvParameters);/* KEY_Task����ʵ�� */
static void HMI_Task(void* pvParameters);/* KEY_Task����ʵ�� */

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
  
	  /* ���� BinarySem */
	SD_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != SD_BinarySem_Handle)
	printf("SD_BinarySem_Handle��ֵ�ź��������ɹ�!\n");
	
	  /* ���� BinarySem */
	HMI_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != HMI_BinarySem_Handle)
	printf("HMI_BinarySem_Handle��ֵ�ź��������ɹ�!\n");
	
	  /* ���� BinarySem */
	START_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != START_BinarySem_Handle)
	printf("START_BinarySem_Handle��ֵ�ź��������ɹ�!\n");
	
	/* ����Test_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )Test_Task, /* ������ں��� */
						(const char*    )"Test_Task",/* �������� */
						(uint16_t       )512,   /* ����ջ��С */
						(void*          )NULL,	/* ������ں������� */
						(UBaseType_t    )5,	    /* ��������ȼ� */
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
	
	/* ����MODBUS_Task���� */
	xReturn = xTaskCreate((TaskFunction_t )HMI_Task,  /* ������ں��� */
						(const char*    )"HMI_Task",/* �������� */
						(uint16_t       )512,  /* ����ջ��С */
						(void*          )NULL,/* ������ں������� */
						(UBaseType_t    )6, /* ��������ȼ� */
						(TaskHandle_t*  )&HMI_Task_Handle);/* ������ƿ�ָ�� */ 
	if(pdPASS == xReturn)
	printf("����HMI_Task����ɹ�!\r\n");

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
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	FRESULT res_sd;                /* �ļ�������� */
	FIL fnew;													/* �ļ����� */
	UINT fnum;   
	uint8_t flag = 0;
	/* �ļ��ɹ���д���� */
	char cmd[80] = {0};
	
	/* �ļ�ϵͳ��ʼ�� */
	FileSystem_Init();

	sprintf(file_name, "0:data%d.txt", file_num);
	printf("\r\n****** �½�txt... ******\r\n");	
	res_sd = f_open(&fnew, file_name,FA_CREATE_ALWAYS | FA_WRITE );
	f_close(&fnew);
	
	///* �ļ�ϵͳ��д���� */
	//FileSystem_Test();
	while (1)
	{
		xReturn = xSemaphoreTake(SD_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		if(pdPASS == xReturn)
		{
			if(save_flag)
			{
				LED1_TOGGLE;
				if(flag != file_num)
				{
					printf("\r\n****** �½�txt... ******\r\n");	
					res_sd = f_open(&fnew, file_name,FA_CREATE_ALWAYS | FA_WRITE );
					f_close(&fnew);
					flag = file_num;

				}
				res_sd = f_open(&fnew, file_name,FA_OPEN_EXISTING | FA_WRITE );
				
				for(int temp = 0; temp < 3; temp++) {

					res_sd=f_lseek(&fnew,f_size(&fnew));
					if(res_sd==FR_OK)
					{
						printf("ƫ�����\r\n");
					}
					switch(temp) {
						case(0): {
							res_sd=f_write(&fnew,text1,sizeof(text1),&fnum);
							break;
						}
						case(1): {
							res_sd=f_write(&fnew,text2,sizeof(text2),&fnum);
							break;
						}
						case(2): {
							res_sd=f_write(&fnew,text3,sizeof(text3),&fnum);
							break;
						}
					}
					
					res_sd=f_lseek(&fnew,f_size(&fnew));
					if(res_sd==FR_OK)
					{
						printf("ƫ�����\r\n");
					}
					
					sprintf(ascii_buf, "%d  %d  %d  %d  %d  %d  %d  %d\r\n", (int)channel_data_buf[temp][0], (int)channel_data_buf[temp][1], (int)channel_data_buf[temp][2], (int)channel_data_buf[temp][3], (int)channel_data_buf[temp][4], (int)channel_data_buf[temp][5], (int)channel_data_buf[temp][6], (int)channel_data_buf[temp][7]);
					res_sd=f_write(&fnew,ascii_buf,sizeof(ascii_buf),&fnum);
					memset(ascii_buf,0,sizeof(ascii_buf));/* ���� */
					if(res_sd==FR_OK)
					{
					  printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\r\n",fnum);
					  //printf("�����ļ�д�������Ϊ��\r\n%s\r\n",(char*)channel_data_buf[temp]);
					}
					
				}
				f_close(&fnew);
			}
				
			if(display)
			{
				sprintf(cmd, "add 2,0,%d",(uint16_t)channel_data_buf[channel_num/2][0+(channel_num%2)*4]/2621);
				Usart_SendString(HMI_USART, cmd);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);

				sprintf(cmd, "add 2,1,%d",(uint16_t)channel_data_buf[channel_num/2][1+(channel_num%2)*4]/2621);
				Usart_SendString(HMI_USART, cmd);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);

				sprintf(cmd, "add 2,2,%d",(uint16_t)channel_data_buf[channel_num/2][2+(channel_num%2)*4]/2621);
				Usart_SendString(HMI_USART, cmd);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);

				sprintf(cmd, "add 2,3,%d",(uint16_t)channel_data_buf[channel_num/2][3+(channel_num%2)*4]/2621);
				Usart_SendString(HMI_USART, cmd);	
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);
				Usart_SendByte(HMI_USART, 0xFF);
			}
		}

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
  * @ ������  �� LED_Task
  * @ ����˵���� LED_Task��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void HMI_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	FRESULT res_sd;                /* �ļ�������� */
	FIL fnew;													/* �ļ����� */


	while (1)
	{
		//��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
		xReturn = xSemaphoreTake(HMI_BinarySem_Handle,/* ��ֵ�ź������ */
							  portMAX_DELAY); /* �ȴ�ʱ�� */
		if(pdPASS == xReturn)
		{
			LED2_TOGGLE;
			//printf("�յ�����:%s\n",HMI_Usart_Rx_Buf);
			
			if(HMI_Usart_Rx_Buf[0] == 0x55 && HMI_Usart_Rx_Buf[1] == 0xAA)
			{
				channel_num = HMI_Usart_Rx_Buf[2]-48;
				if(channel_num > -1 && HMI_Usart_Rx_Buf[3] == 0x00 && HMI_Usart_Rx_Buf[4] == 0xAA && HMI_Usart_Rx_Buf[5] == 0x55)
				{
					//������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
					xSemaphoreGive(START_BinarySem_Handle);	//�ͷŶ�ֵ�ź���
					display = 1;
				}
				else
				{
					if(channel_num == -48 && HMI_Usart_Rx_Buf[3] == 0x00 && HMI_Usart_Rx_Buf[4] == 0xAA && HMI_Usart_Rx_Buf[5] == 0x55)
					{
						display = 0;
						save_flag = 0;
					}
					if(HMI_Usart_Rx_Buf[2] == 0xFF && HMI_Usart_Rx_Buf[3] == 0x00 && HMI_Usart_Rx_Buf[4] == 0xAA && HMI_Usart_Rx_Buf[5] == 0x55)
					{
						save_flag = 1;
						
						file_num++;
						sprintf(file_name, "0:data%d.txt", file_num);
						
					}
				}
			}
			else
			{
				
			}
			printf("channel num = %d\r\n", channel_num);
			//printf("HMI_Usart_Rx_Buf[2] = %u\r\n", HMI_Usart_Rx_Buf[2]);

			memset(HMI_Usart_Rx_Buf,0,HMI_USART_RBUFF_SIZE);/* ���� */
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
	uint8_t channel = 0, num = 0;
    unsigned int  crc;
    unsigned char crch, crcl;
    uint8_t len = 7, data_len = 0;
	
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
	
	xReturn = xSemaphoreTake(START_BinarySem_Handle,/* ��ֵ�ź������ */
						  portMAX_DELAY); /* �ȴ�ʱ�� */
	if(pdPASS == xReturn)
	{

		while (1)
		{
			for(num = 0; num < 3; num++) {
				for(channel = 0; channel < 8; channel ++) {
					switch(num)
					{
						case(0):
						{
							for(int temp = 0; temp < 8; temp++) {
								Usart_SendByte(MODBUS1_USART, MODBUS1[channel][temp]);
							}
							break;
						}
						case(1):
						{
							for(int temp = 0; temp < 8; temp++) {
								Usart_SendByte(MODBUS1_USART, MODBUS2[channel][temp]);
							}
							break;
						}
						case(2):
						{
							for(int temp = 0; temp < 8; temp++) {
								Usart_SendByte(MODBUS1_USART, MODBUS3[channel][temp]);
							}
							break;
						}
					}
					
					
					
					//��ȡ��ֵ�ź��� xSemaphore,û��ȡ����һֱ�ȴ�
					xReturn = xSemaphoreTake(MODBUS_BinarySem_Handle,/* ��ֵ�ź������ */
										  portMAX_DELAY); /* �ȴ�ʱ�� */
					if(pdPASS == xReturn)
					{
						LED3_TOGGLE;
						//printf("�յ�����:%s \r\n",MODBUS1_Usart_Rx_Buf);
				
						if(MODBUS1_Usart_Rx_Buf[0] == num+1)                                                         //�жϵ�ַ�ǲ���01
						{
							crc = GetCRC16((uint8_t *)MODBUS1_Usart_Rx_Buf, len-2); //����CRCУ��ֵ
							crch = crc >> 8;
							crcl = crc & 0xFF;
							if ((MODBUS1_Usart_Rx_Buf[len-2] == crch) && (MODBUS1_Usart_Rx_Buf[len-1] == crcl)) //�ж�CRCУ���Ƿ���ȷ
							{
								switch (MODBUS1_Usart_Rx_Buf[1]) //��������ִ�в���
								{
									case 0x03:  //��ȡһ���������ļĴ���
									{
										data_len = MODBUS1_Usart_Rx_Buf[2];
										for(int temp = 0; temp < data_len; temp++)
										{
											channel_data_buf[num][channel] = channel_data_buf[num][channel] << 8;
											channel_data_buf[num][channel] |= MODBUS1_Usart_Rx_Buf[3+temp];
										}
										
										break;
									}
									
									default:  //������֧�ֵĹ�����
										printf("err��������\r\n");
										channel_data_buf[num][channel] = 0;
										break;
								}
								printf("�յ�����:%d \r\n",channel_data_buf[num][channel]);				 
							}
							else
							{
								printf("err, CRC\r\n");
								channel_data_buf[num][channel] = 0;

							}
				
						}
						else
						{
							printf("err, �豸��\r\n");
							channel_data_buf[num][channel] = 0;
						}
				
						memset(MODBUS1_Usart_Rx_Buf,0,DEBUG_USART_RBUFF_SIZE);/* ���� */
					}
					
				}
			}
			/*-----������һ�������-----*/
			LED4_TOGGLE;
			  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
			xSemaphoreGive(SD_BinarySem_Handle);	//�ͷŶ�ֵ�ź���

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
  
	/* DMA��ʼ��	*/
	HMI_DMA_Config();
	/* ���ڳ�ʼ��	*/
	HMI_USART_Config();
  
	/* ������ʼ��	*/
	Key_GPIO_Config();
	
	printf("Init finish\r\n");
}

/********************************END OF FILE****************************/


