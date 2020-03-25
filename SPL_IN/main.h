#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "LCD.h"
	

#define BUTTON_INFO() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
