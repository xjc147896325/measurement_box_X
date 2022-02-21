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
* ��������:  TIM1_UP_IRQHandler
* ��������: �򿪶�ʱ��1�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void TIM1_UP_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);	                     //����жϣ������´ν�����

    if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //��ȡ����ڵĸߵ͵�ƽ
    {
       GPIO_SetBits(GPIOB,GPIO_Pin_5);	
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    }
}																			   
/*******************************************************************************
* ��������:  TIM2_IRQHandler
* ��������: �򿪶�ʱ��3�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void TIM2_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	                     //����жϣ������´ν�����
    Usart1RxMonitor(1);
}																			   
/*******************************************************************************
* ��������:  TIM3_IRQHandler
* ��������: �򿪶�ʱ��3�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void TIM3_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	                   //����жϣ������´ν�����
      
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
* ��������:  TIM4_IRQHandler
* ��������: �򿪶�ʱ��4�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void TIM4_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	                   //����жϣ������´ν�����
      
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
* ��������:  TIM5_IRQHandler
* ��������: �򿪶�ʱ��2�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM5_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM5,TIM_IT_Update);	//����жϣ������´ν�����
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED ����
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* ��������:  TIM6_IRQHandler
* ��������: �򿪶�ʱ��2�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM6_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	//����жϣ������´ν�����
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED ����
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* ��������:  TIM7_IRQHandler
* ��������: �򿪶�ʱ��7�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM7_IRQHandler(void)
{
      TIM_ClearITPendingBit(TIM7,TIM_IT_Update);	//����жϣ������´ν�����
      
      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED ����
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}

/*******************************************************************************
* ��������:  TIM8_UP_IRQHandler
* ��������: �򿪶�ʱ��1�ж����
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void TIM8_UP_IRQHandler(void)                                                 //TIM8_UP_IRQHandler�жϿ�
{
    TIM_ClearITPendingBit(TIM8,TIM_IT_Update);	                              //����жϣ������´ν�����

      if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==Bit_RESET)
      {
         GPIO_SetBits(GPIOD,GPIO_Pin_6);	
      }
      else
      {
         //LED ����
         GPIO_ResetBits(GPIOD,GPIO_Pin_6);
      }
}
/*******************************************************************************
* ��������:  USART1_IRQHandler
* ��������: usart���ڽ������ݲ����浽USART1_RX_BUF��
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-11-6
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void USART1_IRQHandler(void)
{
   u8 res;	                                                              //����һ�����ݻ������   
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
        res =USART_ReceiveData(USART1);                                       //��ȡ���յ�������
        if(USART1_RX_CNT< sizeof(USART1_RX_BUF) )                             //һ��ֻ�ܽ���64 ���ֽ�,��Ϊ�趨�����Ը��󣬵��˷�ʱ��
        {
                USART1_RX_BUF[USART1_RX_CNT]=res;	                      //��¼���յ���ֵ
                USART1_RX_CNT++;			                      //������������1 
        } 
   }
}
/*******************************************************************************
* ��������:  USART2_IRQHandler
* ��������: usart���ڽ������ݲ����浽USART1_RX_BUF��
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-11-16
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void USART2_IRQHandler(void)
{
   u8 res;	                                                              //����һ�����ݻ������   
   if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
   {
        res =USART_ReceiveData(USART2);                                       //��ȡ���յ�������
        if(USART1_RX_CNT< sizeof(USART1_RX_BUF) )                             //һ��ֻ�ܽ���64 ���ֽ�,��Ϊ�趨�����Ը��󣬵��˷�ʱ��
        {
                USART1_RX_BUF[USART1_RX_CNT]=res;	                      //��¼���յ���ֵ
                USART1_RX_CNT++;			                      //������������1 
        } 
   }
}

