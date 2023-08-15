/*
 * API_adxl.c
 *
 *  Created on: 11 ago. 2023
 *      Author: Jesus
 */

//Inclusiones
#include "API_adxl.h"

//Definiciones
// Defición de tipo de variable máquina de estados para detectar cambio de estados
typedef enum {
	ESTADO_1=1,
	ESTADO_NADA_1=2,
	ESTADO_0=0,
	ESTADO_NADA_M1=-2,
	ESTADO_M1=-1
}  MEF_estado_eje_t;
// Definición de la estructura que maneja un Eje
typedef struct{
	MEF_estado_eje_t * MEF_eje;
	float(*obtener_valor_eje)(void);
	int8_t estadoAcel;
}	eje_t;

//Prototipo funciones privadas
 static void Error_Handler(void);											//Función para el manejo de errores en el driver
 static void MEF_estado_eje_INIT(eje_t * Eje_a_evaluar);					//Función para inicializar la máquina de estados del Eje a utilizar
 static void obtener_estado_MEF_eje(eje_t * Eje_a_evaluar);					//Función que obtiene estado de la MEF del Eje utilizado

 //Definiciones

#define LIMIT_SUP 	0.8f													//Limite superior de la lectura de un eje
#define LIMIT_INF	0.2f													//Limite inferior de la lectura de un eje
//Variables públicas

//Variables privadas
static int16_t desfaseX=0,desfaseY=0;										//Variables para almacenar el desfase de los ejes
static uint16_t direccion_I2C_ADXL;											//Variable que almacena la dirección I2C que se le asigna al acelerómetro
static MEF_estado_eje_t estado_X;											//Creación máquina de estados Eje X
static MEF_estado_eje_t estado_Y;											//Creación máquina de estados Eje Y
static eje_t 	Eje_X={
		 .MEF_eje = &estado_X,
		 .obtener_valor_eje = obtenerX
 };
 static eje_t 	Eje_Y={
		 .MEF_eje = &estado_Y,
		 .obtener_valor_eje = obtenerY
 };
 static eje_t	Eje_Y;

//Implementación funciones públicas

 bool_t init_adxl(uint16_t direccion)
 {
	 assert(&direccion!=NULL);
	 direccion_I2C_ADXL = direccion;
	 MEF_estado_eje_INIT(&Eje_X);
	 MEF_estado_eje_INIT(&Eje_Y);
	  /*
	   * Seteo del acelerómetro para que empiece a mandar datos
	   * Mandamos a 1 el bit 4 (0x08) del registro 0x2D—POWER_CTL del acelerómetro
	   * para que despierte y empiece a mandar datos
	 */
	  uint8_t vec[2]={0x2D,0x08};
	  escribir_por_I2C(direccion_I2C_ADXL,(uint8_t *)vec,sizeof(vec));
	  //Tomamos las muestras de las medidas actuales del acelerómetro para su desfase
	  desfaseX=(float)(obtenerX())*256;
	  desfaseY=(float)(obtenerY())*256;
	  return 1;								//Retornamos 1 en caso la inicialización fue correcta
 }

 /*
  * Función para obtener el valor del eje X con una medida entre 1g a -1g
  * Se deben consultar los registros 0x32 y 0x33 del acelerómetro
  * siendo el primero el byte menos significativo y al unirlos obtendremos la lectura del eje X
  * */

 float obtenerX(void)
 {
	 uint8_t a=0x32;
	 float dato_X;
	 escribir_por_I2C(direccion_I2C_ADXL,(uint8_t *)&a,sizeof(a));
	 uint8_t b[2];
	 int16_t ext;
	 leer_por_I2C(direccion_I2C_ADXL,b,sizeof(b));
	 ext=(b[1]<<8|b[0])-desfaseX;
	 //Dividir el resultado entre 256 debido a que estamos trabajando con la sensivilidad por defecto de +-2g
	 //la cual es correcta para la aplicación de sensado de orientación que estamos realizando
	 dato_X=(float)ext/256;
	 return dato_X;
 }

 /*
  * Función para obtener el valor del eje Y con una medida entre 1g a -1g
  * Se deben consultar los registros 0x34 y 0x35 del acelerómetro
  * siendo el primero el byte menos significativo y al unirlos obtendremos la lectura del eje Y
  * */

 float obtenerY(void)
 {
	 uint8_t a=0x34;
	 float dato_Y;
	 escribir_por_I2C(direccion_I2C_ADXL,(uint8_t *)&a,sizeof(a));
	 uint8_t b[2];
	 int16_t ext;
	 leer_por_I2C(direccion_I2C_ADXL,b,sizeof(b));
	 ext=(b[1]<<8|b[0])-desfaseY;
	 //Dividir el resultado entre 256 debido a que estamos trabajando con la sensivilidad por defecto de +-2g
	 //la cual es correcta para la aplicación de sensado de orientación que estamos realizando
	 dato_Y=(float)ext/256;
	 return dato_Y;
 }

 /*
  * Función que envía el estado de la máquina de estado del eje
  */

 int8_t estadoX(void)
 {
	 obtener_estado_MEF_eje(&Eje_X);
	 int8_t valor_del_eje_X = Eje_X.estadoAcel;
	 return valor_del_eje_X;
 }

 /*
  * Función que envía el estado de la máquina de estado del eje
  */
 int8_t estadoY(void)
  {
	obtener_estado_MEF_eje(&Eje_Y);
	int8_t valor_del_eje_Y = Eje_Y.estadoAcel;
	return -valor_del_eje_Y;
  }


 //Implementación funciones privadas


 /*
  * Inicialización de máquina de estados que se utilizará
  */
 static void MEF_estado_eje_INIT(eje_t * Eje_a_evaluar)
 {
	 assert(&Eje_a_evaluar!=NULL);
	 *(Eje_a_evaluar->MEF_eje) = ESTADO_0;
 }

 /*
  * Evalúa el valor real del sensor acelerómetro para definir si debe camibar de estado o no
  * tomando en cuenta los límites superior e inferior declaros al inicio
  */
 static void obtener_estado_MEF_eje(eje_t * Eje_a_evaluar)
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


 /*
  * Función para manejo de errores
  */


 static void Error_Handler(void)
 {
	  __disable_irq();
	  while (1)
	  {
		  //Funcion de error
	  }
 }
