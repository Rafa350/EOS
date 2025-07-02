#include "eos.h"
#include "eosAssert.h"


using namespace eos;


static void initializeMPU() {

	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU as Strongly ordered for not defined regions */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x00;
	MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
	MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x87;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


/*
*         The system Clock is configured as follow :
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 216000000
*            HCLK(Hz)                       = 216000000
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 4
*            APB2 Prescaler                 = 2
*            HSE Frequency(Hz)              = 25000000
*            PLL_M                          = 25
*            PLL_N                          = 432
*            PLL_P                          = 2
*            VDD(V)                         = 3.3
*            Main regulator output voltage  = Scale1 mode
*            Flash Latency(WS)              = 7
*/
static void initializeClock() {

	bool ok;

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	ok = HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK;
	eosAssert(ok);

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	ok = HAL_PWREx_EnableOverDrive() == HAL_OK;
	eosAssert(ok);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
								 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ok = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) == HAL_OK;
	eosAssert(ok);
}


static void initializeCache() {

	SCB_EnableICache();
	SCB_EnableDCache();
}


static void initializeHAL() {

	HAL_Init();
}


void appInitialize() {

	initializeMPU();
	initializeCache();
	initializeHAL();
	initializeClock();

	__HAL_FREEZE_TIM6_DBGMCU();
}
