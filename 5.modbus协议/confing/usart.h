#ifndef _USART_H
#define _USART_H

extern  u8 USART1_RX_BUF[64];  	      //���ջ���,���64���ֽ�
extern  u8 USART1_RX_CNT;
extern  u8 flagFrame;  //֡������ɱ�־�������յ�һ֡������
extern  u8 feedback_data[]; //���պ�����Ϣ
int fputc(int ch,FILE *f);                         //���printf�������
void usart_Configuration(u32 boot);
void Usart1RxMonitor(u8 ms);
u8 UartRead(u8 *buf, u8  len);
void UartDriver(void);

#endif 

