/*
 * API_I2C.h
 *
 *  Created on: 3 ago. 2023
 *      Author: Jesus
 *
 *      Header para el driver que permite comunicarse con I2C
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

//Inclusiones
#include<stdio.h>
#include<stdbool.h>
#include "stm32f4xx_hal.h"
//Definiciones
typedef bool bool_t;
//Prototipo Funciones
bool_t Init_I2C_1(uint16_t direccion);
void Escritura_por_I2C_1(uint8_t * dato);
uint8_t Lectura_por_I2C_1(void);



#endif /* API_INC_API_I2C_H_ */
