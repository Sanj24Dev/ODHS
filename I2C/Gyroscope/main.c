#include "stm32f4xx.h"
#include "cpal_i2c.h"
#include "gyro.h"

int buff=0;
// nt* ptr = &buff;
BSP_GyrFetchTypeDef gyroStruct;

int main()
{  
  /*
   if(BSP_Gyroscope_Init(&I2C1_DevStructure) == ERROR)
     return 0;
   
   
   buff = BSP_Gyroscope_ReadRegister(&I2C1_DevStructure, 0x75);
  */
   if(BSP_Gyroscope_Init() == 0)
     return 0;
  
   // BSP_Gyroscope_Read_Register(&buff, 0x75);
  
   
   // if(BSP_Gyroscope_SelfTest()==ERROR)
     // return 0;
   
   if(BSP_Gyroscope_GetValues(&gyroStruct) == ERROR)
     return 0;
   
   while(1); 
}
