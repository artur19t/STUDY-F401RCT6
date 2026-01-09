#include "hw_init.h"

//PB 3, 10

void GPIO_I2C2_UsrInit(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  // --- I2C2_SCL PB10 ---
  LL_GPIO_InitTypeDef GPIO_UsrStrct = {0};
  GPIO_UsrStrct.Alternate = LL_GPIO_AF_4;
  GPIO_UsrStrct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_UsrStrct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_UsrStrct.Pin = LL_GPIO_PIN_10;
  GPIO_UsrStrct.Pull = LL_GPIO_PULL_UP;
  GPIO_UsrStrct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(GPIOB, &GPIO_UsrStrct);
  // --- I2C2_SDA PB3 ---
  memset(&GPIO_UsrStrct, 0, sizeof(LL_GPIO_InitTypeDef));
  GPIO_UsrStrct.Alternate = LL_GPIO_AF_9;
  GPIO_UsrStrct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_UsrStrct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_UsrStrct.Pin = LL_GPIO_PIN_3;
  GPIO_UsrStrct.Pull = LL_GPIO_PULL_UP;
  GPIO_UsrStrct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(GPIOB, &GPIO_UsrStrct);
}

void I2C2_UsrInit(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
  
  LL_I2C_Disable(I2C2);
  LL_I2C_EnableReset(I2C2);
  LL_I2C_DisableReset(I2C2);
  
  LL_I2C_InitTypeDef I2C_UsrStruct = {0};
  I2C_UsrStruct.ClockSpeed = 100000;
  I2C_UsrStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
  I2C_UsrStruct.OwnAddress1 = 0;
  I2C_UsrStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  I2C_UsrStruct.PeripheralMode = LL_I2C_MODE_I2C;
  I2C_UsrStruct.TypeAcknowledge = LL_I2C_ACK;
  LL_I2C_Init(I2C2, &I2C_UsrStruct);
  
  LL_I2C_Enable(I2C2);
}
