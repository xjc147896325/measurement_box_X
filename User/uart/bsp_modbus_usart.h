#ifndef __BSP_MODBUS_USART_H
#define	__BSP_MODBUS_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
#define MODBUS1_USART                             USART2

/* 不同的串口挂载的总线不一样，时钟使能函数也不一样，移植时要注意
* 串口1和6是      RCC_APB2PeriphClockCmd
* 串口2/3/4/5是    RCC_APB1PeriphClockCmd
*/
// 串口对应的DMA请求通道
#define  MODBUS1_USART_RX_DMA_CHANNEL      DMA_Channel_4
#define  MODBUS1_USART_DMA_STREAM    	   DMA1_Stream5
// 外设寄存器地址
#define  MODBUS1_USART_DR_ADDRESS          (&MODBUS1_USART->DR)
// 一次发送的数据量
#define  MODBUS1_USART_RBUFF_SIZE          1000 

#define MODBUS1_USART_CLK                         RCC_APB1Periph_USART2
#define MODBUS1_USART_BAUDRATE                    115200  //串口波特率

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
