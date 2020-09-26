#ifndef __STM32_halSYS__
#define	__STM32_halSYS__


// EOS includes
//
#include "eos.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define halSYSGetSystemClockFrequency()      HAL_RCC_GetSysClockFreq()
#define halSYSGetPeripheralClock1Frequency() HAL_RCC_GetPCLK1Freq()
#define halSYSGetPeripheralClock2Frequency() HAL_RCC_GetPCLK2Freq()


void halSYSInitialize();


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halSYS__


