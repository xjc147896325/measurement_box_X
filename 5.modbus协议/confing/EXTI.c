#include "include.h"
/***************************************************************************************/

/*阅读exti：外部设备中断函数
我的理解——外部设备通过引脚给出的硬件中断，也可以产生软件中断，19个上升、下降或都触发。EXTI0～EXTI15连接到管脚，
EXTI线16连接到PVD（VDD监视），EXTI线17连接到RTC（闹钟），EXTI线18连接到USB（唤醒）。
基础应用1，设定外部中断初始化函数。按需求，不是必须代码。*/
/***************************************************************************************/

void EXTI_Configuration(void)	                                   
{
    EXTI_InitTypeDef EXTI_InitStructure;                                     //结构体
    /*----配置外部中断源并进行中断源和GPIO的连接-----*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);              //  选着外部中断作为外设线  映射到PC1外部中断线上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);              //  选着外部中断作为外设线  映射到PC2外部中断线上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);              //  选着外部中断作为外设线  映射到PC3外部中断线上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);              //  选着外部中断作为外设线  映射到PC5外部中断线上
    
    EXTI_ClearITPendingBit(EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line5);     //清除 EXTI 线路挂起位 
    EXTI_InitStructure.EXTI_Line=EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line5;//选择中断线                             //选择中断线
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	                     //设置为中断方式
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;                    //下降沿触发方式
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;			             // 使能
    EXTI_Init(&EXTI_InitStructure);			                     //初始化结构体
}
/****************************************************************************
* 名    称：void EXTI9_5_IRQHandler(void)
* 功    能：EXTI9-5中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5)==SET)                                      //是否产生中断
  {
   	EXTI_ClearITPendingBit(EXTI_Line5);	                             //清除中断EXTI_Line5
	delay_ms(10);                                                        //消抖动 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==Bit_RESET)               //判断按键输入口是否为低电平
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //读取输出口的高低电平
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}
/****************************************************************************
* 名    称：void EXTI1_IRQHandler(void)
* 功    能：EXTI1中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1)==SET)                                      //是否产生中断
  {
   	EXTI_ClearITPendingBit(EXTI_Line1);	                             //清除中断EXTI_Line5
	delay_ms(10);                                                        //消抖动 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==Bit_RESET)               //判断按键输入口是否为低电平
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //读取输出口的高低电平
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}

/****************************************************************************
* 名    称：void EXTI1_IRQHandler(void)
* 功    能：EXTI2中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2)==SET)                                      //是否产生中断
  {
   	EXTI_ClearITPendingBit(EXTI_Line2);	                             //清除中断EXTI_Line5
	delay_ms(10);                                                        //消抖动 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==Bit_RESET)               //判断按键输入口是否为低电平
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //读取输出口的高低电平
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}

