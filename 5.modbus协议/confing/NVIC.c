#include "include.h"
/*******************************************************************************
* 函数名称:  NVIC_Configuration
* 函数功能: 设置中断嵌套优先级
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void NVIC_Configuration(void)	//分配中断响应优先级
{
   	NVIC_InitTypeDef NVIC_InitStructure;                                   //配置结构体 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);                        //选择中断优先级分组，此处选择0。使0级抢占式优先级，16级亚优先级
 	//打开中断线EXTI1_IRQn
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;                       //中断入口函数
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //亚优先级配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //使能通道
	NVIC_Init(&NVIC_InitStructure);                                        //初始化结构体   
 	//打开中断线EXTI2_IRQn
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                       //中断入口函数
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //亚优先级配置
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //使能通道
	NVIC_Init(&NVIC_InitStructure);                                        //初始化结构体   
 	//打开中断线EXTI3_IRQn
        NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 	               //相应的通道配置，此处选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //抢占式优先级配置 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //亚优先级配置 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //使能通道
	NVIC_Init(&NVIC_InitStructure);                                        //初始化结构体   
}


