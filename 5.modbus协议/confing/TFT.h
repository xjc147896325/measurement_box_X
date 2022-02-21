#ifndef _TFT_H
#define _TFT_H

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR


void SSD1963_Init(void);
void LCD_WR_REG(u16 index);
void LCD_WR_CMD(u16 index,u16 val);
void LCD_WR_Data(u16 val);
#endif
