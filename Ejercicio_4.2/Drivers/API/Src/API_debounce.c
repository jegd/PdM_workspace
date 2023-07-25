
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <main.h>
#include "stm32f4xx_hal.h"
#include"API_debounce.h"
#include "Api_delay.h"

#define time_rebote 40

// Nuevo tipo de datos enumerado llamado debounceState_t
// Es nuestra máquina de estados
typedef enum{
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;

//DECLARACIÓN DE FUNCIONES
void buttonPressed();			// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED3

//VARIABLES
static delay_t ret_rebote;				 					//Delay que evita el rebote
static uint16_t led[3] = {LD1_Pin,LD2_Pin,LD3_Pin};		//Vector con leds
static debounceState_t estadoActual;						//Tipo de variable para máquina de estado
bool var_readKey = false;
//DEFINICIÓN DE FUNCIONES
// Inicia nuestra MEF asignando el valor de BUTTON UP
void debounceFSM_init()
{
	assert(&estadoActual!=NULL);
	delayInit(&ret_rebote, time_rebote); 				//Inicialización del delay para antirebote
	estadoActual=BUTTON_UP;
}

//Evalúa el boton de usuario y cambia de estado si acaba el tiempo antirebote
void debounceFSM_update()
{
	assert(&estadoActual!=NULL);
	switch(estadoActual)
	{
	case BUTTON_UP:
		if((HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin)))
			estadoActual=BUTTON_FALLING;

		break;
	case BUTTON_FALLING:
		if(!(delayRead(&ret_rebote)))
		{
			if((HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin)))
			{
				estadoActual=BUTTON_DOWN;
				buttonPressed();
			}
			else{
				estadoActual=BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!(HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin)))
			estadoActual=BUTTON_RAISING;
		break;
	case BUTTON_RAISING:
		if(!(delayRead(&ret_rebote)))
				{
					if(!(HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin)))
					{
						estadoActual=BUTTON_UP;
						buttonReleased();
					}
					else{
						estadoActual=BUTTON_DOWN;
					}
				}
		break;
	default:
		debounceFSM_init();
		break;

	}
}
//Acción que se realiza cuando el botón se presionó
//pasado el tiempo de antirebote
void buttonPressed()
{
	HAL_GPIO_TogglePin(GPIOB, led[0]);
	var_readKey = true;
}
//Acción que se realiza cuando el botón se soltó
//pasado el tiempo de antirebote
void buttonReleased()
{
	HAL_GPIO_TogglePin(GPIOB, led[2]);
	var_readKey = false;
}
bool readKey()
{
return var_readKey;
}
