#include "include.h"

u8 USART1_RX_BUF[64];  	                                                       //接收缓冲,最大64个字节
u8 USART1_RX_CNT;                                                              //接收字节计数器
u8 flagFrame = 0;                                                              //帧接收完成标志，即接收到一帧新数据
u8 feedback_data[40]={"已接收到数据长度为  个\r\n"};  	                                                       //反馈信息
unsigned char regGroup[5];  //Modbus寄存器组，地址为0x00～0x04

int fputc(int ch,FILE *f)                         //输出printf语句配置
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


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

void usart_Configuration(u32 boot)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);                     //打开usart1的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //打开复用功能时钟
    GPIO_InitTypeDef GPIO_InitStructure;	                              //定义一个GPIO_InitTypeDef类型的结构体
    USART_InitTypeDef  USART_InitStructure;                                   //定义一个USART_InitTypeDef类型的结构体
    NVIC_InitTypeDef NVIC_InitStructure;                                      //定义一个NVIC_InitTypeDef类型的结构体
    //USART 发送端口配置
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;                                   //TX：发送端口
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                           //口限速度50MHZ
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;                             //复用功能的推挽输出
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //初始化
    //USART 接受端口配置
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;                                  //RX:接收端
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;                       //浮空输入模式
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //初始化
    //USART1 串口设置
    USART_InitStructure.USART_BaudRate=boot;                                  //波特率的设置
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                 //数据位为8位
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                      //一位停止位
    USART_InitStructure.USART_Parity=USART_Parity_No;                         //无校验位
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件流控制
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;               //收发模式
    USART_Init(USART1,&USART_InitStructure);                                  //初始化串口
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                              //开启中断响应
    USART_Cmd(USART1,ENABLE);                                                 //使能串口配置
    USART_ClearFlag(USART1,USART_FLAG_TC);                                    //清除串口标志位
    //usart 中断配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                           //选择中断优先级分组，此处选择0。使0级抢占式优先级，16级亚优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                         //设置USAET1 为中断入口
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                 //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                        //亚优先级配置
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                           //使能通道
    NVIC_Init(&NVIC_InitStructure);                                           //初始化结构体 
}

/*******************************************************************************
* 函数名称: UartRxMonitor
* 函数功能: USART1串口监控函数
* 参数变量: u8 ms  时间监控设置，这里为1ms后则表示一帧数据接收完成
* 全局变量: NONE
* 调用函数: 在定时器2中调用，1ms调用一次监控一次
* 作    者: 董自祝 
* 编写时间: 2014-11-6
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/
void Usart1RxMonitor(u8 ms)    
{
    static u8 USART1_RX_BKP = 0;                                               //定义USART1_RX_BKP暂时存储数据长度与实际长度比较
    static u8 idletmr = 0;                                                     //定义监控时间

    if (USART1_RX_CNT > 0)                                                     //接收计数器大于零时，监控总线空闲时间
    {
        if (USART1_RX_BKP != USART1_RX_CNT)                                    //接收计数器改变，即刚接收到数据时，清零空闲计时
        {
            USART1_RX_BKP = USART1_RX_CNT;                                     //赋值操作，将实际长度给USART1_RX_BKP
            idletmr = 0;                                                       //将监控时间清零
        }
        else                                                                   //接收计数器未改变，即总线空闲时，累积空闲时间
        {
            if (idletmr < 2)                                                   //空闲计时小于1ms时，持续累加
            {
                idletmr += ms;
                if (idletmr >= 1)                                              //空闲时间达到1ms时，即判定为一帧接收完毕
                {
                    flagFrame = 1;                                             //设置帧接收完成标志
                }
            }       
        }
    }
    else
    {
        USART1_RX_BKP = 0;
    }
}
/*******************************************************************************
* 函数名称: UartRead
* 函数功能: 计算发送的数据长度，并且将数据存放到*buf数组中
* 参数变量: u8 *buf 指针数组  u8 len 指针数组的长度
* 全局变量: NONE
* 调用函数:  len = UartRead(buf, sizeof(buf));
* 作    者: 董自祝 
* 编写时间: 2014-11-6
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/

u8 UartRead(u8 *buf, u8 len)
{
    u8  i;
    if (len > USART1_RX_CNT)                                                   //指定读取长度大于实际接收到的数据长度时，
    {                                                 
        len = USART1_RX_CNT;                                                   //读取长度设置为实际接收到的数据长度
    }
    for (i=0; i<len; i++)                                                      //拷贝接收到的数据到接收指针上
    {
        *buf++ = USART1_RX_BUF[i];                                             //将数据复制到buf中
    }
    USART1_RX_CNT = 0;                                                         //接收计数器清零
    return len;                                                                //返回实际读取长度
}
/* 串口驱动函数，监测数据帧的接收，调度功能函数，需在主循环中调用 */
void UartDriver(void)
{ 
    unsigned char i,cnt;
    unsigned int  crc;
    unsigned char crch, crcl;
    static u8 len;
    static u8  buf[60];
   if(flagFrame>0)                                                            //帧接收完成标志，即接收到一帧新数据    
    {
      flagFrame = 0;                                                           //帧接收完成标志清零
      len = UartRead(buf, sizeof(buf));                                        //将接收到的命令读取到缓冲区中
      if(buf[0]==0x01)                                                         //判断地址是不是01
      {
        crc = GetCRC16(buf, len-2); //计算CRC校验值
        crch = crc >> 8;
        crcl = crc & 0xFF;
          if ((buf[len-2] == crch) && (buf[len-1] == crcl)) //判断CRC校验是否正确
           {
              switch (buf[1]) //按功能码执行操作
              {
                    case 0x03:  //读取一个或连续的寄存器
                        if ((buf[2] == 0x00) && (buf[3] <= 0x05)) //寄存器地址支持0x0000～0x0005
                        {
                            if (buf[3] <= 0x04)
                            {
                                i = buf[3];      //提取寄存器地址
                                cnt = buf[5];    //提取待读取的寄存器数量
                                buf[2] = cnt*2;  //读取数据的字节数，为寄存器数*2，因Modbus定义的寄存器为16位
                                len = 3;
                                while (cnt--)
                                {
                                    buf[len++] = 0x00;          //寄存器高字节补0
                                    buf[len++] = regGroup[i++]; //寄存器低字节
                                }
                            }
                            else  //地址0x05为蜂鸣器状态
                            {
                                buf[2] = 2;  //读取数据的字节数
                                buf[3] = 0x00;
                                buf[4] = 0;
                                len = 5;
                            }
                            break;
                        }
                        else  //寄存器地址不被支持时，返回错误码
                        {
                            buf[1] = 0x83;  //功能码最高位置1
                            buf[2] = 0x02;  //设置异常码为02-无效地址
                            len = 3;
                            break;
                        }
                    case 0x06:  //写入单个寄存器
                        if ((buf[2] == 0x00) && (buf[3] <= 0x05)) //寄存器地址支持0x0000～0x0005
                        {
                            if (buf[3] <= 0x04)
                            {
                                i = buf[3];             //提取寄存器地址
                                regGroup[i] = buf[5];   //保存寄存器数据
                                cnt = regGroup[i] >> 4; //显示到液晶上
                            }
                            len -= 2; //长度-2以重新计算CRC并返回原帧
                            break;
                        }
                        else  //寄存器地址不被支持时，返回错误码
                        {
                            buf[1] = 0x86;  //功能码最高位置1
                            buf[2] = 0x02;  //设置异常码为02-无效地址
                            len = 3;
                            break;
                        }
                        
                    default:  //其它不支持的功能码
                        buf[1] |= 0x80;  //功能码最高位置1
                        buf[2] = 0x01;   //设置异常码为01-无效功能
                        len = 3;
                        break;
                        
                        
                        
              }
                crc = GetCRC16(buf, len); //计算CRC校验值
                buf[len++] = crc >> 8;    //CRC高字节
                buf[len++] = crc & 0xFF;  //CRC低字节
                rs485_UartWrite(buf, len);      //发送响应帧
             
           }
 
      }
      
      
/*    printf("已接收到数据长度为:%d\r\n",len);
      Uart_length(feedback_data,len);                                          //发送接收数据的长度
      LCD_ShowString(20,200,200,12,16,buf);                                    //将buf中的数据写到
      for(i=0;i<=len;i++)                                                      //将buf数组清零
      {
      buf[i]=' ';
      }
*/      
    }   
}

