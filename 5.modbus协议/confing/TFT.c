#include "include.h"


//д�Ĵ�������
//index:�Ĵ���ֵ
void LCD_WR_REG(u16 index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;
}	

//���Ĵ���
//val  :�Ĵ�����ַ
//����ֵ:����������
void LCD_WR_Data(u16 val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}
//д�Ĵ���
//index:�Ĵ�����ַ
//val  :Ҫд�������
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
    
    LCD_WR_REG(0x00E2);	           //PLL ��Ƶ��120M   PLL=10*36/3=120M
    LCD_WR_Data(0x0023);	   //���ñ�Ƶ�� M   0x2c for 8M //Ϊ6.5��,N = 0 x36 0 x23 10�׾���
    LCD_WR_Data(0x0002);           //���÷�Ƶ�� N
    LCD_WR_Data(0x0004);           //ʹ��MN   PLL = INCLK*(M+1) / (N+1)  PLL ��Ƶ��120M PLL=8*44/3=120M
    
    LCD_WR_REG(0x00E0);            //0XE0��PLLʹ�ܼĴ���
    LCD_WR_Data(0x0001);           //�ȿ���PLL
    Delay(0xAFFFF);
    LCD_WR_REG(0x00E0);            //��Ҫһ��
    LCD_WR_Data(0x0003);           // ʹ�� PLL��Ϊʱ��
    Delay(0xAFFFF);
    LCD_WR_REG(0x0001);            // �����λ
    Delay(0xAFFFF);
    LCD_WR_REG(0x00E6);	           //���໷����PCLK,ȡ���ڷֱ���0XE6����������ʱ�ӵļĴ��� 
    LCD_WR_Data(0x0001);           //�ҵ���Ļ��4.3�磬���Ƶ�ʾͿ����ˣ������Ļ�Ƚϴ�����˸�Ļ��������ټӴ�
    LCD_WR_Data(0x0033);
    LCD_WR_Data(0x0032);            //����˵�ˣ��Ĵ���ָ���8λ����ģ����������ʱ����Ҫ3���ֽ������ã���λ��ǰ
    
    LCD_WR_REG(0x00B0);	            //����LCD��ʾģʽ���ֱ���
    LCD_WR_Data(0x0000);
    LCD_WR_Data(0x0000);            //TFTģʽ
    LCD_WR_Data((HDP>>8)&0X00FF);   //Set HDP ˮƽ��С
    LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);   //Set VDP  ��ֱ�ߴ�
    LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);            //RGB˳����TFT�ӿ�
    
    LCD_WR_REG(0x00B4);	            //����  ˮƽ��ʾʱ�����
    LCD_WR_Data((HT>>8)&0X00FF);    //Set HTˮƽ������
    LCD_WR_Data(HT&0X00FF);
    LCD_WR_Data((HPS>>8)&0X00FF);   //Set HPS ˮƽͬ�����忪ʼλ
    LCD_WR_Data(HPS&0X00FF);
    LCD_WR_Data(HPW);	            //Set HPW ˮƽͬ��������
    LCD_WR_Data((LPS>>8)&0X00FF);   //Set HPS
    LCD_WR_Data(LPS&0X00FF);
    LCD_WR_Data(0x0000);            //TFT mode�£��������
    
    LCD_WR_REG(0x00B6);             //���ô�ֱ��ʾʱ�����
    LCD_WR_Data((VT>>8)&0X00FF);    //Set VT
    LCD_WR_Data(VT&0X00FF);         //Set VT ��ֱ������
    LCD_WR_Data((VPS>>8)&0X00FF);   //Set VPS ��ֱͬ�����忪ʼλ
    LCD_WR_Data(VPS&0X00FF);
    LCD_WR_Data(VPW);	            //Set VPW��ֱͬ��������
    LCD_WR_Data((FPS>>8)&0X00FF);   //Set FPS��ʾ��ʼλ��
    LCD_WR_Data(FPS&0X00FF);
    
    LCD_WR_REG(0x00BA);
    LCD_WR_Data(0x000F);           //GPIO[3:0] out 1
    
    LCD_WR_REG(0x00B8);
    LCD_WR_Data(0x0007);          //GPIO3=input, GPIO[2:0]=output
    LCD_WR_Data(0x0001);          //GPIO0 normal
    
    LCD_WR_REG(0x0036);          //rotation
    LCD_WR_Data(0x0000);
    
    LCD_WR_REG(0x00F0);          //16λ  565ģʽ
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
    
    LCD_WR_REG(0x00d0);          //���ö�̬����������� 
    LCD_WR_Data(0x000d);
    
    LCD_WR_REG(0x002A);	
    LCD_WR_Data(0);	    
    LCD_WR_Data(0);
    LCD_WR_Data((480-1)>>8);	    
    LCD_WR_Data((480-1));
    LCD_WR_REG(0x002b);	
    LCD_WR_Data(0);	    
    LCD_WR_Data(0);
    LCD_WR_Data((272-1)>>8);	//(0x0080);//���Ͷ�ֵ  //    
    LCD_WR_Data((272-1));//���������
    LCD_WR_REG(0x002c);
    w=(480)*(272);
    while(w--)
    LCD_WR_Data(0xFFFF);	//ˢ�ɰ�ɫ
}

