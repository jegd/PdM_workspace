/*
 * API_adxl.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

//Inclusiones
#include "API_adxl.h"

//Definiciones
#define Tiempo_out HAL_MAX_DELAY
//Prototipo funciones privadas
 static void Error_Handler(void);
 //Definiciones
#define TIMEOUT HAL_MAX_DELAY
//Variables públicas
 uint16_t direc;
//Variables privadas
 static I2C_HandleTypeDef *Modulo_I2C;
static int16_t desfaseX=0,desfaseY=0;			//Variables de desfase
 static uint16_t direccion_I2C_ADXL;
//I2C_HandleTypeDef hi2c1;
//Implementación funciones públicas
 bool_t init_adxl(uint16_t direccion)
 {
	 assert(&direccion!=NULL);
	 direccion_I2C_ADXL = direccion;
	 Modulo_I2C=enviar_handle_i2c();
	  //Seteo del acelerómetro para que empiece a mandar datos
	 // Mandamos a 1 el bit 4 (0x08) del registro 0x2D—POWER_CTL del acelerómetro
	 // para que despierte y empiece a mandar datos
	  uint8_t vec[2]={0x2D,0x08};
	  HAL_I2C_Master_Transmit(Modulo_I2C,direccion_I2C_ADXL,(uint8_t *)vec, sizeof(vec), TIMEOUT);
	  //Tomamos las muestras de desfase
	  desfaseX=(float)(obtenerX())*256;

 }

 float obtenerX(void)
 {
	 uint8_t a=0x32;				//Registro que se debe consultar en el acelerómetro para tener el primer byte de datos X
	 float dato_X;
	 HAL_I2C_Master_Transmit(Modulo_I2C, direccion_I2C_ADXL,(uint8_t *)&a, sizeof(a), TIMEOUT);
	 uint8_t b[2];
	 int16_t ext;
	 HAL_I2C_Master_Receive(enviar_handle_i2c(), 0x53<<1, b, sizeof(b), HAL_MAX_DELAY);
	 ext=(b[1]<<8|b[0])-desfaseX;
	 dato_X=(float)ext/256;
	 return dato_X;
 }
 void obtenerY(uint8_t * dato)
 {

 }
 static void Error_Handler(void)
 {
	  __disable_irq();
	  while (1)
	  {
	  }
 }
