/*
 * API_I2C.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

//Includes
#include "API_I2C.h"

//Variables privadas
static I2C_HandleTypeDef hi2c1;



/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init()
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  /*

  uint8_t vec[2]={0x2D,0x08};
  	  HAL_I2C_Master_Transmit(&hi2c1,0x53<<1,(uint8_t *)vec, sizeof(vec), HAL_MAX_DELAY);


  	  */
  /* USER CODE END I2C1_Init 2 */

}
I2C_HandleTypeDef * enviar_handle_i2c()
{
	return &hi2c1;
}
