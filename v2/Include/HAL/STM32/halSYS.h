#ifndef __STM32_halSYS__
#define	__STM32_halSYS__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


void halSYSInitialize();

uint32_t halSYSGetSystemClockFrequency();
uint32_t halSYSGetPeripheralClock1Frequency();
uint32_t halSYSGetPeripheralClock2Frequency();
uint32_t halSYSGetTimerClock1Frequency();
uint32_t halSYSGetTimerClock2Frequency();


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halSYS__


