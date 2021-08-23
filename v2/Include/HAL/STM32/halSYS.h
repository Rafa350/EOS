/// \file     halSYS.h
/// \author   Rafael Serrano (rsr.openware@gmail.com)
/// \brief    Gestio del sistema
/// \addtogroup HAL Hardware Abstraction Layer
/// @{
/// \addtogroup HAL_STM32 STM32 Hardware Abstraction Layer
/// @{
/// \defgroup HAL_STM32_SYS SYSTEM
/// @{
///
#ifndef __STM32_halSYS__
#define	__STM32_halSYS__


// EOS includes
//
#include "HAL/hal.h"


#ifdef	__cplusplus
extern "C" {
#endif


void halSYSInitialize();

uint32_t halSYSGetSystemClockFrequency();
uint32_t halSYSGetPeripheralClock1Frequency();
uint32_t halSYSGetPeripheralClock2Frequency();
uint32_t halSYSGetTimerClock1Frequency();
uint32_t halSYSGetTimerClock2Frequency();

unsigned halSYSGetTick();
bool halSYSCheckTimeout(unsigned startTime, unsigned blockTime);

#ifdef	__cplusplus
}
#endif


#endif // __STM32_halSYS__

/// @}
/// @}
/// @}

