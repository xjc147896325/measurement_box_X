#ifndef   _drawTFT_H
#define   _drawTFT_H

#define RGB565(r, g, b) ((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3))          //颜色计算函数

#define RED   RGB565(255,0,0)		//红色
#define GREEN RGB565(0,255,0)		//绿色
#define BLUE  RGB565(0,0,255)		//蓝色
#define BLACK RGB565(0,0,0)		//黑色
#define WHITE RGB565(255,255,255)	//白色


/*********函数声明区******************/
void SSD1963_Draw_Point(u16 x,u16 y,u16 color);             //画点函数
void SSD1963_CLEAR(u16 color);                              //清屏函数
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);             //画圆函数
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);//画线函数
void Show_Str(u16 x,u16 y,u16 qj,u8 id);            //写一个字符串
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void TFT_Draw_Rectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

#endif




