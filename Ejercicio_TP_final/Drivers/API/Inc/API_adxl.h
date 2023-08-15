/*
 * API_adxl.h
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

#ifndef API_INC_API_ADXL_H_
#define API_INC_API_ADXL_H_

//Inclusiones
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include "stm32f4xx_hal.h"
#include "API_I2C.h"
//Definiciones
typedef bool bool_t;
//Prototipo Funciones
bool_t init_adxl(uint16_t direccion);		//Inicializa el acelerómetro para que empiece a enviar datos
float obtenerX(void);						//Obtenemos el valor del eje X en el rango de 1g a -1g
float obtenerY(void);						//Obtenemos el valor del eje Y en el rango de 1g a -1g
int8_t estadoX(void);						//Obtenemos el valor de la máquina de estado del eje X
int8_t estadoY(void);						//Obtenemos el valro de la máquina de estado del eje Y



#endif /* API_INC_API_ADXL_H_ */
