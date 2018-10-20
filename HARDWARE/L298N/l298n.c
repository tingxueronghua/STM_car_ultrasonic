#include "l298n.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

//初始化电机
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//开启引脚时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |
																GPIO_Pin_4 | GPIO_Pin_5  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //使用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //配置输出功率
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | 
												GPIO_Pin_4 | GPIO_Pin_5 );
}


//控制pwm输出
void TIM4_PWM_Init_L(u16 value) 
{   
  TIM_TimeBaseInitTypeDef TIM_Timeinit;
  TIM_OCInitTypeDef TIM_OCInitstruct;
         
  GPIO_InitTypeDef GPIO_InitStrucyure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //使能定时器4时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB
 
 
  GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;  //改为复用推挽输出
  GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_6;
  GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStrucyure);          //初始化IO口
     
 
	TIM_Timeinit.TIM_ClockDivision = TIM_CKD_DIV1 ; 
	TIM_Timeinit.TIM_CounterMode =  TIM_CounterMode_Up; //设置计数模式
				
	TIM_Timeinit.TIM_Prescaler = 0;           //预分频系数为0，即为不分频
	TIM_Timeinit.TIM_Period = 7199;		//  72MHZ /(7199+1) = 10KHZ  7199 为计数总数
	TIM_TimeBaseInit(TIM4,&TIM_Timeinit); 
 
	TIM_OCInitstruct.TIM_Pulse = value;         //占空比0-7199
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;   //模式2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //极性输出高
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;     
 
	TIM_OC1Init(TIM4,&TIM_OCInitstruct);        //TIM_OCX   通道1
     
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
  			
	TIM_Cmd(TIM4,ENABLE);  //使能定时器
     
}

void TIM4_PWM_Init_R(u16 value) 
{   
  TIM_TimeBaseInitTypeDef TIM_Timeinit;
  TIM_OCInitTypeDef TIM_OCInitstruct;
         
  GPIO_InitTypeDef GPIO_InitStrucyure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //使能定时器4时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB
 
 
  GPIO_InitStrucyure.GPIO_Mode=GPIO_Mode_AF_PP;  //改为复用推挽输出
  GPIO_InitStrucyure.GPIO_Pin=GPIO_Pin_7;
  GPIO_InitStrucyure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStrucyure);          //初始化IO口
     
 
	TIM_Timeinit.TIM_ClockDivision = TIM_CKD_DIV1 ; 
	TIM_Timeinit.TIM_CounterMode =  TIM_CounterMode_Up; //设置计数模式
				
	TIM_Timeinit.TIM_Prescaler = 0;           //预分频系数为0，即为不分频
	TIM_Timeinit.TIM_Period = 7199;		//  72MHZ /(7199+1) = 10KHZ  7199 为计数总数
	TIM_TimeBaseInit(TIM4,&TIM_Timeinit); 
 
	TIM_OCInitstruct.TIM_Pulse = value;         //占空比0-7199
	TIM_OCInitstruct.TIM_OCMode =   TIM_OCMode_PWM2 ;   //模式2
	TIM_OCInitstruct.TIM_OCNPolarity  = TIM_OCPolarity_High ;   //极性输出高
	TIM_OCInitstruct.TIM_OutputState = TIM_OutputState_Enable ;     
 
	TIM_OC2Init(TIM4,&TIM_OCInitstruct);        //TIM_OCX   通道2
     
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
  			
	TIM_Cmd(TIM4,ENABLE);  //使能定时器
     
}

//3对基本的电机控制函数
void Motor_Stop(void)
{
	IN1(High);
	IN2(High);
	IN3(High);
	IN4(High);
}

void Motor_Run(void)
{
	IN1(Low);
	IN2(High);
	IN3(Low);
	IN4(High);
}

void Motor_NRun(void)
{
	IN1(High);
	IN2(Low);
	IN3(High);
	IN4(Low);
}

void Motor_Left(void)
{
	IN1(Low);
	IN2(High);
	IN3(High);
	IN4(Low);
}
void Motor_Right(void)
{
	IN1(High);
	IN2(Low);
	IN3(Low);
	IN4(High);
}

//码盘读取
void Encoder_Init(void) //PA0(TIM2 CH1),PA1(TIM2 CH2)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler=0x0;
    TIM_TimeBaseStructure.TIM_Period=TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//使用编码器模式3

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter=10;
    TIM_ICInit(TIM2,&TIM_ICInitStructure);
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    TIM_SetCounter(TIM2,0);
    TIM_Cmd(TIM2,ENABLE);
}

int Read_Encoder(void)
{
    int Encoder_TIM;    
        Encoder_TIM= (short)TIM2 -> CNT;  
        TIM2 -> CNT=0; 
        return Encoder_TIM;
}

