/*
 * CTRL_leds_acel.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */


//Includes
#include "CTRL_leds_acel.h"

//Defines
typedef enum{
	ADELANTE,
	BASE,
	ATRAS,
	IZQUIERDA,
	DERECHA
} MEF_ctrl_leds_acel;

#define PASO_ADELANTE 1
#define PASO_ATRAS -1
#define PASO_DERECHA 1
#define PASO_IZQUIERDA -1
#define PASO_BASE 0
//Funciones privadas
static void funcion_adelante(void);
static void funcion_base(void);
static void funcion_atras(void);
static void funcion_izquierda(void);
static void funcion_derecha(void);

//Variables privadas
//static uint16_t vector_leds[]= {LD1_Pin,LD2_Pin,LD3_Pin};
static MEF_ctrl_leds_acel Estado_actual;


//Implentación de funciones públicas

bool_t ctrl_leds_acel_INIT(void)
{
	assert(&Estado_actual!=NULL);
	INIT_GPIO_LEDS();
	Estado_actual=BASE;
	return 1;
}

//Función para indentificar en que estado se debe encontrar la máquina
void update_leds_acel(int8_t valor_entrada_1, int8_t valor_entrada_2)
{
	switch(Estado_actual)
	{
	case ADELANTE:
		if(valor_entrada_1==PASO_BASE)
		{
			Estado_actual=BASE;
			funcion_base();
		}
		break;
	case BASE:
		if(valor_entrada_1==PASO_ADELANTE)
		{
			Estado_actual=ADELANTE;
			funcion_adelante();
		}
		if(valor_entrada_1==PASO_ATRAS)
		{
			Estado_actual=ATRAS;
			funcion_atras();
		}
		if(valor_entrada_2==PASO_IZQUIERDA)
		{
			Estado_actual=IZQUIERDA;
			funcion_izquierda();
		}
		if(valor_entrada_2==PASO_DERECHA)
		{
			Estado_actual=DERECHA;
			funcion_derecha();
		}
		break;
	case ATRAS:
		if(valor_entrada_1==PASO_BASE)
		{
			Estado_actual=BASE;
			funcion_base();
		}
		break;
	case IZQUIERDA:
		if(valor_entrada_2==PASO_BASE)
		{
			Estado_actual=BASE;
			funcion_base();
		}
		break;
	case DERECHA:
		if(valor_entrada_2==PASO_BASE)
		{
			Estado_actual=BASE;
			funcion_base();
		}
		break;

	default:
		ctrl_leds_acel_INIT();
		break;

	}
}

//Implementación de funciones privadas

static void funcion_adelante(void)
{
	Modificar_LED_2(1);
}
static void funcion_base(void)
{
	Modificar_LED_1(0);
	Modificar_LED_2(0);
	Modificar_LED_3(0);
}
static void funcion_atras(void)
{
	Modificar_LED_2(1); //cambiar por parpadeante
}
static void funcion_izquierda(void)
{
	Modificar_LED_3(1);
}
static void funcion_derecha(void)
{
	Modificar_LED_1(1);
}

