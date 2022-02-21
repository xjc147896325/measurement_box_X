#ifndef _RS485_H
#define _RS485_H

void rs485_Configuration(u32 boot);
void rs485_UartWrite(unsigned char *buf, unsigned char len); //串口数据写入函数，即串口发送函数，待发送数据指针buf，数据长度len
void Uart_length(unsigned char *buf, unsigned char len);

#endif