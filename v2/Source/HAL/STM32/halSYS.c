#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halSYS.h"
#if defined(EOS_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal.h"
#else
#error Hardware no soportado
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza el sistema
///
void halSYSInitialize() {

	HAL_Init();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia (teorica) del rellotge del sistema.
/// \return   El valor de la frequencia.
///
uint32_t halSYSGetSystemClockFrequency() {

	return HAL_RCC_GetSysClockFreq();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del relotge dels periferics AB1
/// \return   El valor de la frequencia.
///
uint32_t halSYSGetPeripheralClock1Frequency() {

	return HAL_RCC_GetPCLK1Freq();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del relotge dels periferics AB2
/// \return   El valor de la frequencia.
///
uint32_t halSYSGetPeripheralClock2Frequency() {

	return HAL_RCC_GetPCLK2Freq();
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del relotge dels timers AB1
/// \return   El valor de la frequencia.
///
uint32_t halSYSGetTimerClock1Frequency() {

	uint32_t f = HAL_RCC_GetPCLK1Freq();

	// PCLK1 prescaler equal to 1 => TIMCLK = PCLK1
	if((RCC->CFGR & RCC_CFGR_PPRE1) == 0)
	    return (f);

    // PCLK1 prescaler different from 1 => TIMCLK = 2 * PCLK1
	else
		return(2 * f);
}


/// ----------------------------------------------------------------------
/// \brief    Obte la frequencia del relotge dels timers AB2
/// \return   El valor de la frequencia.
///
uint32_t halSYSGetTimerClock2Frequency() {

	uint32_t f = HAL_RCC_GetPCLK2Freq();

	// PCLK2 prescaler equal to 1 => TIMCLK = PCLK1
	if((RCC->CFGR & RCC_CFGR_PPRE2) == 0)
	    return (f);

    // PCLK2 prescaler different from 1 => TIMCLK = 2 * PCLK1
	else
		return(2 * f);
}

