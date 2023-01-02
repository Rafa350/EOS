#include "eos.h"
#include "hal/halSYS.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_flash_ex.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sdram.h"


/// ----------------------------------------------------------------------
/// \brief Configura el rellotge del sistema
///
static void ConfigureSystemClock() {

	RCC_ClkInitTypeDef clkInit;
	RCC_OscInitTypeDef oscInit;

	// Enable HSE Oscillator and activate PLL with HSE as source
	//
	oscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscInit.HSEState = RCC_HSE_ON;
	oscInit.HSIState = RCC_HSI_OFF;
	oscInit.PLL.PLLState = RCC_PLL_ON;
	oscInit.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscInit.PLL.PLLM = 25;
	oscInit.PLL.PLLN = 400; // 432???
	oscInit.PLL.PLLP = RCC_PLLP_DIV2;
	oscInit.PLL.PLLQ = 9;
	HAL_RCC_OscConfig(&oscInit);

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
    // clocks dividers
	//
	clkInit.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkInit.APB1CLKDivider = RCC_HCLK_DIV4;
	clkInit.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&clkInit, FLASH_LATENCY_7);
}


/// ----------------------------------------------------------------------
/// \brief Configura el cache del sistema.
///
void ConfigureSystemCache() {

	SCB_EnableICache();
    SCB_EnableDCache();
}


/// ----------------------------------------------------------------------
/// \brief Configura el modul SDRAM
///
static void ConfigureSDRAM() {

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/// ----------------------------------------------------------------------
/// \brief Configura el modul MPU
///
static void ConfigureMPU() {

	MPU_Region_InitTypeDef mpuInit;

	// Disable the MPU
	//
	HAL_MPU_Disable();

	// Configure the MPU as Normal Non Cacheable for Ethernet Buffers in the SRAM2
	//
	mpuInit.Enable = MPU_REGION_ENABLE;
	mpuInit.BaseAddress = 0x2004C000;
	mpuInit.Size = MPU_REGION_SIZE_16KB;
	mpuInit.AccessPermission = MPU_REGION_FULL_ACCESS;
	mpuInit.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	mpuInit.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	mpuInit.IsShareable = MPU_ACCESS_SHAREABLE;
	mpuInit.Number = MPU_REGION_NUMBER0;
	mpuInit.TypeExtField = MPU_TEX_LEVEL1;
	mpuInit.SubRegionDisable = 0x00;
	mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	HAL_MPU_ConfigRegion(&mpuInit);

	// Configure the MPU as Device for Ethernet Descriptors in the SRAM2
	//
	mpuInit.Enable = MPU_REGION_ENABLE;
	mpuInit.BaseAddress = 0x2004C000;
	mpuInit.Size = MPU_REGION_SIZE_256B;
	mpuInit.AccessPermission = MPU_REGION_FULL_ACCESS;
	mpuInit.IsBufferable = MPU_ACCESS_BUFFERABLE;
	mpuInit.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	mpuInit.IsShareable = MPU_ACCESS_SHAREABLE;
	mpuInit.Number = MPU_REGION_NUMBER1;
	mpuInit.TypeExtField = MPU_TEX_LEVEL0;
	mpuInit.SubRegionDisable = 0x00;
	mpuInit.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	HAL_MPU_ConfigRegion(&mpuInit);

	// Enable the MPU
	//
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void appInitialize() {

	#ifdef EOS_DEBUG
		__HAL_FREEZE_TIM6_DBGMCU();
	#endif

	ConfigureMPU();
	ConfigureSystemCache();
    halSYSInitialize();
	ConfigureSystemClock();
	ConfigureSDRAM();
}
