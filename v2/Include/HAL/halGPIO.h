#ifndef __halGPIO__
#define	__halGPIO__


// HAL includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halGPIO.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halGPIO.h"
	#include "HAL/STM32/halGPIO_AF.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halGPIO.h"

#endif


#endif // __halGPIO__

