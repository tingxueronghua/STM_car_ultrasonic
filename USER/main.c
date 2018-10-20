#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "led.h"

#include "l298n.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "sys.h"
#include "hcsr04.h"


 int main(void)
 {
	 float result=0;
	 // the result is used to accept the data from ultrasonic
   int rrr; 	 
 
	 Motor_Init();
	 delay_init();
	 LED_Init();
	 KEY_Init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200);    
	 // I don't know what happened, but Chinese will end up with strange things. I don't know what 115200 means.
	 
	 NVIC_Configuration();
	 GPIO_Configuration();
	 TIM_Configuration();
	 
	 Encoder_Init();
	 
	 GPIO_SetBits(GPIOD,GPIO_Pin_2); //让小灯亮以表示程序正常烧录
	 
	 while(1)
	 {
		 result=Sensor_using();
	 }
	 // this is the interface of the ultrasonic
	 
	 while(1)
	 {
		 
		 TIM4_PWM_Init_L(2000);		 
		 TIM4_PWM_Init_R(2000);
		 Motor_Run();
		 rrr = Read_Encoder();
		 
		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
		 
		 TIM4_PWM_Init_L(3000);		 
		 TIM4_PWM_Init_R(3000);
		 Motor_Left();
		 rrr = Read_Encoder();

		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
		 
		 TIM4_PWM_Init_L(5000);		 
		 TIM4_PWM_Init_R(5000);
		 Motor_Right();
		 rrr = Read_Encoder();
		 
		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
		 
		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
		 
		 Motor_NRun();
		 
		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
		 
		 Motor_Stop();
		 
		 delay_ms(10000);
		 delay_ms(10000);
		 delay_ms(10000);
	 }
 }

