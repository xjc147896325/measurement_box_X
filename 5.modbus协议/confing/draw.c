#include "include.h"
/*******************************************************************************
* 函数名称:  SSD1963_Draw_Point
* 函数功能: SSD1963画点函数
* 参数变量: NONE
* 全局变量: NONE
* 调用函数: 基础函数，画图画线都得调用
* 作    者: 董自祝 
* 编写时间: 2014-10-30
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void SSD1963_Draw_Point(u16 x,u16 y,u16 color)
{								       
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//起始地址X
	LCD_WR_Data(x);	    			
	LCD_WR_Data(x>>8);	    			//结束地址X
	LCD_WR_Data(x);	    			    
        LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//起始地址Y
	LCD_WR_Data(y);	    			    
	LCD_WR_Data(y>>8);	    			//结束地址Y
	LCD_WR_Data(y);	    			
	LCD_WR_REG(0x2c);
	LCD_WR_Data(color); 	   	
}
/*******************************************************************************
* 函数名称:  SSD1963_CLEAR
* 函数功能: SSD1963清屏函数
* 参数变量: NONE
* 全局变量: NONE
* 调用函数: 清屏时或者让屏幕为一个颜色
* 作    者: 董自祝 
* 编写时间: 2014-10-30
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
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
* 函数名称:  Draw_Circle
* 函数功能: 在指定位置画一个指定大小的圆
* 参数变量: (x,y):中心点   r:半径   color 颜色
* 调用函数: 在480*272屏幕上画圆
* 作    者: 董自祝 
* 编写时间: 2014-10-30
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
/*******************************************************************************
* 函数名称:  Draw_Circle
* 函数功能: 在指定位置画一条线
* 参数变量: //x1,y1:起点坐标  //x2,y2:终点坐标 //color  颜色
* 调用函数: 在480*272屏幕上画线
* 作    者: 董自祝 
* 编写时间: 2014-10-30
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
          SSD1963_Draw_Point(uRow,uCol,color);//画点 
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
* 函数名称:  Show_Str
* 函数功能: 在指定位置写一个字符
* 参数变量: //x1,y1:起点坐标  
* 调用函数: 在480*272屏幕上写一个字符
* 作    者: 董自祝 
* 编写时间: 2014-10-30
* 修改时间: 
* 版    本: V0.0 
* 状    态:调试完成
*******************************************************************************/

void Show_Str(u16 x,u16 y,u16 qj,u8 id)
{
	u8 temp,k,t;
	u8 y0=y;
	id=id-' ';                                                        //得到偏移后的值
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
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//p:字符串起始地址		  
*******************************************************************************/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
    u8 x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
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
