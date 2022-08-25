/**
  ******************************************************************************
  * @file    TIM/TIM_ComplementarySignals/main.c 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 0 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_ComplementarySignals
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
NVIC_InitTypeDef        NVIC_InitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0;
int h1, h2, h3;
__IO uint32_t uwStep = 1;
/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);
static void SysTickConfig(void);
/* Private functions ---------------------------------------------------------*/

int getStep(int h1, int h2, int h3)
{
  
  switch(h1)
  {
      case 0:
          switch(h2)
          {
              case 0:
                  switch(h3)
                  {
                      case 0:
                          
                          return 0;
                      break;
                      case 1:
                          return 3;
                      break;
                  }
              case 1:
                  switch(h3)
                  {
                      case 0:
                          return 5; 
                      break;
                      case 1:
                          return 4;
                      break;
                  }
          }
      case 1:
          switch(h2)
          {
              case 0:
                  switch(h3)
                  {
                      case 0:
                          return 1;
                      break;
                      case 1:
                          return 2;
                      break;
                  }
              case 1:
                  switch(h3)
                  {
                      case 0:
                          return 6;
                      break;
                      case 1:
                          return 0;
                      break;
                  }
          }

  }
}


void commute(int h1,int h2,int h3)
{
   
    
      uwStep = getStep(h1,h2,h3);
      switch(uwStep)
      {
        case 1:
          GPIO_SetBits(GPIOA, GPIO_Pin_8);
          GPIO_ResetBits(GPIOB, GPIO_Pin_13);
          GPIO_ResetBits(GPIOE, GPIO_Pin_11);
          GPIO_SetBits(GPIOB, GPIO_Pin_14);
          GPIO_ResetBits(GPIOA, GPIO_Pin_10);
          GPIO_ResetBits(GPIOB, GPIO_Pin_15);
          uwStep++;
        break;
        case 2:
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          GPIO_ResetBits(GPIOB, GPIO_Pin_13);
          GPIO_ResetBits(GPIOE, GPIO_Pin_11);
          GPIO_SetBits(GPIOB, GPIO_Pin_14);
          GPIO_SetBits(GPIOA, GPIO_Pin_10);
          GPIO_ResetBits(GPIOB, GPIO_Pin_15);
          uwStep++;
        break;
        case 3:
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          GPIO_SetBits(GPIOB, GPIO_Pin_13);
          GPIO_ResetBits(GPIOE, GPIO_Pin_11);
          GPIO_ResetBits(GPIOB, GPIO_Pin_14);
          GPIO_SetBits(GPIOA, GPIO_Pin_10);
          GPIO_ResetBits(GPIOB, GPIO_Pin_15);
          uwStep++;
        break;
        case 4:
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          GPIO_SetBits(GPIOB, GPIO_Pin_13);
          GPIO_SetBits(GPIOE, GPIO_Pin_11);
          GPIO_ResetBits(GPIOB, GPIO_Pin_14);
          GPIO_ResetBits(GPIOA, GPIO_Pin_10);
          GPIO_ResetBits(GPIOB, GPIO_Pin_15);
          uwStep++;
        break;
        case 5:
          GPIO_ResetBits(GPIOA, GPIO_Pin_8);
          GPIO_ResetBits(GPIOB, GPIO_Pin_13);
          GPIO_SetBits(GPIOE, GPIO_Pin_11);
          GPIO_ResetBits(GPIOB, GPIO_Pin_14);
          GPIO_ResetBits(GPIOA, GPIO_Pin_10);
          GPIO_SetBits(GPIOB, GPIO_Pin_15);
          uwStep++;
        break;
        case 6:
          GPIO_SetBits(GPIOA, GPIO_Pin_8);
          GPIO_ResetBits(GPIOB, GPIO_Pin_13);
          GPIO_ResetBits(GPIOE, GPIO_Pin_11);
          GPIO_ResetBits(GPIOB, GPIO_Pin_14);
          GPIO_ResetBits(GPIOA, GPIO_Pin_10);
          GPIO_SetBits(GPIOB, GPIO_Pin_15);
          uwStep=1;
        break;
      }
    
}











/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40_41xxx.s/startup_stm32f427_437xx.s/startup_stm32f429_439xx.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */     
  SysTickConfig();
  /* TIM1 Configuration */
  TIM_Config();
  
  GPIO_ResetBits(GPIOA, GPIO_Pin_8);
  GPIO_ResetBits(GPIOB, GPIO_Pin_13);
  GPIO_ResetBits(GPIOE, GPIO_Pin_11);
  GPIO_ResetBits(GPIOB, GPIO_Pin_14);
  GPIO_ResetBits(GPIOA, GPIO_Pin_10);
  GPIO_ResetBits(GPIOB, GPIO_Pin_15);
  GPIO_ResetBits(GPIOC, GPIO_Pin_1);
  GPIO_ResetBits(GPIOC, GPIO_Pin_2);
  GPIO_ResetBits(GPIOC, GPIO_Pin_3);
  /* ---------------------------------------------------------------------------
  TIM1 Configuration to:
  1/ Generate 3 complementary PWM signals with 3 different duty cycles:
  
    TIM1 input clock (TIM1CLK) is set to 2 * APB2 clock (PCLK2), since APB2 
    prescaler is different from 1.   
    TIM1CLK = 2 * PCLK2  
    PCLK2 = HCLK / 2 
    => TIM1CLK = 2 * (HCLK / 2) = HCLK = SystemCoreClock
  
    TIM1CLK is fixed to SystemCoreClock, the TIM1 Prescaler is equal to 0 so the 
    TIM1 counter clock used is SystemCoreClock (168MHz).
    The objective is to generate PWM signal at 17.57 KHz:
    - TIM1_Period = (SystemCoreClock / 17570) - 1
    The Three Duty cycles are computed as the following description: 
    The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
    The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
    The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
    
    The Timer pulse is calculated as follows:
      - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  2/ Insert a dead time equal to (11/SystemCoreClock) ns
  3/ Configure the break feature, active at High level, and using the automatic 
     output enable feature
  4/ Use the Locking parameters level1. 
  
  Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  --------------------------------------------------------------------------- */

  /* Compute the value to be set in ARR register to generate signal frequency at 17.57 Khz */
  // TimerPeriod = (SystemCoreClock / 17570) - 1;

  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  // Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

  /* Compute CCR2 value to generate a duty cycle at 25%  for channel 2 */
  // Channel2Pulse = (uint16_t) (((uint32_t) 25 * (TimerPeriod - 1)) / 100);

  /* Compute CCR3 value to generate a duty cycle at 12.5%  for channel 3 */
  // Channel3Pulse = (uint16_t) (((uint32_t) 125 * (TimerPeriod - 1)) / 1000);

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 27;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 999;                       // 1ms
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  
  
  
  
  
  
  
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);


  while (1)
  {
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0 || GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0 || GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
    {
      h1 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
      h2 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
      h3 = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
      commute(h1,h2,h3);
      GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      GPIO_ResetBits(GPIOC, GPIO_Pin_2);
      GPIO_ResetBits(GPIOC, GPIO_Pin_3);
    }
  }
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure,GPIO_hall;

  /* GPIOA and GPIOB clocks enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
                         
  /* GPIOA Configuration: Channel 1 and 3 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* GPIOA Configuration: Channel 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
   
  /* GPIOB Configuration: BKIN, Channel 1N, 2N and 3N as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  GPIO_StructInit(&GPIO_hall);
  GPIO_hall.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_hall.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOC, &GPIO_hall);
  
  /* Enable the TIM1 Trigger and commutation interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
}

static void SysTickConfig(void)
{
  /* Setup SysTick Timer for 100 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 100))
  { 
    /* Capture error */ 
    while (1);
  }

  NVIC_SetPriority(SysTick_IRQn, 0);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */
