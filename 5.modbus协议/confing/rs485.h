#ifndef _RS485_H
#define _RS485_H

void rs485_Configuration(u32 boot);
void rs485_UartWrite(unsigned char *buf, unsigned char len); //��������д�뺯���������ڷ��ͺ���������������ָ��buf�����ݳ���len
void Uart_length(unsigned char *buf, unsigned char len);

#endif