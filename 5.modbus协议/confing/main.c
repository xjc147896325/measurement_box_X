#include "include.h"


void main(void)
{      
    RCC_Configuration();	                  //ϵͳʱ�ӳ�ʼ��
    FSMC_LCD_Init();                              //FSMC�ӿڳ�ʼ��
    SSD1963_Init();                               //SSD1963оƬ��ʼ��
    LCD_DrawLine(0,0,100,100,RED);                //���ߺ���
    Draw_Circle(100,100,50,RED);                  //��Բ����
   // LCD_ShowString(20,200,200,16,16,"dongzizhu");//д�ַ���
    delay_ms(1000);                               //��ʱһ��
    
    usart_Configuration(115200);                  //usart���ڳ�ʼ����������Ϊ115200
    rs485_Configuration(115200);
    TIMER_Configuration();                        //��ʱ��3����   ������ں���
    GPIO_Configuration();                         //�˿ڳ�ʼ��
   while(1)   
   {   
    UartDriver(); 
   }
}
