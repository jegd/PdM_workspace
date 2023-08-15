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
#include<assert.h>
#include "stm32f4xx_hal.h"
//Definiciones
typedef bool bool_t;

//Declaración de funciones
void MX_I2C1_Init();																//Función para inicialización del periférico I2C1
I2C_HandleTypeDef* enviar_handle_i2c();												//Función que devuelve un puntero del handle I2C
void escribir_por_I2C(uint16_t direccion_I2C,uint8_t * dato,uint16_t tamano);		//Función para escribir por I2C
void leer_por_I2C(uint16_t direccion_I2C,uint8_t * dato_alma,uint16_t tamano);		//Función para leer por I2C

#endif /* API_INC_API_I2C_H_ */
