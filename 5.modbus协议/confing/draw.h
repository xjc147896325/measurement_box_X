#ifndef   _drawTFT_H
#define   _drawTFT_H

#define RGB565(r, g, b) ((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3))          //��ɫ���㺯��

#define RED   RGB565(255,0,0)		//��ɫ
#define GREEN RGB565(0,255,0)		//��ɫ
#define BLUE  RGB565(0,0,255)		//��ɫ
#define BLACK RGB565(0,0,0)		//��ɫ
#define WHITE RGB565(255,255,255)	//��ɫ


/*********����������******************/
void SSD1963_Draw_Point(u16 x,u16 y,u16 color);             //���㺯��
void SSD1963_CLEAR(u16 color);                              //��������
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);             //��Բ����
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);//���ߺ���
void Show_Str(u16 x,u16 y,u16 qj,u8 id);            //дһ���ַ���
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void TFT_Draw_Rectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

#endif




