#ifndef __BSP_HMI_USART_H
#define	__BSP_HMI_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
#define HMI_USART                             USART3

/* 不同的串口挂载的总线不一样，时钟使能函数也不一样，移植时要注意
* 串口1和6是      RCC_APB2PeriphClockCmd
* 串口2/3/4/5是    RCC_APB1PeriphClockCmd
*/
// 串口对应的DMA请求通道
#define  HMI_USART_RX_DMA_CHANNEL      DMA_Channel_4
#define  HMI_USART_DMA_STREAM    	   DMA1_Stream1
// 外设寄存器地址
#define  HMI_USART_DR_ADDRESS          (&HMI_USART->DR)
// 一次发送的数据量
#define  HMI_USART_RBUFF_SIZE          1000 

#define HMI_USART_CLK                         	  RCC_APB1Periph_USART3
#define HMI_USART_BAUDRATE                    	  115200  //串口波特率

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
