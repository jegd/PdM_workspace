/*
 * API_adxl.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

//Inclusiones
#include "API_adxl.h"

//Definiciones
// Defición de tipo de variable máquina de estados para detectar cambio a 0, 1 o -1
typedef enum {
	ESTADO_1=1,
	ESTADO_NADA_1=2,
	ESTADO_0=0,
	ESTADO_NADA_M1=-2,
	ESTADO_M1=-1
}  MEF_estado_eje_t;

typedef struct{
	MEF_estado_eje_t * MEF_eje;
	float(*obtener_valor_eje)(void);
	int8_t estadoAcel;
}	eje_t;

//Prototipo funciones privadas
 static void Error_Handler(void);
 static void MEF_estado_eje_INIT(eje_t * Eje_a_evaluar);
 static void uint8_obtener_estado_MEF_eje(eje_t * Eje_a_evaluar);

 //Definiciones
#define TIMEOUT HAL_MAX_DELAY				//Timeout de la función transmit I2C de Hal
#define LIMIT_SUP 	0.8f
#define LIMIT_INF	0.2f
//Variables públicas
 uint16_t direc;
//Variables privadas
 static I2C_HandleTypeDef *Modulo_I2C;
static int16_t desfaseX=0,desfaseY=0;			//Variables de desfase
 static uint16_t direccion_I2C_ADXL;
 static MEF_estado_eje_t estado_X;
 static MEF_estado_eje_t estado_Y;
 static eje_t 	Eje_X={
		 .MEF_eje = &estado_X,
		 .obtener_valor_eje = obtenerX
 };
 static eje_t 	Eje_Y={
		 .MEF_eje = &estado_Y,
		 .obtener_valor_eje = obtenerY
 };
 static eje_t	Eje_Y;
//I2C_HandleTypeDef hi2c1;
//Implementación funciones públicas
 bool_t init_adxl(uint16_t direccion)
 {
	 assert(&direccion!=NULL);
	 direccion_I2C_ADXL = direccion;
	 Modulo_I2C=enviar_handle_i2c();
	 MEF_estado_eje_INIT(&Eje_X);
	 MEF_estado_eje_INIT(&Eje_Y);
	  //Seteo del acelerómetro para que empiece a mandar datos
	 // Mandamos a 1 el bit 4 (0x08) del registro 0x2D—POWER_CTL del acelerómetro
	 // para que despierte y empiece a mandar datos
	  uint8_t vec[2]={0x2D,0x08};
	  HAL_I2C_Master_Transmit(Modulo_I2C,direccion_I2C_ADXL,(uint8_t *)vec, sizeof(vec), TIMEOUT);
	  //Tomamos las muestras de desfase
	  desfaseX=(float)(obtenerX())*256;
	  desfaseY=(float)(obtenerY())*256;
	  return 1;
 }

 float obtenerX(void)
 {
	 uint8_t a=0x32;				//Registro que se debe consultar en el acelerómetro para tener el primer byte de datos X
	 float dato_X;
	 HAL_I2C_Master_Transmit(Modulo_I2C, direccion_I2C_ADXL,(uint8_t *)&a, sizeof(a), TIMEOUT);
	 uint8_t b[2];
	 int16_t ext;
	 HAL_I2C_Master_Receive(enviar_handle_i2c(), direccion_I2C_ADXL, b, sizeof(b), TIMEOUT);
	 ext=(b[1]<<8|b[0])-desfaseX;
	 dato_X=(float)ext/256;
	 return dato_X;
 }
 float obtenerY(void)
 {
	 uint8_t a=0x34;				//Registro que se debe consultar en el acelerómetro para tener el primer byte de datos Y
	 float dato_Y;
	 HAL_I2C_Master_Transmit(Modulo_I2C, direccion_I2C_ADXL,(uint8_t *)&a, sizeof(a), TIMEOUT);
	 uint8_t b[2];
	 int16_t ext;
	 HAL_I2C_Master_Receive(enviar_handle_i2c(), direccion_I2C_ADXL, b, sizeof(b), TIMEOUT);
	 ext=(b[1]<<8|b[0])-desfaseY;
	 dato_Y=(float)ext/256;
	 return dato_Y;
 }

 int8_t estadoX(void)
 {
	 uint8_obtener_estado_MEF_eje(&Eje_X);
	 int8_t valor_del_eje_X = Eje_X.estadoAcel;
	 return valor_del_eje_X;
 }
 int8_t estadoY(void)
  {
	uint8_obtener_estado_MEF_eje(&Eje_Y);
	int8_t valor_del_eje_Y = Eje_Y.estadoAcel;
	return -valor_del_eje_Y;
  }


 //Implementación funciones privadas
 static void MEF_estado_eje_INIT(eje_t * Eje_a_evaluar)
 {
	 assert(&Eje_a_evaluar!=NULL);
	 *(Eje_a_evaluar->MEF_eje) = ESTADO_0;
 }


 static void uint8_obtener_estado_MEF_eje(eje_t * Eje_a_evaluar)
 {
	 assert(&Eje_a_evaluar!=NULL);
	 switch(*(Eje_a_evaluar->MEF_eje))
	 {
	 case ESTADO_1:
		 // Se realiza cuando estamos en el estado 1
		 if(Eje_a_evaluar->obtener_valor_eje() < LIMIT_SUP)
			 *(Eje_a_evaluar->MEF_eje)=ESTADO_NADA_1;

		 Eje_a_evaluar->estadoAcel=1;
		 break;
	 case ESTADO_NADA_1:
		 // Se realiza cuando estamos en un limbo entre saber si es 1 o 0
		 if(Eje_a_evaluar->obtener_valor_eje() > LIMIT_SUP)
			*(Eje_a_evaluar->MEF_eje)=ESTADO_1;

		 if(Eje_a_evaluar->obtener_valor_eje() < LIMIT_INF)
			*(Eje_a_evaluar->MEF_eje)=ESTADO_0;
	 		 break;
	 case ESTADO_0:
		 // Se realiza cuando estamos en el estado 0
		 if(Eje_a_evaluar->obtener_valor_eje() > LIMIT_INF)
			*(Eje_a_evaluar->MEF_eje)=ESTADO_NADA_1;

		 if(Eje_a_evaluar->obtener_valor_eje() < (-LIMIT_INF))
			*(Eje_a_evaluar->MEF_eje)=ESTADO_NADA_M1;

		 Eje_a_evaluar->estadoAcel=0;
	 		 break;
	 case ESTADO_NADA_M1:
		 // Se realiza cuando estamos en un limbo entre saber si es 0 o -1
		 if(Eje_a_evaluar->obtener_valor_eje() > (-LIMIT_INF))
			*(Eje_a_evaluar->MEF_eje)=ESTADO_0;

		 if(Eje_a_evaluar->obtener_valor_eje() < (-LIMIT_SUP))
			*(Eje_a_evaluar->MEF_eje)=ESTADO_M1;
	 		 break;
	 case ESTADO_M1:
		 // Se realiza cuando estamos en el estado -1

		 if(Eje_a_evaluar->obtener_valor_eje() > (-LIMIT_SUP))
		 { *(Eje_a_evaluar->MEF_eje)=ESTADO_NADA_M1;}

		 Eje_a_evaluar->estadoAcel=-1;

	 		 break;
	 default:
		 MEF_estado_eje_INIT(Eje_a_evaluar);
		 break;


	 }
 }



 static void Error_Handler(void)
 {
	  __disable_irq();
	  while (1)
	  {
	  }
 }
