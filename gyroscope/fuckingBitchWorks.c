/* 
This program executes write and read function sepertely, and when it comes to CPAL_PASS, it goes to event handler.
But when breakpoint set on while(1), it goes through the entire codeand stops at while(1)
Slave address when it enters the 8 bit register mode in read function
Register address when it enters the master mode in read function.

*/

#include "stm32f4xx.h"
#include "main.h"
#include "cpal.h"

//uint8_t RxBuffer[8], TxBuffer[8]; 
uint8_t RxBuffer[8]={0};
//int Buffersize =8;



int main()
{
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  //RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  // PB6/8 and PB7/9 are I2C SCL and SDA lines.
  
  I2C_InitTypeDef pCPAL_I2C_Struct;
  pCPAL_I2C_Struct.I2C_ClockSpeed = 400000;
  pCPAL_I2C_Struct.I2C_Mode = I2C_Mode_I2C;
  pCPAL_I2C_Struct.I2C_DutyCycle = I2C_DutyCycle_2;
  pCPAL_I2C_Struct.I2C_OwnAddress1 = 0;
  pCPAL_I2C_Struct.I2C_Ack = I2C_Ack_Enable;
  pCPAL_I2C_Struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_StructInit(&pCPAL_I2C_Struct);
  
  /*
  CPAL_TransferTypeDef Tx_Init;
  Tx_Init.pbBuffer = 0x00;	//!<The address of the buffer from/to which the transfer should start 
  Tx_Init.wAddr1 = 0xD0;	//!<Contains the Target device Address (optional)
  Tx_Init.wAddr2 = 0x6B;	//!<Contains the Register/Physical Address into the device (optional) 
  Tx_Init.wNumData = 1 ; //!<Number of data to be transferred for the current transaction  
  */
  
  CPAL_TransferTypeDef Rx_Init;
  Rx_Init.pbBuffer = RxBuffer ;	/*!<The address of the buffer from/to which the transfer should start */
  Rx_Init.wAddr1 = 0x68<<1;	/*!<Contains the Target device Address (optional)*/
  Rx_Init.wAddr2 = 0x75;	/*!<Contains the Register/Physical Address into the device (optional) */
  Rx_Init.wNumData = 1;	/*!<Number of data to be transferred for the current transaction */ 
  
  
  
  //CPAL_InitTypeDef I2C1_DevStructure;
  I2C1_DevStructure.CPAL_Dev = CPAL_I2C1;
  I2C1_DevStructure.CPAL_State = CPAL_STATE_READY;
  I2C1_DevStructure.CPAL_Direction = CPAL_DIRECTION_TXRX;
  I2C1_DevStructure.CPAL_Mode = CPAL_MODE_MASTER;
  I2C1_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_INTERRUPT;
  //I2C1_DevStructure.pCPAL_TransferTx = &Tx_Init;
  I2C1_DevStructure.pCPAL_TransferRx = &Rx_Init;
  //I2C1_DevStructure.CPAL_State = 
  //I2C1_DevStructure.wCPAL_DevError = CPAL_I2C_ERR_NONE;
  //I2C1_DevStructure.wCPAL_Options = 
  //I2C1_DevStructure.wCPAL_Timeout = 0;
  I2C1_DevStructure.pCPAL_I2C_Struct = &pCPAL_I2C_Struct;
  CPAL_I2C_Init(&I2C1_DevStructure);
  
  //CPAL_I2C_Write(&I2C1_DevStructure);
  CPAL_I2C_Read(&I2C1_DevStructure);
  while(I2C1_DevStructure.CPAL_State != CPAL_STATE_READY);
  
  //I2C1_DevStructure.CPAL_State = CPAL_STATE_READY_RX;
  //CPAL_I2C_Init(&I2C1_DevStructure);
  

  while(1); 
  
  
    
  	 
 
}
