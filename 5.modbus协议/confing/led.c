#include "include.h"
/*******************************************************************************
* 函数名称:  GPIO_Configuration
* 函数功能: 设置gpio口的操作
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-17
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void GPIO_Configuration(void)//Config(配置)
{		
        /*定义一个GPIO_InitTypeDef类型的结构体*/
        GPIO_InitTypeDef GPIO_InitStructure;//此句必须有，定义一个结构体
       /*选择要控制的GPIOC引脚*/															   
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//选择所需要的口，定义一下，	
        /*设置引脚模式为通用推挽输出*/
        GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //设置引脚模式，
        /* STM32的输入输出管脚有下面8种可能的配置：（4输入+2输出+2复用输出）
            ① 浮空输入_GPIO_Mode_IN_FLOATING 
            ② 带上拉输入GPIO_Mode_IPU
            ③ 带下拉输入GPIO_Mode_IPD
            ④ 模拟输入 GPIO_Mode_AIN
            ⑤ 开漏输出 GPIO_Mode_Out_OD
            ⑥ 推挽输出 GPIO_Mode_Out_PP
            ⑦ 复用功能的推挽输出GPIO_Mode_AF_PP 
            ⑧ 复用功能的开漏输出 GPIO_Mode_AF_OD*/                        
        /*设置引脚速率为50MHz */   
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   // 设置引脚速率为50MHz 
        GPIO_Init(GPIOB, &GPIO_InitStructure);                              //初始化函数	  
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_3;		 			
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOB, GPIO_Pin_5);                                    //上电复位高电平 
        GPIO_SetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_6);                       //上电复位高电平 

	/*****************KEYGIOPconfig**********************/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

