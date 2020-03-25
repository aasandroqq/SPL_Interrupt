#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


#define 		LCD_PORT							GPIOE
#define     LCD_PIN_RS            GPIO_Pin_7  
#define     LCD_PIN_RW            GPIO_Pin_10
#define     LCD_PIN_EN            GPIO_Pin_11          
#define     LCD_PIN_D7            GPIO_Pin_15         
#define     LCD_PIN_D6            GPIO_Pin_14          
#define     LCD_PIN_D5            GPIO_Pin_13         
#define     LCD_PIN_D4            GPIO_Pin_12         
#define     LCD_PIN_MASK  				((LCD_PIN_RS | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4))
#define 		LCD_PIN_OFFSET  			12

void LCD_Init(void);
void ClearLCD(void);
void LCD_Write_Byte(uint8_t data);
void LCD_Pin_Initialize(void);
void lcd_delay(unsigned int p);
void LCD_ShowStr(unsigned char *s);
void LCD_ShowChar(unsigned char c);

