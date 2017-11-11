#include "HAL/halSYS.h"
#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
#error hardware no soportado
#endif



/// ----------------------------------------------------------------------
/// /brief  System Clock Configuration
///         The system Clock is configured as follow :
///            System Clock source            = PLL (HSE)
///            SYSCLK(Hz)                     = 1800000
///            HCLK(Hz)                       = 180000000
///            AHB Prescaler                  = 1
///            APB1 Prescaler                 = 4
///            APB2 Prescaler                 = 2
///            HSE Frequency(Hz)              = 8000000
///            PLL_M                          = 8
///            PLL_N                          = 360
///            PLL_P                          = 2
///            PLL_Q                          = 7
///            VDD(V)                         = 3.3
///            Main regulator output voltage  = Scale1 mode
///            Flash Latency(WS)              = 5
///
#ifdef STM32F4
static void SystemClock_Config() {

	RCC_ClkInitTypeDef clkInit;
	RCC_OscInitTypeDef oscInit;

	// Enable Power Control clock
	//
	__HAL_RCC_PWR_CLK_ENABLE();

	// The voltage scaling allows optimizing the power consumption when the device is
	// clocked below the maximum system frequency, to update the voltage scaling value
	// regarding system frequency refer to product datasheet.
	//
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	// Enable HSE Oscillator and activate PLL with HSE as source
	//
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
	oscInit.PLL.PLLState = RCC_PLL_ON;
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscInit.PLL.PLLM = 8;
	oscInit.PLL.PLLN = 360;
	oscInit.PLL.PLLP = RCC_PLLP_DIV2;
	oscInit.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&oscInit);

	// Activate the Over-Drive mode
	//
	HAL_PWREx_EnableOverDrive();

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	//
	clkInit.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_5);
}
#endif


/// ----------------------------------------------------------------------
/// @brief  System Clock Configuration
///         The system Clock is configured as follow :
///            System Clock source            = PLL (HSE)
///            SYSCLK(Hz)                     = 216000000
///            HCLK(Hz)                       = 216000000
///            AHB Prescaler                  = 1
///            APB1 Prescaler                 = 4
///            APB2 Prescaler                 = 2
///            HSE Frequency(Hz)              = 25000000
///            PLL_M                          = 25
///            PLL_N                          = 432
///            PLL_P                          = 2
///            PLL_Q                          = 9
///            VDD(V)                         = 3.3
///            Main regulator output voltage  = Scale1 mode
///            Flash Latency(WS)              = 7
///
#ifdef STM32F7
void SystemClock_Config() {

	RCC_ClkInitTypeDef clkInit;
	RCC_OscInitTypeDef oscInit;
	HAL_StatusTypeDef ret = HAL_OK;

	// Enable HSE Oscillator and activate PLL with HSE as source
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
	oscInit.PLL.PLLState = RCC_PLL_ON;
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscInit.PLL.PLLM = 25;
	oscInit.PLL.PLLN = 432;
	oscInit.PLL.PLLP = RCC_PLLP_DIV2;
	oscInit.PLL.PLLQ = 9;

	ret = HAL_RCC_OscConfig(&oscInit);
	if(ret != HAL_OK) {
		while(1)
			continue;
	}

	// Activate the OverDrive to reach the 216 MHz Frequency
	ret = HAL_PWREx_EnableOverDrive();
	if (ret != HAL_OK) {
		while(1)
			continue;
	}

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
	clkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);
	if(ret != HAL_OK) {
		while(1)
			continue;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza el sistema
///
void halSYSInitialize() {

	HAL_Init();
	SystemClock_Config();
}
