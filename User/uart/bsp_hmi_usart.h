#ifndef __BSP_HMI_USART_H
#define	__BSP_HMI_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//���Ŷ���
/*******************************************************/
#define HMI_USART                             USART3

/* ��ͬ�Ĵ��ڹ��ص����߲�һ����ʱ��ʹ�ܺ���Ҳ��һ������ֲʱҪע��
* ����1��6��      RCC_APB2PeriphClockCmd
* ����2/3/4/5��    RCC_APB1PeriphClockCmd
*/
// ���ڶ�Ӧ��DMA����ͨ��
#define  HMI_USART_RX_DMA_CHANNEL      DMA_Channel_4
#define  HMI_USART_DMA_STREAM    	   DMA1_Stream1
// ����Ĵ�����ַ
#define  HMI_USART_DR_ADDRESS          (&HMI_USART->DR)
// һ�η��͵�������
#define  HMI_USART_RBUFF_SIZE          1000 

#define HMI_USART_CLK                         	  RCC_APB1Periph_USART3
#define HMI_USART_BAUDRATE                    	  115200  //���ڲ�����

#define HMI_USART_RX_GPIO_PORT                    GPIOD
#define HMI_USART_RX_GPIO_CLK                     RCC_AHB1Periph_GPIOD
#define HMI_USART_RX_PIN                          GPIO_Pin_9
#define HMI_USART_RX_AF                           GPIO_AF_USART3
#define HMI_USART_RX_SOURCE                       GPIO_PinSource9
		                                       
#define HMI_USART_TX_GPIO_PORT                    GPIOD
#define HMI_USART_TX_GPIO_CLK                     RCC_AHB1Periph_GPIOD
#define HMI_USART_TX_PIN                          GPIO_Pin_8
#define HMI_USART_TX_AF                           GPIO_AF_USART3
#define HMI_USART_TX_SOURCE                       GPIO_PinSource8
		                                       
#define HMI_USART_IRQHandler                      USART3_IRQHandler
#define HMI_USART_IRQ                 		      USART3_IRQn
/************************************************************/

void HMI_USART_Config(void);

void HMI_DMA_Config(void);
void HMI_DMA_Rx_Data(void);

#endif /* __USART1_H */
