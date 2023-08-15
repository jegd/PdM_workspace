#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

//Includes
#include<stdbool.h>
#include "stm32f4xx_hal.h"
#include <string.h>
//Definiciones
typedef bool bool_t;
//Funciones públicas
bool_t uartInit();															//Función para configurar UART3
void uartSendString(const uint8_t * pstring);								//Función enviar mensaje sin definir el tamaño
void uartSendStringSize(const uint8_t * pstring, uint16_t size);			//Función que envía palabra pidiendo tamaño a transmitir
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);				//Función que recibe una palabra pidiendo el tamaño a transmitir
bool_t consultar_uart(void);												//Función que permite informar si el UART3 está inicializado y se puede trabajar con él

#endif /* API_INC_API_UART_H_ */
