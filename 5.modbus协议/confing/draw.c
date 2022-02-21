#include "include.h"
/*******************************************************************************
* ��������:  SSD1963_Draw_Point
* ��������: SSD1963���㺯��
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���: ������������ͼ���߶��õ���
* ��    ��: ����ף 
* ��дʱ��: 2014-10-30
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void SSD1963_Draw_Point(u16 x,u16 y,u16 color)
{								       
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//��ʼ��ַX
	LCD_WR_Data(x);	    			
	LCD_WR_Data(x>>8);	    			//������ַX
	LCD_WR_Data(x);	    			    
        LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//��ʼ��ַY
	LCD_WR_Data(y);	    			    
	LCD_WR_Data(y>>8);	    			//������ַY
	LCD_WR_Data(y);	    			
	LCD_WR_REG(0x2c);
	LCD_WR_Data(color); 	   	
}
/*******************************************************************************
* ��������:  SSD1963_CLEAR
* ��������: SSD1963��������
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���: ����ʱ��������ĻΪһ����ɫ
* ��    ��: ����ף 
* ��дʱ��: 2014-10-30
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void SSD1963_CLEAR(u16 color)
{                    
    u16 i=0,j=0;
	                    
   	for(i=0;i<480;i++)
	{
		for(j=0;j<272;j++)
		{
		SSD1963_Draw_Point(i,j,color);
		}
	} 
}
/*******************************************************************************
* ��������:  Draw_Circle
* ��������: ��ָ��λ�û�һ��ָ����С��Բ
* ��������: (x,y):���ĵ�   r:�뾶   color ��ɫ
* ���ú���: ��480*272��Ļ�ϻ�Բ
* ��    ��: ����ף 
* ��дʱ��: 2014-10-30
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		SSD1963_Draw_Point(x0+a,y0-b,color);             //5
 		SSD1963_Draw_Point(x0+b,y0-a,color);             //0           
		SSD1963_Draw_Point(x0+b,y0+a,color);             //4               
		SSD1963_Draw_Point(x0+a,y0+b,color);             //6 
		SSD1963_Draw_Point(x0-a,y0+b,color);             //1       
 		SSD1963_Draw_Point(x0-b,y0+a,color);             
		SSD1963_Draw_Point(x0-a,y0-b,color);             //2             
  		SSD1963_Draw_Point(x0-b,y0-a,color);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
/*******************************************************************************
* ��������:  Draw_Circle
* ��������: ��ָ��λ�û�һ����
* ��������: //x1,y1:�������  //x2,y2:�յ����� //color  ��ɫ
* ���ú���: ��480*272��Ļ�ϻ���
* ��    ��: ����ף 
* ��дʱ��: 2014-10-30
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
          SSD1963_Draw_Point(uRow,uCol,color);//���� 
          xerr+=delta_x ; 
          yerr+=delta_y ; 
          if(xerr>distance) 
          { 
                  xerr-=distance; 
                  uRow+=incx; 
          } 
          if(yerr>distance) 
          { 
                  yerr-=distance; 
                  uCol+=incy; 
          } 
	}  
}    

/*******************************************************************************
* ��������:  Show_Str
* ��������: ��ָ��λ��дһ���ַ�
* ��������: //x1,y1:�������  
* ���ú���: ��480*272��Ļ��дһ���ַ�
* ��    ��: ����ף 
* ��дʱ��: 2014-10-30
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void Show_Str(u16 x,u16 y,u16 qj,u8 id)
{
	u8 temp,k,t;
	u8 y0=y;
	id=id-' ';                                                        //�õ�ƫ�ƺ��ֵ
	for(k=0;k<16;k++)
        {   												   
	    temp=asc2_1608[id][k];                          
        for(t=0;t<8;t++)
		{
                    if(temp&0x80)
                            SSD1963_Draw_Point(x,y,qj);
                    else 				
                            SSD1963_Draw_Point(x,y,WHITE);
                    
                    temp<<=1;
                    y++;
                    if((y-y0)==16)
                    {
                            y=y0;
                            x++;
                            break;
                    }
		}  	 
	 }	 
}
/*******************************************************************************
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//p:�ַ�����ʼ��ַ		  
*******************************************************************************/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
    u8 x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        Show_Str(x,y,RED,*p);
        x+=size/2;
        p++;
    }  
}

void TFT_Draw_Rectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 i,j;
	for(i=x1;i<x2;i++)
	{
		for(j=y1;j<y2;j++)
		{
			SSD1963_Draw_Point(i, j,color); 
		}
	}
}
