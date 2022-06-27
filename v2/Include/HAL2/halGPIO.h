#ifndef __hal2GPIO__
#define	__hal2GPIO__


// HAL includes
//
#include "HAL2/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL2/PIC32/halGPIO.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL2/STM32/halGPIO.h"

#elif defined(EOS_MSP432)
    #include "HAL2/MSP432/halGPIO.h"

#endif


#endif // __hal2GPIO__

