#include "LCD.h"

const unsigned char lcd_addLUT[2] = {0x80, 0xC0};
unsigned char lcd_Address, lcd_Line;

void lcd_delay(unsigned int p)
{
	unsigned long i;
	for(i=0;i<(p*10);i++){
	__nop();
	}
}

void LCD_Pin_Initialize(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = LCD_PIN_RS | LCD_PIN_RW | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_RW);
}


void LCD_Write_Byte(uint8_t data)
{
	GPIO_SetBits(LCD_PORT, (((data>>4) & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(LCD_PORT, LCD_PIN_EN);
	lcd_delay(100);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_EN);
	GPIO_ResetBits(LCD_PORT, 0x0F<<LCD_PIN_OFFSET);
	
	GPIO_SetBits(LCD_PORT, ((data & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(LCD_PORT, LCD_PIN_EN);
	lcd_delay(100);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_EN);
	GPIO_ResetBits(LCD_PORT, 0x0F<<LCD_PIN_OFFSET);
}
void LCD_GoToLine(char LineNum)
{
	GPIO_ResetBits(LCD_PORT, LCD_PIN_RS);
	lcd_Address = lcd_addLUT[LineNum-1];
	LCD_Write_Byte(lcd_Address);
	GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
	lcd_Address = 0;
	lcd_Line = LineNum;
}
void ClearLCD(void)
{
	GPIO_ResetBits(LCD_PORT, LCD_PIN_RS);
	LCD_Write_Byte(0x01);
	lcd_delay(100);
	GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
	LCD_GoToLine(1);
}

void LCD_ShowChar(unsigned char c)
{
	GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
	LCD_Write_Byte(c);
	lcd_Address++;
	switch (lcd_Address)
	{
		case 20: LCD_GoToLine(2); break;
		case 40: LCD_GoToLine(3); break;
		case 60: LCD_GoToLine(4); break;
		case 80: LCD_GoToLine(1); break;
	}
}

void LCD_ShowStr(unsigned char *s)
{
	while (*s != 0) LCD_ShowChar(*s++);
}

void LCD_Init(void)
{
	LCD_Write_Byte(0x20);
	lcd_delay(100);
	LCD_Write_Byte(0x28);
	lcd_delay(100);
	LCD_Write_Byte(0x28);
	lcd_delay(100);
	LCD_Write_Byte(0x0f);
	lcd_delay(100);
	LCD_Write_Byte(0x01);
	lcd_delay(100);
	LCD_Write_Byte(0x06);
	lcd_delay(100);
}


