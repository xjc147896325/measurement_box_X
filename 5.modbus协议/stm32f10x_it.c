/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "include.h"

/*******************************************************************************
* 函数名称:  TIM1_UP_IRQHandler
* 函数功能: 打开定时器1中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void TIM1_UP_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);	                     //清空中断，否则下次进不来

    if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //读取输出口的高低电平
    {
       GPIO_SetBits(GPIOB,GPIO_Pin_5);	
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    }
}																			   
/*******************************************************************************
* 函数名称:  TIM2_IRQHandler
* 函数功能: 打开定时器3中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void TIM2_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	                     //清空中断，否则下次进不来
    Usart1RxMonitor(1);
}																			   
/*******************************************************************************
* 函数名称:  TIM3_IRQHandler
* 函数功能: 打开定时器3中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void TIM3_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	                   //清空中断，否则下次进不来
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_3)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_3);	
      }
      else
      {
         GPIO_ResetBits(GPIOD,GPIO_Pin_3);
      }
}																			   
/*******************************************************************************
* 函数名称:  TIM4_IRQHandler
* 函数功能: 打开定时器4中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void TIM4_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	                   //清空中断，否则下次进不来
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_3)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_3);	
      }
      else
      {
         GPIO_ResetBits(GPIOD,GPIO_Pin_3);
      }
}																			   
/*******************************************************************************
* 函数名称:  TIM5_IRQHandler
* 函数功能: 打开定时器2中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM5_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM5,TIM_IT_Update);	//清空中断，否则下次进不来
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED 发光
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* 函数名称:  TIM6_IRQHandler
* 函数功能: 打开定时器2中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM6_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	//清空中断，否则下次进不来
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED 发光
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* 函数名称:  TIM7_IRQHandler
* 函数功能: 打开定时器7中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM7_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM7,TIM_IT_Update);	//清空中断，否则下次进不来
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED 发光
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* 函数名称:  TIM8_UP_IRQHandler
* 函数功能: 打开定时器1中段入口
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void TIM8_UP_IRQHandler(void)                                                 //TIM8_UP_IRQHandler中断口
{
    TIM_ClearITPendingBit(TIM8,TIM_IT_Update);	                              //清空中断，否则下次进不来

      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED 发光
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}
/*******************************************************************************
* 函数名称:  USART1_IRQHandler
* 函数功能: usart串口接收数据并储存到USART1_RX_BUF中
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-11-6
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void USART1_IRQHandler(void)
{
   u8 res;	                                                              //定义一个数据缓存变量   
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
        res =USART_ReceiveData(USART1);                                       //读取接收到的数据
        if(USART1_RX_CNT< sizeof(USART1_RX_BUF) )                             //一次只能接收64 个字节,认为设定，可以更大，但浪费时间
        {
                USART1_RX_BUF[USART1_RX_CNT]=res;	                      //记录接收到的值
                USART1_RX_CNT++;			                      //接收数据增加1 
        } 
   }
}
/*******************************************************************************
* 函数名称:  USART2_IRQHandler
* 函数功能: usart串口接收数据并储存到USART1_RX_BUF中
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-11-16
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void USART2_IRQHandler(void)
{
   u8 res;	                                                              //定义一个数据缓存变量   
   if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
   {
        res =USART_ReceiveData(USART2);                                       //读取接收到的数据
        if(USART1_RX_CNT< sizeof(USART1_RX_BUF) )                             //一次只能接收64 个字节,认为设定，可以更大，但浪费时间
        {
                USART1_RX_BUF[USART1_RX_CNT]=res;	                      //记录接收到的值
                USART1_RX_CNT++;			                      //接收数据增加1 
        } 
   }
}

