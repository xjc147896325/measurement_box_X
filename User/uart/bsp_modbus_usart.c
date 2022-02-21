/**
  ******************************************************************************
  * @file    bsp_mosbus_usart.c
  * @author  jOKERII
  * @version V1.0
  * @date    2022-02-20
  * @brief   �жϽ���ģʽ
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
  
#include "bsp_modbus_usart.h"
/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* ����USARTΪ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = MODBUS1_USART_IRQ;
	/* �������ȼ�Ϊ1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
	/* �����ȼ�Ϊ1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* ��ʼ������NVIC */
	NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  MODBUS_USART GPIO ����,����ģʽ���á�115200 8-N-1 ���жϽ���ģʽ
  * @param  ��
  * @retval ��
  */
void MODBUS1_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
			
	RCC_AHB1PeriphClockCmd(MODBUS1_USART_RX_GPIO_CLK|MODBUS1_USART_TX_GPIO_CLK,ENABLE);
	
	/* ʹ�� USART ʱ�� */
	RCC_APB1PeriphClockCmd(MODBUS1_USART_CLK, ENABLE);
	
	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MODBUS1_USART_TX_PIN  ;  
	GPIO_Init(MODBUS1_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����Rx����Ϊ���ù��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = MODBUS1_USART_RX_PIN;
	GPIO_Init(MODBUS1_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(MODBUS1_USART_RX_GPIO_PORT,MODBUS1_USART_RX_SOURCE,MODBUS1_USART_RX_AF);
	
	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(MODBUS1_USART_TX_GPIO_PORT,MODBUS1_USART_TX_SOURCE,MODBUS1_USART_TX_AF);
	
	/* ���ô�DEBUG_USART ģʽ */
	/* ���������ã�DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = MODBUS1_USART_BAUDRATE;
	/* �ֳ�(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(MODBUS1_USART, &USART_InitStructure); 
	
  /* Ƕ�������жϿ�����NVIC���� */
	NVIC_Configuration();
  
	// ���� ���ڿ���IDEL �ж�
	USART_ITConfig(MODBUS1_USART, USART_IT_IDLE, ENABLE);  
  // ��������DMA����
	USART_DMACmd(MODBUS1_USART, USART_DMAReq_Rx, ENABLE); 
	
  /* ʹ�ܴ��� */
	USART_Cmd(MODBUS1_USART, ENABLE);
}


char MODBUS1_Usart_Rx_Buf[MODBUS1_USART_RBUFF_SIZE];

void MODBUS1_DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  // ����DMAʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
  // DMA��λ
  DMA_DeInit(MODBUS1_USART_DMA_STREAM);  
  // ����DMAͨ��
  DMA_InitStructure.DMA_Channel = MODBUS1_USART_RX_DMA_CHANNEL;  
  /*����DMAԴ���������ݼĴ�����ַ*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)MODBUS1_USART_DR_ADDRESS;
  // �ڴ��ַ(Ҫ����ı�����ָ��)
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)MODBUS1_Usart_Rx_Buf;
  // ���򣺴��ڴ浽����	
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  // �����С	
  DMA_InitStructure.DMA_BufferSize = MODBUS1_USART_RBUFF_SIZE;
  // �����ַ����	    
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �ڴ��ַ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  // �������ݵ�λ	
  DMA_InitStructure.DMA_PeripheralDataSize = 
  DMA_PeripheralDataSize_Byte;
  // �ڴ����ݵ�λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
  // DMAģʽ��һ�λ���ѭ��ģʽ
  //DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
  // ���ȼ�����	
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
  // ��ֹ�ڴ浽�ڴ�Ĵ���
  /*����FIFO*/
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;    
  /*�洢��ͻ������ 1������*/
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  /*����ͻ������ 1������*/
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
  /*����DMA2��������7*/		   
  DMA_Init(MODBUS1_USART_DMA_STREAM, &DMA_InitStructure);
  // ���DMA���б�־
  DMA_ClearFlag(MODBUS1_USART_DMA_STREAM,DMA_FLAG_TCIF2);
  DMA_ITConfig(MODBUS1_USART_DMA_STREAM, DMA_IT_TE, ENABLE);
  // ʹ��DMA
  DMA_Cmd (MODBUS1_USART_DMA_STREAM,ENABLE);
}

extern SemaphoreHandle_t MODBUS_BinarySem_Handle;

void MODBUS1_DMA_Rx_Data(void)
{
  BaseType_t pxHigherPriorityTaskWoken;
  // �ر�DMA ����ֹ����
  DMA_Cmd(MODBUS1_USART_DMA_STREAM, DISABLE);      
  // ��DMA��־λ
  DMA_ClearFlag(MODBUS1_USART_DMA_STREAM,DMA_FLAG_TCIF2);         
  //  ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
  DMA_SetCurrDataCounter(MODBUS1_USART_DMA_STREAM,MODBUS1_USART_RBUFF_SIZE);     
  DMA_Cmd(MODBUS1_USART_DMA_STREAM, ENABLE);       
  /* 
  xSemaphoreGiveFromISR(SemaphoreHandle_t xSemaphore,
                      BaseType_t *pxHigherPriorityTaskWoken);
  */

  //������ֵ�ź��� �����ͽ��յ������ݱ�־����ǰ̨�����ѯ
  xSemaphoreGiveFromISR(MODBUS_BinarySem_Handle,&pxHigherPriorityTaskWoken);	//�ͷŶ�ֵ�ź���
  //�����Ҫ�Ļ�����һ�������л���ϵͳ���ж��Ƿ���Ҫ�����л�
  portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);

}


/*********************************************END OF FILE**********************/
