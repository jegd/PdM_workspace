/*
 * API_LEDS.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */


#include "API_LEDS.h"
#include "main.h"

//Implementación de funciones públicas
/*
 * Se inicializa los GPIO de los leds de la placa
 */

void INIT_GPIO_LEDS(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : USER_Btn_Pin */
	  GPIO_InitStruct.Pin = USER_Btn_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
	  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : USB_OverCurrent_Pin */
	  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}
//Escribe el valor booleano deseado en el LED1
void Modificar_LED_1(bool_t valor)
{
	HAL_GPIO_WritePin(GPIOB,LD1_Pin,valor);
}
//Escribe el valor booleano deseado en el LED2
void Modificar_LED_2(bool_t valor)
{
	HAL_GPIO_WritePin(GPIOB,LD2_Pin,valor);
}
//Escribe el valor booleano deseado en el LED3
void Modificar_LED_3(bool_t valor)
{
	HAL_GPIO_WritePin(GPIOB,LD3_Pin,valor);
}
