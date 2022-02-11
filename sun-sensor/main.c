//sunsensor code

#include "stm32f4xx.h"
static int data[8] = {0};






int main()
{
	//Considered GPIOA for all the pins
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable the clock of port A of the GPIO
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable the clock of port B of the GPIO
  
  //ALE configuration
  GPIO_InitTypeDef ALE;
  ALE.Pin = GPIO_PIN_0;
  ALE.Mode = GPIO_MODE_OUTPUT_PP;
  ALE.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	ALE.Pull = GPIO_PULLUP;
	
	//SOC configuration
	GPIO_InitTypeDef SOC;
  SOC.Pin = GPIO_PIN_1;
  SOC.Mode = GPIO_MODE_OUTPUT_PP;
  SOC.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	SOC.Pull = GPIO_PULLUP;
	
	//EOC configuration
	GPIO_InitTypeDef EOC;
  EOC.Pin = GPIO_PIN_2;
  EOC.Mode = GPIO_MODE_INPUT;
  EOC.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	EOC.Pull = GPIO_PULLUP;								//check
	
	//OE configuration
	GPIO_InitTypeDef OE;
  OE.Pin = GPIO_PIN_3;
  OE.Mode = GPIO_MODE_OUTPUT_PP;
  OE.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	OE.Pull = GPIO_PULLUP;
	
	//data line configuration
	GPIO_InitTypeDef D0;
  D0.Pin = GPIO_PIN_4;
  D0.Mode = GPIO_MODE_INPUT;
  D0.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D0.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D1;
  D1.Pin = GPIO_PIN_5;
  D1.Mode = GPIO_MODE_INPUT;
  D1.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D1.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D2;
  D2.Pin = GPIO_PIN_6;
  D2.Mode = GPIO_MODE_INPUT;
  D2.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D2.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D3;
  D3.Pin = GPIO_PIN_7;
  D3.Mode = GPIO_MODE_INPUT;
  D3.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D3.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D4;
  D4.Pin = GPIO_PIN_8;
  D4.Mode = GPIO_MODE_INPUT;
  D4.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D4.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D5;
  D5.Pin = GPIO_PIN_9;
  D5.Mode = GPIO_MODE_INPUT;
  D5.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D5.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D6;
  D6.Pin = GPIO_PIN_10;
  D6.Mode = GPIO_MODE_INPUT;
  D6.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D6.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef D7;
  D7.Pin = GPIO_PIN_13;
  D7.Mode = GPIO_MODE_INPUT;
  D7.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	D7.Pull = GPIO_PULLUP;								//check
	
	GPIO_InitTypeDef clock;
  clock.Pin = GPIO_PIN_6;
  clock.Mode = GPIO_MODE_OUTPUT_PP;
  clock.Speed = GPIO_SPEED_FREQ_MEDIUM;   //refer to datasheet of ADC0808
	clock.Pull = GPIO_PULLUP;								//check
	
	//All gpio inits
	HAL_GPIO_Init(GPIOA, &ALE);
	HAL_GPIO_Init(GPIOA, &SOC);
	HAL_GPIO_Init(GPIOA, &EOC);
	HAL_GPIO_Init(GPIOA, &OE);
	HAL_GPIO_Init(GPIOA, &D0);
	HAL_GPIO_Init(GPIOA, &D1);
	HAL_GPIO_Init(GPIOA, &D2);
	HAL_GPIO_Init(GPIOA, &D3);
	HAL_GPIO_Init(GPIOA, &D4);
	HAL_GPIO_Init(GPIOA, &D5);
	HAL_GPIO_Init(GPIOA, &D6);
	HAL_GPIO_Init(GPIOA, &D7);
	HAL_GPIO_Init(GPIOB, &clock);
	
	//PB6 - TIM4_CH1
	//for the clock line
	TIM_HandleTypeDef CLOCK;	
	HAL_TIM_Base_DeInit(&CLOCK);
	
	// 28000000/1280 = 21875	<= 1280000	
	CLOCK.Init.CounterMode = TIM_COUNTERMODE_UP;
	CLOCK.Init.Period = 21875;
	CLOCK.Init.Prescaler = 1279;
	CLOCK.Instance = TIM4;
	//CLOCK.Instance = CR1;
	CLOCK.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
	CLOCK.State = HAL_TIM_STATE_READY;
	
	HAL_TIM_Base_Init(&CLOCK);
		
	//in peripheral toolbar option, check the timer/counter once its debugging

	
	//after selecting the channel
	//ALE goes low-high-low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	
	//SOC goes low-high-low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	
	//waiting for EOC
	//while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) != 0){}
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1){}
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0){}
		
	//OE goes low-high-low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	
	//getting the data
	data[0] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	data[1] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
	data[2] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	data[3] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	data[4] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
	data[5] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
	data[6] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
	data[7] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
		
	//unset OE
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	while(1){}
		
}
