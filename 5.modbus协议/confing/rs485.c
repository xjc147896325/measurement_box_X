#include "include.h"

/*******************************************************************************
* 函数名称:  usart_Configuration
* 函数功能:USART1 串口的设置
* 参数变量: u32 boot  波特率的设置
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-11-6
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/

void rs485_Configuration(u32 boot)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);                     //打开usart1的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //打开复用功能时钟
    GPIO_InitTypeDef GPIO_InitStructure;	                              //定义一个GPIO_InitTypeDef类型的结构体
    USART_InitTypeDef  USART_InitStructure;                                   //定义一个USART_InitTypeDef类型的结构体
    NVIC_InitTypeDef NVIC_InitStructure;                                      //定义一个NVIC_InitTypeDef类型的结构体
    //CS_485
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    //USART 发送端口配置
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;                                   //TX：发送端口
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                           //口限速度50MHZ
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;                             //复用功能的推挽输出
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //初始化
    //USART 接受端口配置
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;                                  //RX:接收端
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;                       //浮空输入模式
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //初始化
    //USART1 串口设置
    USART_InitStructure.USART_BaudRate=boot;                                  //波特率的设置
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                 //数据位为8位
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                      //一位停止位
    USART_InitStructure.USART_Parity=USART_Parity_No;                         //无校验位
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件流控制
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;               //收发模式
    USART_Init(USART2,&USART_InitStructure);                                  //初始化串口
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                              //开启中断响应
    USART_Cmd(USART2,ENABLE);                                                 //使能串口配置
    USART_ClearFlag(USART2,USART_FLAG_TC);                                    //清除串口标志位
    //usart 中断配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                           //选择中断优先级分组，此处选择0。使0级抢占式优先级，16级亚优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                         //设置USAET1 为中断入口
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                 //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                        //亚优先级配置
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                           //使能通道
    NVIC_Init(&NVIC_InitStructure);                                           //初始化结构体 
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                                         //拉低信号，使485处于接收状态
}

/*******************************************************************************
* 函数名称:  rs485_UartWrite
* 函数功能:485串口发送函数
* 参数变量: u32 boot  波特率的设置
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-11-16
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/
void rs485_UartWrite(u8 *buf ,u8 len)
{ u8 i=0; 
   GPIO_SetBits(GPIOE,GPIO_Pin_5);                                            //发送模式
   delay_ms(3);                                                               //3MS延
    for(i=0;i<=len;i++)
    {
	USART_SendData(USART2,buf[i]);	                                      //通过外设USARTx发送单个数据
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);             //检查指定的USART标志位设置与否 发送数据寄存器空标志位
    }
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                                         //设置接收模式

}
/*******************************************************************************
* 函数名称:  Uart_length
* 函数功能: 485串口发送数据长度计算函数
* 参数变量: *buf feedback_data  len 接收到的数据长度
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-11-16
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/
void Uart_length(unsigned char *buf, unsigned char len)
{
                                                                              //在接收到的数据帧后添加换车换行符后发回
      feedback_data[18]=0x30+len/10;                                          //将接收的字节高位位长度转化为ASCII形式
      feedback_data[19]=0x30+len%10;                                          //将接收的字节低位长度转化为ASCII形式
      rs485_UartWrite(buf, 23);
}

