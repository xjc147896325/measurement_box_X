/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   FreeRTOS V9.0.0  + STM32 固件库例程
  *********************************************************************
  * @attention
  *
  * 实验平台:野火 STM32 全系列开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             包含的头文件
*************************************************************************
*/ 
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* 开发板硬件bsp头文件 */
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_modbus_usart.h"
#include "bsp_key.h"
#include "ff.h"
#include "./FatFs_Test/FatFs_test.h"

/* 标准库头文件 */
#include <string.h>

/* CRC-16 MODBUS */
#include "CRC16.h"
/**************************** 任务句柄 ********************************/
/* 
 * 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
 * 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
 * 这个句柄可以为NULL。
 */
static TaskHandle_t AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
static TaskHandle_t Test_Task_Handle = NULL;/* LED任务句柄 */
static TaskHandle_t MODBUS_Task_Handle = NULL;/* KEY任务句柄 */
static TaskHandle_t Uart_Task_Handle = NULL;/* KEY任务句柄 */

/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 * 
 */
SemaphoreHandle_t DEBUG_BinarySem_Handle =NULL;
SemaphoreHandle_t MODBUS_BinarySem_Handle =NULL;
SemaphoreHandle_t SD_BinarySem_Handle =NULL;


/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */
 
extern char Debug_Usart_Rx_Buf[DEBUG_USART_RBUFF_SIZE];
extern char MODBUS1_Usart_Rx_Buf[MODBUS1_USART_RBUFF_SIZE];

uint8_t MODBUS1[8][8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x05, 0x85, 0xC9,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x06, 0xC5, 0xC8,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x08, 0x44, 0x0C}; //站号 01 功能码 03 起始地址 0000 寄存器数量 0001 CRC 840A

/*----------------jide gai ------------------*/
uint8_t MODBUS2[8][8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x05, 0x85, 0xC9,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x06, 0xC5, 0xC8,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x08, 0x44, 0x0C}; //站号 01 功能码 03 起始地址 0000 寄存器数量 0001 CRC 840A

uint8_t MODBUS3[8][8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x05, 0x85, 0xC9,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x06, 0xC5, 0xC8,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08,
						 0x01, 0x03, 0x00, 0x00, 0x00, 0x08, 0x44, 0x0C}; //站号 01 功能码 03 起始地址 0000 寄存器数量 0001 CRC 840A
/*-------------------------------*/
uint16_t channel_data_buf[3][50] = {0};
char text1[] = "\r\n第一组：\r\n";
char text2[] = "\r\n第二组：\r\n";
char text3[] = "\r\n第三组：\r\n";

						 
/*
*************************************************************************
*                             函数声明
*************************************************************************
*/
static void AppTaskCreate(void);/* 用于创建任务 */

static void Test_Task(void* pvParameters);/* Test_Task任务实现 */
static void MODBUS_Task(void* pvParameters);/* MODBUS_Task任务实现 */
static void Uart_Task(void* pvParameters);/* KEY_Task任务实现 */

static void BSP_Init(void);/* 用于初始化板载相关资源 */

/*****************************************************************
  * @brief  主函数
  * @param  无
  * @retval 无
  * @note   第一步：开发板硬件初始化 
            第二步：创建APP应用任务
            第三步：启动FreeRTOS，开始多任务调度
  ****************************************************************/
int main(void)
{	
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  /* 开发板硬件初始化 */
  BSP_Init();
  
  printf("RTOS_Init\n\n");
  
   /* 创建AppTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
    return -1;  
  
  while(1);   /* 正常不会执行到这里 */    
}


/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

	taskENTER_CRITICAL();           //进入临界区
  
	  /* 创建 DEBUG_BinarySem_Handle */
	DEBUG_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != DEBUG_BinarySem_Handle)
	printf("DEBUG_BinarySem_Handle二值信号量创建成功!\n");
  
	  /* 创建 BinarySem */
	MODBUS_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != MODBUS_BinarySem_Handle)
	printf("MODBUS_BinarySem_Handle二值信号量创建成功!\n");
  
	  /* 创建 BinarySem */
	SD_BinarySem_Handle = xSemaphoreCreateBinary();	 
  
	if(NULL != SD_BinarySem_Handle)
	printf("SD_BinarySem_Handle二值信号量创建成功!\n");
	
  /* 创建Test_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Test_Task, /* 任务入口函数 */
						(const char*    )"Test_Task",/* 任务名字 */
						(uint16_t       )512,   /* 任务栈大小 */
						(void*          )NULL,	/* 任务入口函数参数 */
						(UBaseType_t    )5,	    /* 任务的优先级 */
						(TaskHandle_t*  )&Test_Task_Handle);/* 任务控制块指针 */
	if(pdPASS == xReturn)
	printf("创建Test_Task任务成功!\r\n");
	/* 创建Uart_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )Uart_Task,  /* 任务入口函数 */
						(const char*    )"Uart_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )3, /* 任务的优先级 */
						(TaskHandle_t*  )&Uart_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建Uart_Task任务成功!\r\n");
	/* 创建MODBUS_Task任务 */
	xReturn = xTaskCreate((TaskFunction_t )MODBUS_Task,  /* 任务入口函数 */
						(const char*    )"MODBUS_Task",/* 任务名字 */
						(uint16_t       )512,  /* 任务栈大小 */
						(void*          )NULL,/* 任务入口函数参数 */
						(UBaseType_t    )4, /* 任务的优先级 */
						(TaskHandle_t*  )&MODBUS_Task_Handle);/* 任务控制块指针 */ 
	if(pdPASS == xReturn)
	printf("创建MODBUS_Task任务成功!\r\n");

	vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务

	taskEXIT_CRITICAL();            //退出临界区
}



/**********************************************************************
  * @ 函数名  ： Test_Task
  * @ 功能说明： Test_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Test_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	FRESULT res_sd;                /* 文件操作结果 */
	FIL fnew;													/* 文件对象 */
	UINT fnum;            					  /* 文件成功读写数量 */
	/* 文件系统初始化 */
	FileSystem_Init();

	printf("\r\n****** 新建txt... ******\r\n");	
	res_sd = f_open(&fnew, "0:data0.txt",FA_CREATE_ALWAYS | FA_WRITE );
	f_close(&fnew);
	
	///* 文件系统读写测试 */
	//FileSystem_Test();
	while (1)
	{
		xReturn = xSemaphoreTake(SD_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */
		if(pdPASS == xReturn)
		{
			LED1_TOGGLE;
			res_sd = f_open(&fnew, "0:data0.txt",FA_OPEN_EXISTING | FA_WRITE );
			
			for(int temp = 0; temp < 3; temp++) {

				res_sd=f_lseek(&fnew,f_size(&fnew));
				if(res_sd==FR_OK)
				{
					printf("偏移完毕\r\n");
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
					printf("偏移完毕\r\n");
				}
				
				res_sd=f_write(&fnew,channel_data_buf[temp],sizeof(channel_data_buf[temp]),&fnum);
				
				if(res_sd==FR_OK)
				{
				  printf("》文件写入成功，写入字节数据：%d\r\n",fnum);
				  printf("》向文件写入的数据为：\r\n%s\r\n",(char*)channel_data_buf[temp]);
				}
				
			}
			f_close(&fnew);
		}
	}
}

/**********************************************************************
  * @ 函数名  ： LED_Task
  * @ 功能说明： LED_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void Uart_Task(void* parameter)
{	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	while (1)
	{
		//获取二值信号量 xSemaphore,没获取到则一直等待
		xReturn = xSemaphoreTake(DEBUG_BinarySem_Handle,/* 二值信号量句柄 */
							  portMAX_DELAY); /* 等待时间 */
		if(pdPASS == xReturn)
		{
			LED2_TOGGLE;
			printf("收到数据:%s\n",Debug_Usart_Rx_Buf);
			
			
			
			
			memset(Debug_Usart_Rx_Buf,0,DEBUG_USART_RBUFF_SIZE);/* 清零 */
		}
	}
}

/**********************************************************************
  * @ 函数名  ： Test_Task
  * @ 功能说明： Test_Task任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void MODBUS_Task(void* parameter)
{	
	uint8_t channel = 0, num = 0;
    unsigned int  crc;
    unsigned char crch, crcl;
    uint8_t len = 7, data_len = 0;

	
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	

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
				
				
				
				//获取二值信号量 xSemaphore,没获取到则一直等待
				xReturn = xSemaphoreTake(MODBUS_BinarySem_Handle,/* 二值信号量句柄 */
									  portMAX_DELAY); /* 等待时间 */
				if(pdPASS == xReturn)
				{
					LED3_TOGGLE;
					//printf("收到数据:%s \r\n",MODBUS1_Usart_Rx_Buf);
			
					if(MODBUS1_Usart_Rx_Buf[0]==0x01)                                                         //判断地址是不是01
					{
						crc = GetCRC16((uint8_t *)MODBUS1_Usart_Rx_Buf, len-2); //计算CRC校验值
						crch = crc >> 8;
						crcl = crc & 0xFF;
						if ((MODBUS1_Usart_Rx_Buf[len-2] == crch) && (MODBUS1_Usart_Rx_Buf[len-1] == crcl)) //判断CRC校验是否正确
						{
							switch (MODBUS1_Usart_Rx_Buf[1]) //按功能码执行操作
							{
								case 0x03:  //读取一个或连续的寄存器
								{
									data_len = MODBUS1_Usart_Rx_Buf[2];
									for(int temp = 0; temp < data_len; temp++)
									{
										channel_data_buf[num][channel*2] = channel_data_buf[num][channel*2] >> 8;
										channel_data_buf[num][channel*2] |= MODBUS1_Usart_Rx_Buf[3+temp];
									}
									channel_data_buf[num][channel*2+1] = 0x20 >> 8;
									channel_data_buf[num][channel*2+1] |= 0x20 ;
									
									break;
								}
								
								default:  //其它不支持的功能码
									printf("err，功能码\r\n");
									break;
							}
							printf("收到数据:%d \r\n",channel_data_buf[num][channel*2]);				 
						}
						else
						{
							printf("err, CRC\r\n");
						}
			
					}
					else
					{
						printf("err, 设备号\r\n");
					}
			
					memset(MODBUS1_Usart_Rx_Buf,0,DEBUG_USART_RBUFF_SIZE);/* 清零 */
				}
				
			}
		}
		/*-----完整的一组出来了-----*/
		LED4_TOGGLE;
		  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
		xSemaphoreGive(SD_BinarySem_Handle);	//释放二值信号量

	}
}


/***********************************************************************
  * @ 函数名  ： BSP_Init
  * @ 功能说明： 板级外设初始化，所有板子上的初始化均可放在这个函数里面
  * @ 参数    ：   
  * @ 返回值  ： 无
  *********************************************************************/
static void BSP_Init(void)
{
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	
	/* LED 初始化 */
	LED_GPIO_Config();

	/* DMA初始化	*/
	Debug_DMA_Config();
	/* 串口初始化	*/
	Debug_USART_Config();
  
	/* DMA初始化	*/
	MODBUS1_DMA_Config();
	/* 串口初始化	*/
	MODBUS1_USART_Config();
  
	/* 按键初始化	*/
	Key_GPIO_Config();
	
	printf("Init finish\r\n");
}

/********************************END OF FILE****************************/
