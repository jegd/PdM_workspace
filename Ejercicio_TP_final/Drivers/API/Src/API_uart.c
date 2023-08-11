// Archivo .c driver de manejo de UART


#include"API_uart.h"
#include<string.h>
//Variables Públicas
//Variables privadas
UART_HandleTypeDef huart3;
#define USART USART3
#define BAUDIOS 9600
#define PALABRA UART_WORDLENGTH_8B
#define STOP UART_STOPBITS_1
#define PARI UART_PARITY_ODD
#define MODO UART_MODE_TX_RX
#define FLOW UART_HWCONTROL_NONE
#define TIME UART_OVERSAMPLING_16
PCD_HandleTypeDef hpcd_USB_OTG_FS;

//Prototipos Funciones Públicas
bool_t uartInit();
void uartSendString(const uint8_t * pstring);			//Función para enviar mensaje por UART3
void uartSendStringSize(const uint8_t * pstring, uint16_t size);			//Función que envía palabra pidiendo tamaño a transmitir
//Prototipos Funciones Privadas
static void MX_USART3_UART_Init(void);					//Inicialización del UART3
static void MX_USB_OTG_FS_PCD_Init(void);
static void Error_Handler(void);						//Función para manejo de errores

//Implementación de funciones

bool_t uartInit(void)
{
	bool_t Estado_uart = false;
	 MX_USART3_UART_Init();
	 MX_USB_OTG_FS_PCD_Init();
	 if (HAL_UART_Init(&huart3) == HAL_OK)
	 Estado_uart = true;
	 // Mensaje de inicialización y parámetros de
	 uartSendString((const uint8_t *) "\n\rInicializacion de UART exitosa \n\r");
	 uartSendString((const uint8_t *) "Parametros de UART \n\r ");
	 uartSendString((const uint8_t *) "- Baudios: 9600 \n\r ");
	 uartSendString((const uint8_t *) "- Palabra(incluyendo pariedad): 8 \n\r ");
	 uartSendString((const uint8_t *) "- Stop bits: 1 \n\r ");
	 uartSendString((const uint8_t *) "- Pariedad: Impar \n\r ");
	 uartSendString((const uint8_t *) "- Modo: Transmisor receptor \n\r ");
	 uartSendString((const uint8_t *) "- Flow: Ninguno \n\r ");


	 return Estado_uart;
}

void uartSendString(const uint8_t *  pstring)
{
	 const uint8_t *puntero=pstring;
	 while(*puntero)
	 {
		 HAL_UART_Transmit(&huart3,(const uint8_t *)puntero++,1,200);
	 }
}

void uartSendStringSize( const uint8_t * pstring, uint16_t size)
{
	 const uint8_t *puntero=pstring;
	 while(*pstring+size>*puntero)
	 {
		 HAL_UART_Transmit(&huart3,(const uint8_t *)puntero++,1,200);
	 }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART;
  huart3.Init.BaudRate = BAUDIOS;
  huart3.Init.WordLength = PALABRA;
  huart3.Init.StopBits = STOP;
  huart3.Init.Parity = PARI;
  huart3.Init.Mode = MODO;
  huart3.Init.HwFlowCtl = FLOW;
  huart3.Init.OverSampling = TIME;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

static void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

