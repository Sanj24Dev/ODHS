/*Configure the device structure */
 /**NOTES:
   0x75: is the address of who_am_i reg
   0x68: is the address of gyro
   sRxStructure:  struct members of CPAL_TransferTypeDef (reception) 
   sTxStructure:  struct members of CPAL_TransferTypeDef (transmission)
   tRxBuffer:
 sda: pb6 
 scl : pb9 
*/
 #include "cpal_i2c.h"
 int main()
 {
  CPAL_TransferTypeDef  sRxStructure, sTxStructure;
  uint8_t RxBuffer;
  CPAL_I2C_StructInit(&I2C1_DevStructure);
   /* Set all fields to default values */
  //I2C1_DevStructure.pCPAL_I2C_Struct->I2C_ClockSpeed = 4000000;
  //I2C1_DevStructure.wCPAL_Options = CPAL_OPT_16BIT_REG;
  I2C1_DevStructure.CPAL_ProgModel = CPAL_PROGMODEL_INTERRUPT;
  I2C1_DevStructure.CPAL_Dev = CPAL_I2C1;
  I2C1_DevStructure.CPAL_Mode = CPAL_MODE_MASTER; 
  I2C1_DevStructure.CPAL_Direction = CPAL_DIRECTION_TXRX;
  I2C1_DevStructure.pCPAL_TransferRx = &sRxStructure;
  I2C1_DevStructure.pCPAL_TransferTx = &sTxStructure;
  /* Initialize CPAL device with the selected parameters */
  CPAL_I2C_Init(&I2C1_DevStructure);
  
  /* Initialize local Transmission structures */
  //sTxStructure.wNumData = 1u; /* Maximum Number of data to be received */
  //sTxStructure.pbBuffer = &TxBuffer; 
  //sTxStructure.wAddr1 = 0xD0;      /*<Contains the Target device Address (optional)*/
  //sTxStructure.wAddr2 = 0x75;         /* Contains the Register/Physical Address into the device */  
  
  /* Initialize local Reception structures */
  sRxStructure.wNumData = 1u;       /* Maximum Number of data to be received */
  sRxStructure.pbBuffer = &RxBuffer;        /* Common Rx buffer for all received data */
  sRxStructure.wAddr1 = 0x69 << 1;               /*Contains the Target device Address */
  sRxStructure.wAddr2 = 0x75;               /* Contains the Register/Physical Address into the device */
  
   /** Read ------------------------------------------------------------------- */ 
   
  //I2C1_DevStructure.CPAL_State = CPAL_STATE_READY;
  //CPAL_I2C_Init(&I2C1_DevStructure); 
  if(CPAL_I2C_Read(&I2C1_DevStructure) == CPAL_PASS);
  while(I2C1_DevStructure.CPAL_State!=CPAL_STATE_READY);
   while(1); 
}//end of main fn
