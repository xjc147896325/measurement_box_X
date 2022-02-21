#ifndef _USART_H
#define _USART_H

extern  u8 USART1_RX_BUF[64];  	      //接收缓冲,最大64个字节
extern  u8 USART1_RX_CNT;
extern  u8 flagFrame;  //帧接收完成标志，即接收到一帧新数据
extern  u8 feedback_data[]; //接收后反馈信息
int fputc(int ch,FILE *f);                         //输出printf语句配置
void usart_Configuration(u32 boot);
void Usart1RxMonitor(u8 ms);
u8 UartRead(u8 *buf, u8  len);
void UartDriver(void);

#endif 

