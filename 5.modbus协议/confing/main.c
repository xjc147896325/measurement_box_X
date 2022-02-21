#include "include.h"


void main(void)
{      
    RCC_Configuration();	                  //系统时钟初始化
    FSMC_LCD_Init();                              //FSMC接口初始化
    SSD1963_Init();                               //SSD1963芯片初始化
    LCD_DrawLine(0,0,100,100,RED);                //划线函数
    Draw_Circle(100,100,50,RED);                  //画圆函数
   // LCD_ShowString(20,200,200,16,16,"dongzizhu");//写字符串
    delay_ms(1000);                               //延时一下
    
    usart_Configuration(115200);                  //usart串口初始化。波特率为115200
    rs485_Configuration(115200);
    TIMER_Configuration();                        //定时器3配置   必须放在后面
    GPIO_Configuration();                         //端口初始化
   while(1)   
   {   
    UartDriver(); 
   }
}
