/*
 * API_I2C.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

//Includes
#include "API_I2C.h"


#define TIMEOUT HAL_MAX_DELAY												//Timeout de la función transmit I2C de Hal
//Variables privadas
static I2C_HandleTypeDef hi2c1;						//Handle I2C que se utiliza en el driver
static void  Error_Handler(void);					//Función para manejar error de inicialización en el driver


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

  /* USER CODE END I2C1_Init 2 */


/*
 * Función pública que permite enviar el puntero al handle I2C que contiene la información del periférico I2C
 * que se está utilizando
*/
}
I2C_HandleTypeDef * enviar_handle_i2c()
{
	assert(&hi2c1!=NULL);
	return &hi2c1;
}

void escribir_por_I2C(uint16_t direccion_I2C,uint8_t * dato,uint16_t tamano)
{
	HAL_I2C_Master_Transmit(&hi2c1,direccion_I2C,dato, tamano, TIMEOUT);
}

void leer_por_I2C(uint16_t direccion_I2C,uint8_t * dato_alma,uint16_t tamano)
{
	 HAL_I2C_Master_Receive(&hi2c1, direccion_I2C, dato_alma, tamano, TIMEOUT);
}

static void  Error_Handler(void)
{
	//funcion de error
}
