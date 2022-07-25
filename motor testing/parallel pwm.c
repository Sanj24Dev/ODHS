#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"


int main()
{
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //Enabling the AHB1 peripheral clock for GPIOE
	GPIO_InitTypeDef GPIO_InitStruct; // gpio structure
        
        //GPIO configuration	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;//| GPIO_Pin_11 | GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_TIM1);
        //GPIO_PinAFConfig(GPIOD, GPIO_PinSource11 , GPIO_AF_TIM1);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource13 , GPIO_AF_TIM1);
        GPIO_Init(GPIOE, &GPIO_InitStruct);
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//timer structure
        
        //time configuration
	TIM_TimeBaseInitStruct.TIM_Period = 8399;
        TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
        
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
       
	TIM_OCInitTypeDef TIM_OCStruct1,TIM_OCStruct3,TIM_OCStruct2;
	        
        //pwm configuration
	TIM_OCStruct1.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCStruct1.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCStruct1.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct1.TIM_Pulse = 8399;// 100% duty cycle 
        
        /*
	TIM_OCStruct3.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCStruct3.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCStruct3.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct3.TIM_Pulse = 0;// 25% duty cycle 
        
        TIM_OCStruct2.TIM_OCMode = TIM_OCMode_PWM2;
        TIM_OCStruct2.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCStruct2.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCStruct2.TIM_Pulse = 0;// 25% duty cycle 
  
        */
        
	
	TIM_OC1Init(TIM1, &TIM_OCStruct1);
        //TIM_OC3Init(TIM1, &TIM_OCStruct3);
	//TIM_OC2Init(TIM1, &TIM_OCStruct2);
        
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
        //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

        // TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
	//GPIO_SetBits(GPIOD, GPIO_Pin_12);
	TIM_Cmd(TIM1, ENABLE);
	
        
	while(1)
	{
          //GPIO_ToggleBits(GPIOE, GPIO_Pin_9);
          //for(int i=0;i<25000;i++){}
         /* 
          int count12,count14,count15,i;
          for(count12=0,count14=0,count15=0;count12<8399|count14<8399|count15<8399;count12+=10,count14+=50,count15+=100)
          {
                  TIM_OCStruct1.TIM_Pulse = count12;
                  TIM_OCStruct3.TIM_Pulse = count14;
                  TIM_OCStruct2.TIM_Pulse = count15;
                  TIM_OC1Init(TIM1, &TIM_OCStruct1);
                  TIM_OC3Init(TIM1, &TIM_OCStruct3);
                  TIM_OC2Init(TIM1, &TIM_OCStruct2);
                for(i=0;i<25000;i++){}
          }
          
          /*
          for(count12=8399,count15=0;count12>=0,count15<8399;count12-=10,count15+=10)
          {
           TIM_OCStruct1.TIM_Pulse = count12;
           TIM_OCStruct2.TIM_Pulse = count15;
           TIM_OC1Init(TIM4, &TIM_OCStruct1);				
           TIM_OC4Init(TIM4, &TIM_OCStruct2);
           for(i=0;i<25000;i++){}
          }
          */
       
          }
}
