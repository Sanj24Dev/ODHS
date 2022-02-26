#include "stm32f4xx.h"

#define GYRO_ADDR_WRITE		0xD0		//0b11010000		check
#define WHOAMI_REG_ADDR		0x75		//dont know
#define GYRO_ADDR_READ		0xD1


uint8_t Rx_Buffer=0;	
HAL_StatusTypeDef check = HAL_ERROR;

//can use polling mode or interrupt mode
//use while loop for polling mode

int main()
{
	HAL_Init();
	ConfigureI2CPins();
	
	I2C_HandleTypeDef hi2c;
	hi2c.Instance = I2C1;
	hi2c.Init.ClockSpeed = 400000; //clock speed of i2c
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.OwnAddress2 = 0;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c.Init.OwnAddress1 = 0;
	hi2c.PreviousState = HAL_I2C_MODE_NONE;
	hi2c.State = HAL_I2C_STATE_READY;

	hi2c.Mode = HAL_I2C_MODE_MASTER;
	hi2c.pBuffPtr = &Rx_Buffer;
	hi2c.XferSize = 1u;
	hi2c.XferOptions = I2C_FIRST_FRAME; //no idea
	
	hi2c.Devaddress = GYRO_ADDR_READ;
	hi2c.Memaddress = WHOAMI_REG_ADDR;
	hi2c.MemaddSize = I2C_MEMADD_SIZE_8BIT;

	
	check = HAL_I2C_Init(&hi2c);
	
	//no waking the device
	//nvic?
	check = HAL_I2C_Master_Transmit_IT(&hi2c, GYRO_ADDR_READ, &Rx_Buffer, 1u);
	//check = HAL_I2C_Master_Receive(&hi2c, GYRO_ADDR_READ, &Rx_Buffer, I2C_MEMADD_SIZE_8BIT, 1);
	
	while(1);
}

