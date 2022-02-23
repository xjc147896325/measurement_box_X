/**
  ******************************************************************************
  * @file    bsp_mosbus_usart.c
  * @author  jOKERII
  * @version V1.0
  * @date    2022-02-20
  * @brief   中断接收模式
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
  
#include "bsp_hmi_usart.h"
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 嵌套向量中断控制器组选择 */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* 配置USART为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = HMI_USART_IRQ;
	/* 抢断优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
	/* 子优先级为1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* 初始化配置NVIC */
	NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  MODBUS_USART GPIO 配置,工作模式配置。115200 8-N-1 ，中断接收模式
  * @param  无
  * @retval 无
  */
void HMI_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
			
	RCC_AHB1PeriphClockCmd(HMI_USART_RX_GPIO_CLK|HMI_USART_TX_GPIO_CLK,ENABLE);
	
	/* 使能 USART 时钟 */
	RCC_APB1PeriphClockCmd(HMI_USART_CLK, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 配置Tx引脚为复用功能  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = HMI_USART_TX_PIN  ;  
	GPIO_Init(HMI_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置Rx引脚为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = HMI_USART_RX_PIN;
	GPIO_Init(HMI_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(HMI_USART_RX_GPIO_PORT,HMI_USART_RX_SOURCE,HMI_USART_RX_AF);
	
	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(HMI_USART_TX_GPIO_PORT,HMI_USART_TX_SOURCE,HMI_USART_TX_AF);
	
	/* 配置串DEBUG_USART 模式 */
	/* 波特率设置：DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = HMI_USART_BAUDRATE;
	/* 字长(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(HMI_USART, &USART_InitStructure); 
	
  /* 嵌套向量中断控制器NVIC配置 */
	NVIC_Configuration();
  
	// 开启 串口空闲IDEL 中断
	USART_ITConfig(HMI_USART, USART_IT_IDLE, ENABLE);  
  // 开启串口DMA接收
	USART_DMACmd(HMI_USART, USART_DMAReq_Rx, ENABLE); 
	
  /* 使能串口 */
	USART_Cmd(HMI_USART, ENABLE);
}


char HMI_Usart_Rx_Buf[HMI_USART_RBUFF_SIZE];

void HMI_DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  // 开启DMA时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
  // DMA复位
  DMA_DeInit(HMI_USART_DMA_STREAM);  
  // 设置DMA通道
  DMA_InitStructure.DMA_Channel = HMI_USART_RX_DMA_CHANNEL;  
  /*设置DMA源：串口数据寄存器地址*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)HMI_USART_DR_ADDRESS;
  // 内存地址(要传输的变量的指针)
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)HMI_Usart_Rx_Buf;
  // 方向：从内存到外设	
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  // 传输大小	
  DMA_InitStructure.DMA_BufferSize = HMI_USART_RBUFF_SIZE;
  // 外设地址不增	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // 内存地址自增
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  // 外设数据单位	
  DMA_InitStructure.DMA_PeripheralDataSize = 
  DMA_PeripheralDataSize_Byte;
  // 内存数据单位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
  // DMA模式，一次或者循环模式
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
  // 优先级：中	
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
  // 禁止内存到内存的传输
  /*禁用FIFO*/
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
  /*存储器突发传输 1个节拍*/
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  /*外设突发传输 1个节拍*/
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
  /*配置DMA2的数据流7*/		   
  DMA_Init(HMI_USART_DMA_STREAM, &DMA_InitStructure);
  // 清除DMA所有标志
  DMA_ClearFlag(HMI_USART_DMA_STREAM,DMA_FLAG_TCIF2);
  DMA_ITConfig(HMI_USART_DMA_STREAM, DMA_IT_TE, ENABLE);
  // 使能DMA
  DMA_Cmd (HMI_USART_DMA_STREAM,ENABLE);
}

extern SemaphoreHandle_t HMI_BinarySem_Handle;

void HMI_DMA_Rx_Data(void)
{
  BaseType_t pxHigherPriorityTaskWoken;
  // 关闭DMA ，防止干扰
  DMA_Cmd(HMI_USART_DMA_STREAM, DISABLE);      
  // 清DMA标志位
  DMA_ClearFlag(HMI_USART_DMA_STREAM,DMA_FLAG_TCIF2);         
  //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目
  DMA_SetCurrDataCounter(HMI_USART_DMA_STREAM,HMI_USART_RBUFF_SIZE);     
  DMA_Cmd(HMI_USART_DMA_STREAM, ENABLE);       
  /* 
  xSemaphoreGiveFromISR(SemaphoreHandle_t xSemaphore,
                      BaseType_t *pxHigherPriorityTaskWoken);
  */

  //给出二值信号量 ，发送接收到新数据标志，供前台程序查询
  xSemaphoreGiveFromISR(HMI_BinarySem_Handle,&pxHigherPriorityTaskWoken);	//释放二值信号量
  //如果需要的话进行一次任务切换，系统会判断是否需要进行切换
  portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);

}


/*********************************************END OF FILE**********************/
