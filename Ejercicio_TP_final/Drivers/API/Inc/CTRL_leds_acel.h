/*
 * CTRL_leds_acel.h
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 *
 *
 *      Libreria para controlar leds de la placa de desarrollo Nucleo-F44ZE con un acelerómetro
 */

#ifndef API_INC_CTRL_LEDS_ACEL_H_
#define API_INC_CTRL_LEDS_ACEL_H_

#include<stdio.h>
#include<stdbool.h>
#include <main.h>
#include "API_LEDS.h"
#include "Api_delay.h"
#include "API_uart.h"
typedef bool bool_t;

bool_t ctrl_leds_acel_INIT(void);
void update_leds_acel(int8_t valor_entrada_1, int8_t valor_entrada_2);

#endif /* API_INC_CTRL_LEDS_ACEL_H_ */
