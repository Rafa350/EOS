#ifndef __PIC32_halSYS__
#define	__PIC32_halSYS__


// HAL includes
//
#include "HAL/hal.h"


#ifdef	__cplusplus
extern "C" {
#endif


void halSYSInitialize(void);


#define halSYSGetSystemClockFrequency()     CLOCK_SYSTEM_HZ
#define halSYSGetPeripheralClockFrequency() CLOCK_PERIPHERICAL_HZ


#ifdef	__cplusplus
}
#endif


#endif // __PIC32_halSYS__


