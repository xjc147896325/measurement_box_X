#ifndef __BSP_MODBUS_USART_H
#define	__BSP_MODBUS_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//���Ŷ���
/*******************************************************/
#define MODBUS1_USART                             USART2

/* ��ͬ�Ĵ��ڹ��ص����߲�һ����ʱ��ʹ�ܺ���Ҳ��һ������ֲʱҪע��
* ����1��6��      RCC_APB2PeriphClockCmd
* ����2/3/4/5��    RCC_APB1PeriphClockCmd
*/
// ���ڶ�Ӧ��DMA����ͨ��
#define  MODBUS1_USART_RX_DMA_CHANNEL      DMA_Channel_4
#define  MODBUS1_USART_DMA_STREAM    	   DMA1_Stream5
// ����Ĵ�����ַ
#define  MODBUS1_USART_DR_ADDRESS          (&MODBUS1_USART->DR)
// һ�η��͵�������
#define  MODBUS1_USART_RBUFF_SIZE          1000 

#define MODBUS1_USART_CLK                         RCC_APB1Periph_USART2
#define MODBUS1_USART_BAUDRATE                    115200  //���ڲ�����

#define MODBUS1_USART_RX_GPIO_PORT                GPIOA
#define MODBUS1_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define MODBUS1_USART_RX_PIN                      GPIO_Pin_3
#define MODBUS1_USART_RX_AF                       GPIO_AF_USART2
#define MODBUS1_USART_RX_SOURCE                   GPIO_PinSource3

#define MODBUS1_USART_TX_GPIO_PORT                GPIOA
#define MODBUS1_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define MODBUS1_USART_TX_PIN                      GPIO_Pin_2
#define MODBUS1_USART_TX_AF                       GPIO_AF_USART2
#define MODBUS1_USART_TX_SOURCE                   GPIO_PinSource2

#define MODBUS1_USART_IRQHandler                  USART2_IRQHandler
#define MODBUS1_USART_IRQ                 		  USART2_IRQn
/************************************************************/

void MODBUS1_USART_Config(void);

void MODBUS1_DMA_Config(void);
void MODBUS1_DMA_Rx_Data(void);

#endif /* __USART1_H */
