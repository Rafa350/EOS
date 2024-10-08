#include "HAL/hal.h"
#include "HAL/STM32/halSYS.h"
#if defined(EOS_PLATFORM_STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(EOS_PLATFORM_STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(EOS_PLATFORM_STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(EOS_PLATFORM_STM32F7)
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
	//
	if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0)
	    return (f);

    // PCLK1 prescaler different from 1 => TIMCLK = 2 * PCLK1
	//
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
	//
	if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0)
	    return (f);

    // PCLK2 prescaler different from 1 => TIMCLK = 2 * PCLK1
	//
	else
		return(2 * f);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el tick del sistema.
/// \return   El valor del tick.
///
unsigned halSYSGetTick() {

	return HAL_GetTick();
}


/// ----------------------------------------------------------------------
/// \brief    Verifica el temps.
/// \param    startTime: Temps des del inici.
/// \param    maxTime: Temps maxim.
/// \return   Trus si ha passat el limit.
///
bool halSYSCheckTimeout(
	unsigned startTime,
	unsigned maxTime) {

	int time = HAL_GetTick();
	return ((__abs_diff(time, startTime) > maxTime) && (maxTime != -1)) || (maxTime == 0);
}

