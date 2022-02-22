#include "stm32f4xx.h"

#define SUN_SENSOR_ADDR 	0xD0		//0b11010000		check
#define CONF_REG_ADDR		0x00		//dont know
#define CONF_FOR_START 		0x8C		//0b10001100		check
#define CONF_FOR_READ		0x00		//dont know
#define FLAG_CHECK_EOC  	0x80		//0b10000000

uint8_t Tx_Buffer=0;

//can use polling mode or interrupt mode
//use while loop for polling mode

int main()
{
	I2C_HandleTypeDef hi2c;
	hi2c.Init.ClockSpeed = 0; //clock speed of i2c
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.OwnAddress1 = 0;
	hi2c.State = HAL_I2C_STATE_READY;
	hi2c.Mode = HAL_I2C_MODE_MASTER;
	hi2c.pBuffPtr = &Tx_Buffer;
	hi2c.XferSize = 1u;
	hi2c.XferOptions = I2C_FIRST_FRAME; //no idea
	
	hi2c.Devaddress = SUN_SENSOR_ADDR;
	hi2c.Memaddress = CONF_REG_ADDR;
	hi2c.MemaddSize = 1u;
	
	HAL_I2C_Init(&hi2c);
	
	//sending configuration reg value to start the conversion
	Tx_Buffer = CONF_FOR_START;
	while(HAL_I2C_Master_Transmit(&hi2c, SUN_SENSOR_ADDR, &Tx_Buffer, 1u, 3) != HAL_OK){}
		
	//waiting until the READY bit in configuration reg is 0		
	uint8_t check;
	do
	{
		check = Tx_Buffer & FLAG_CHECK_EOC;
		if(check == 0)
			break;
	}while(HAL_I2C_Master_Receive(&hi2c, SUN_SENSOR_ADDR, &Tx_Buffer, 1u, 3) != HAL_OK);

}
