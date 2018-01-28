/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "u8g_com_arm_stm32.h"
#include "nrf24l01.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint32_t newAdcValues;
nrf24l01_dev myNRF;
uint8_t nrfRxBuffer[32];
uint8_t nrfTxBuffer[32];
uint8_t nrfRxAddress[5];
uint8_t nrfTxAddress[5];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Nrf_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	u8g_t u8g;
	uint16_t adcValue[10];
	uint32_t i;
	char adcString[20];
	HAL_StatusTypeDef adcStatus;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

	u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_i2c, u8g_com_arm_stm32_ssd_i2c_fn);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
	__enable_irq();

  /* USER CODE BEGIN 2 */
  u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_i2c, u8g_com_arm_stm32_ssd_i2c_fn);
  memset(adcValue,0,sizeof(adcValue));
  newAdcValues=0;
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcValue,10);
  Nrf_Config();
//  HAL_ADC_Start_DMA(&hadc1,adcValue,10);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
/*	  if((HAL_ADC_GetState(&hadc1)&HAL_ADC_STATE_REG_EOC)==HAL_ADC_STATE_REG_EOC)
	  {
		  HAL_ADC_Stop_DMA(&hadc1);
			HAL_Delay(2000);
		  HAL_ADC_Start_DMA(&hadc1,adcValue,10);
	  }*/
	  /*HAL_ADC_Start(&hadc1);
	  adcStatus=HAL_ADC_PollForConversion(&hadc1,1000);
	  if(adcStatus==HAL_OK)
	  {
		  for(i=0;i<10;i++)
			  adcValue[i]=HAL_ADC_GetValue(&hadc1);
	  }*/


	  if(newAdcValues)
	  {
		  newAdcValues=0;
		  u8g_FirstPage(&u8g);
		  do {
			  	  u8g_SetFont(&u8g, u8g_font_profont12);
			  	  sprintf(adcString," A0=%04X A5=%04X",adcValue[0],adcValue[5]);
			  	  u8g_DrawStr(&u8g, 0, 12,  adcString);
			  	  sprintf(adcString," A1=%04X A6=%04X",adcValue[1],adcValue[6]);
			  	  u8g_DrawStr(&u8g, 0, 24,  adcString);
			  	  sprintf(adcString," A2=%04X A7=%04X",adcValue[2],adcValue[7]);
			  	  u8g_DrawStr(&u8g, 0, 36,  adcString);
			  	  sprintf(adcString," A3=%04X A8=%04X",adcValue[3],adcValue[8]);
			  	  u8g_DrawStr(&u8g, 0, 48,  adcString);
			  	  sprintf(adcString," A4=%04X A9=%04X",adcValue[4],adcValue[9]);
			  	  u8g_DrawStr(&u8g, 0, 60,  adcString);
		  } while (u8g_NextPage(&u8g));

	  }
		HAL_Delay(500);
/*
		u8g_FirstPage(&u8g);
		do {
			u8g_SetFont(&u8g, u8g_font_courB10);
			u8g_DrawStr(&u8g, 0, 35, "blog.domski.pl");
		} while (u8g_NextPage(&u8g));

		HAL_Delay(2000);
		*/

/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
/*
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_B3_Pin))
	  HAL_GPIO_WritePin(LED_BOARD_GPIO_Port, LED_BOARD_Pin, GPIO_PIN_RESET);
	  else
	  HAL_GPIO_WritePin(LED_BOARD_GPIO_Port, LED_BOARD_Pin, GPIO_PIN_SET);
*/
  }
  /* USER CODE END 3 */

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	newAdcValues++;
}

void Nrf_Config(void)
{
	myNRF.DATA_RATE=NRF_DATA_RATE_250KBPS;
	myNRF.TX_POWER=NRF_TX_PWR_M18dBm;
	myNRF.CRC_WIDTH=NRF_CRC_WIDTH_1B;
	myNRF.ADDR_WIDTH=NRF_ADDR_WIDTH_5;
	myNRF.STATE=NRF_STATE_TX;
	myNRF.PayloadLength=32;
	myNRF.RetransmitCount=0;
	myNRF.RetransmitDelay=0;
	myNRF.BUSY_FLAG=0;
	myNRF.RX_BUFFER=nrfRxBuffer;
	myNRF.TX_BUFFER=nrfTxBuffer;
	myNRF.RF_CHANNEL=0;
	myNRF.RX_ADDRESS=nrfRxAddress;
	myNRF.TX_ADDRESS=nrfTxAddress;

	myNRF.spi=&hspi2;
	myNRF.NRF_CSN_GPIO_PIN=GPIO_PIN_12;
	myNRF.NRF_CSN_GPIOx=GPIOB;
	myNRF.NRF_CE_GPIO_PIN=SPI_CE_Pin;
	myNRF.NRF_CE_GPIOx=SPI_CE_GPIO_Port;
	myNRF.NRF_IRQ_GPIO_PIN=SPI_IRQ_Pin;
	myNRF.NRF_IRQ_GPIOx=SPI_IRQ_GPIO_Port;
	myNRF.NRF_IRQn=EXTI0_IRQn;
	myNRF.NRF_IRQ_preempt_priority=3;
	myNRF.NRF_IRQ_sub_priority=0;

	NRF_Init(&myNRF);
}
/** System Clock Configuration
*/
void SystemClock_Config(void)
{

	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_PeriphCLKInitTypeDef PeriphClkInit;

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Configure the Systick interrupt time
	    */
	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	    /**Configure the Systick
	    */
	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
