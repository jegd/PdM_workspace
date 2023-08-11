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
#include "stm32f4xx_hal.h"
#include "API_I2C.h"
//Definiciones
typedef bool bool_t;
//Prototipo Funciones
bool_t init_adxl(uint16_t direccion);		//Inicializa el acelerómetro para que empiece a enviar datos
float obtenerX(void);
float obtenerY(void);
int8_t estadoX(void);
int8_t estadoY(void);



#endif /* API_INC_API_ADXL_H_ */
