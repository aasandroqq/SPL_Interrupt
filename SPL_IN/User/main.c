#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include <time.h>
#include <stdlib.h>

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

#define BUTTON_INFO() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

int value = -1;

char str1[] = "Hello";
char str2[] = "again";
char str3[] = "SPI";
char str4[] = "and";
char str5[] = "SPL";

uint16_t delay_count=0;
uint16_t status=0;

void SysTick_Handler(void)//1ms
{
	if (delay_count > 0){delay_count--;}
}

void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	while(delay_count){}
}

void h_drv_WH1602B_Pin_Initialize(void)
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

void h_drv_WH1602B_Write_Byte(uint8_t data)
{
	GPIO_SetBits(LCD_PORT, ((data & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(LCD_PORT, LCD_PIN_EN);
	lcd_delay(100);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_EN);// Data receive on falling edge
	GPIO_ResetBits(LCD_PORT, 0x0F<<LCD_PIN_OFFSET);
}
void Button_Init(void)
{
	GPIO_InitTypeDef GPIO_Init_Button;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_Init_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Button.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_Init_Button);
}
int RandomNumber(){
	srand(time(NULL));
	return rand()%5;
}

int main(void)
{
	LCD_Pin_Initialize();
	LCD_Init();
	SysTick_Config(SystemCoreClock/1000);
	
	while(1){
		delay_ms(2000);
		
			value = RandomNumber();
			switch(value){
				case 0 : LCD_ShowStr(str1);break;value = -1;
				case 1 : LCD_ShowStr(str2);break;value = -1;
				case 2 : LCD_ShowStr(str3);break;value = -1;
				case 3 : LCD_ShowStr(str4);break;value = -1;
				case 4 : LCD_ShowStr(str5);break;value = -1;
				default :  LCD_ShowStr("No data");break;
			}
			
		}
		delay_ms(2000);
}





