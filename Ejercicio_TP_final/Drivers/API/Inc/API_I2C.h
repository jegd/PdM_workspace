/*
 * API_I2C.h
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#include<stdio.h>
#include<stdbool.h>
#include "stm32f4xx_hal.h"
//Definiciones
typedef bool bool_t;
void MX_I2C1_Init();
I2C_HandleTypeDef* enviar_handle_i2c();


#endif /* API_INC_API_I2C_H_ */
