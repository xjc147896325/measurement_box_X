#include "include.h"


//写寄存器函数
//index:寄存器值
void LCD_WR_REG(u16 index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;
}	

//读寄存器
//val  :寄存器地址
//返回值:读到的数据
void LCD_WR_Data(u16 val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}
//写寄存器
//index:寄存器地址
//val  :要写入的数据
void LCD_WR_CMD(u16 index,u16 val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void SSD1963_Init(void)
{		
    u32 w=0;
    u16 HDP=479;
    u16 HT=531;
    u16 HPS=43;
    u16 LPS=8;
    u16 VDP=271;
    u16 VT=288;
    u16 VPS=12;
    u16 FPS=4;
    u8 	HPW=1;
    u8	VPW=10;

    GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    Delay(0xAFFFF);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
    Delay(0xAFFFF);					   
    
    LCD_WR_REG(0x00E2);	           //PLL 倍频到120M   PLL=10*36/3=120M
    LCD_WR_Data(0x0023);	   //设置倍频数 M   0x2c for 8M //为6.5米,N = 0 x36 0 x23 10米晶体
    LCD_WR_Data(0x0002);           //设置分频数 N
    LCD_WR_Data(0x0004);           //使能MN   PLL = INCLK*(M+1) / (N+1)  PLL 倍频到120M PLL=8*44/3=120M
    
    LCD_WR_REG(0x00E0);            //0XE0是PLL使能寄存器
    LCD_WR_Data(0x0001);           //先开启PLL
    Delay(0xAFFFF);
    LCD_WR_REG(0x00E0);            //还要一次
    LCD_WR_Data(0x0003);           // 使用 PLL作为时钟
    Delay(0xAFFFF);
    LCD_WR_REG(0x0001);            // 软件复位
    Delay(0xAFFFF);
    LCD_WR_REG(0x00E6);	           //锁相环设置PCLK,取决于分辨率0XE6是设置像素时钟的寄存器 
    LCD_WR_Data(0x0001);           //我的屏幕是4.3寸，这个频率就可以了，如果屏幕比较大，有闪烁的话，可以再加大
    LCD_WR_Data(0x0033);
    LCD_WR_Data(0x0032);            //忘记说了，寄存器指令都是8位传输的，这里的像素时钟需要3个字节来设置，高位在前
    
    LCD_WR_REG(0x00B0);	            //设置LCD显示模式及分辨率
    LCD_WR_Data(0x0000);
    LCD_WR_Data(0x0000);            //TFT模式
    LCD_WR_Data((HDP>>8)&0X00FF);   //Set HDP 水平大小
    LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);   //Set VDP  垂直尺寸
    LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);            //RGB顺序串行TFT接口
    
    LCD_WR_REG(0x00B4);	            //设置  水平显示时间参数
    LCD_WR_Data((HT>>8)&0X00FF);    //Set HT水平总周期
    LCD_WR_Data(HT&0X00FF);
    LCD_WR_Data((HPS>>8)&0X00FF);   //Set HPS 水平同步脉冲开始位
    LCD_WR_Data(HPS&0X00FF);
    LCD_WR_Data(HPW);	            //Set HPW 水平同步脉冲宽度
    LCD_WR_Data((LPS>>8)&0X00FF);   //Set HPS
    LCD_WR_Data(LPS&0X00FF);
    LCD_WR_Data(0x0000);            //TFT mode下，如此设置
    
    LCD_WR_REG(0x00B6);             //设置垂直显示时间参数
    LCD_WR_Data((VT>>8)&0X00FF);    //Set VT
    LCD_WR_Data(VT&0X00FF);         //Set VT 垂直总周期
    LCD_WR_Data((VPS>>8)&0X00FF);   //Set VPS 垂直同步脉冲开始位
    LCD_WR_Data(VPS&0X00FF);
    LCD_WR_Data(VPW);	            //Set VPW垂直同步脉冲宽度
    LCD_WR_Data((FPS>>8)&0X00FF);   //Set FPS显示开始位置
    LCD_WR_Data(FPS&0X00FF);
    
    LCD_WR_REG(0x00BA);
    LCD_WR_Data(0x000F);           //GPIO[3:0] out 1
    
    LCD_WR_REG(0x00B8);
    LCD_WR_Data(0x0007);          //GPIO3=input, GPIO[2:0]=output
    LCD_WR_Data(0x0001);          //GPIO0 normal
    
    LCD_WR_REG(0x0036);          //rotation
    LCD_WR_Data(0x0000);
    
    LCD_WR_REG(0x00F0);          //16位  565模式
    LCD_WR_Data(0x0003);
    
    Delay(0xAFFFF);
    
    LCD_WR_REG(0x0029);          //display on
    LCD_WR_REG(0x00BE);          //set PWM for B/L
    LCD_WR_Data(0x0006);
    LCD_WR_Data(0x0080);
    
    LCD_WR_Data(0x0001);
    LCD_WR_Data(0x00f0);
    LCD_WR_Data(0x0000);
    LCD_WR_Data(0x0000);
    
    LCD_WR_REG(0x00d0);          //设置动态背光控制配置 
    LCD_WR_Data(0x000d);
    
    LCD_WR_REG(0x002A);	
    LCD_WR_Data(0);	    
    LCD_WR_Data(0);
    LCD_WR_Data((480-1)>>8);	    
    LCD_WR_Data((480-1));
    LCD_WR_REG(0x002b);	
    LCD_WR_Data(0);	    
    LCD_WR_Data(0);
    LCD_WR_Data((272-1)>>8);	//(0x0080);//饱和度值  //    
    LCD_WR_Data((272-1));//处理机允许
    LCD_WR_REG(0x002c);
    w=(480)*(272);
    while(w--)
    LCD_WR_Data(0xFFFF);	//刷成白色
}

