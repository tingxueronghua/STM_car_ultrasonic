#include "stm32f10x_gpio.h"

void LED_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	/* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//ÍÆÍìÊä³ö
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	 GPIO_Init(GPIOD, &GPIO_InitStructure);
}
