/*
 * API_LEDS.h
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

#ifndef API_INC_API_LEDS_H_
#define API_INC_API_LEDS_H_


#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;
void INIT_GPIO_LEDS(void);
void Modificar_LED_1(bool_t valor);
void Modificar_LED_2(bool_t valor);
void Modificar_LED_3(bool_t valor);




#endif /* API_INC_API_LEDS_H_ */
