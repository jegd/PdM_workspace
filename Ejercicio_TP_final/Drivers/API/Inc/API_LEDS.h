/*
 * API_LEDS.h
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 *
 *      Libreria que permite manejar los estados de leds 1,2 y 3 de la placa de desarrollo núcleo-F446ZE
 */

#ifndef API_INC_API_LEDS_H_
#define API_INC_API_LEDS_H_


#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;
void INIT_GPIO_LEDS(void);							//Inicializa los GPIO de los leds
void Modificar_LED_1(bool_t valor);					//Escribe el valor que debe tener el led1 representado por un dato booleano
void Modificar_LED_2(bool_t valor);					//Escribe el valor que debe tener el led2 representado por un dato booleano
void Modificar_LED_3(bool_t valor);					//Escribe el valor que debe tener el led3 representado por un dato booleano


#endif /* API_INC_API_LEDS_H_ */
