#include "include.h"
/*******************************************************************************
（1）       利用TIM_DeInit()函数将Timer设置为默认缺省值；
（2）       TIM_InternalClockConfig()选择TIMx来设置内部时钟源；
（3）       TIM_Perscaler来设置预分频系数；
（4）       TIM_ClockDivision来设置时钟分割；
（5）       TIM_CounterMode来设置计数器模式；
（6）       TIM_Period来设置自动装入的值
（7）       TIM_ARRPerloadConfig()来设置是否使用预装载缓冲器
（8）       TIM_ITConfig()来开启TIMx的中断
*******************************************************************************/
/*******************************************************************************
* 函数名称:  TIMER_Configuration
* 函数功能: 调用所有定时器的配置
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIMER_Configuration(void)
{
  //TIM1_Configuration();
  TIM2_Configuration();
  //TIM3_Configuration();
  //TIM4_Configuration();
  //TIM5_Configuration();
  //TIM6_Configuration();
  //TIM7_Configuration();
  //TIM8_Configuration();
}
/*******************************************************************************
* 函数名称:  TIM1_Configuration
* 函数功能: 定时器1打开配置为500ms
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);             //打开APB2TIM1时钟
	//定时器TIM2初始化
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM1,ENABLE);	                                        //使能TIM1
	//中断优先级NVIC设置
        NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;              //TIM1_UP_IRQn为中端口
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
}
/*******************************************************************************
* 函数名称:  TIM2_Configuration
* 函数功能: 定时器2打开配置为500ms
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);             //打开APB1TIM2时钟
	//定时器TIM2初始化
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM2,ENABLE);	                                        //使能TIMx
	//中断优先级NVIC设置
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
}

/*******************************************************************************
* 函数名称:  TIM3_Configuration
* 函数功能: 定时器3打开配置为1S
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);             //打开APB1TIM3时钟
	//定时器TIM3初始化
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM3,ENABLE);	                                        //使能TIM3
	//中断优先级NVIC设置
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
}/*******************************************************************************
* 函数名称:  TIM3_Configuration
* 函数功能: 定时器3打开配置为1S
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);             //打开APB1TIM4时钟
	//定时器TIM4初始化
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM4,ENABLE);	                                        //使能TIM4
	//中断优先级NVIC设置
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
}
/*******************************************************************************
* 函数名称:  TIM5_Configuration
* 函数功能: 定时器5打开配置为1S
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);             //打开APB1TIM5时钟
	//定时器TIM5初始化
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM5,ENABLE);	                                        //使能TIM5
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级5级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器

}
/*******************************************************************************
* 函数名称:  TIM6_Configuration
* 函数功能: 定时器6打开配置为1S
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-23
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);             //打开APB1TIM6时钟
	//定时器TIM5初始化
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM6,ENABLE);	                                        //使能TIM6
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;                 //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器

}
/*******************************************************************************
* 函数名称:  TIM7_Configuration
* 函数功能: 定时器7打开配置为1S
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-23
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);             //打开APB1TIM6时钟
	//定时器TIM5初始化
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=1999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM7,ENABLE);	                                        //使能TIM6
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;                 //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器

}
/*******************************************************************************
* 函数名称:  TIM1_Configuration
* 函数功能: 定时器1打开配置为500ms
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void TIM8_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //配置结构体 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);             //打开APB2TIM1时钟
	//定时器TIM2初始化
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update);                      //清空定时器中断
	TIM_TimeBaseStruct.TIM_Period=999;                             //装初值  范围0——0xffff  65536	一秒钟计数2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //预分频 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //设置时钟分割
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStruct);	                //初始化
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);                        //打开定时器的中断  没有这语句产生不了中断
	TIM_Cmd(TIM8,ENABLE);	                                        //使能TIM1
	//中断优先级NVIC设置
        NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;              //TIM1_UP_IRQn为中端口
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                                 //初始化NVIC寄存器
}
