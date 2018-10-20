#ifndef _L298N_H
#define _L298N_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define High 1		//��high,low��������
#define Low 0

#define TIM_PERIOD (u16)(65535)   
//���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ

//�ú���IN�������gpio
#define IN1(a) if (a)  \
	GPIO_SetBits(GPIOA,GPIO_Pin_2);\
else  \
	GPIO_ResetBits(GPIOA,GPIO_Pin_2)
 
#define IN2(a) if (a)  \
	GPIO_SetBits(GPIOA,GPIO_Pin_3);\
else  \
	GPIO_ResetBits(GPIOA,GPIO_Pin_3)
 
#define IN3(a) if (a)  \
	GPIO_SetBits(GPIOA,GPIO_Pin_4);\
else  \
	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
 
#define IN4(a) if (a)  \
	GPIO_SetBits(GPIOA,GPIO_Pin_5);\
else  \
	GPIO_ResetBits(GPIOA,GPIO_Pin_5)
 
void Motor_Init(void);
void TIM4_PWM_Init_L(u16 value);
void TIM4_PWM_Init_R(u16 value);
 
void Motor_Stop(void);
void Motor_Run(void);
void Motor_NRun(void);
 
void Motor_Left(void);
void Motor_Right(void);

void Encoder_Init(void);
int	Read_Encoder(void);


#endif
