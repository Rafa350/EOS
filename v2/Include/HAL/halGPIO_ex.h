#ifndef __halGPIO_ex__
#define	__halGPIO_ex__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halGPIO_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halGPIO_ex.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halGPIO_ex.h"

#endif


#endif // __halGPIO_ex__

