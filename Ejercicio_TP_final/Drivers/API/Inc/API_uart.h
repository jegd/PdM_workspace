
//Header de driver UART
//Inclusión de headers
#include<stdbool.h>
#include "stm32f4xx_hal.h"
#include <string.h>
//Definiciones
typedef bool bool_t;
//Funciones públicas
bool_t uartInit();
void uartSendString(const uint8_t * pstring);								//Función para configurar UART y enviar mensaje por UART3
void uartSendStringSize(const uint8_t * pstring, uint16_t size);			//Función que envía palabra pidiendo tamaño a transmitir
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
bool_t consultar_uart(void);
