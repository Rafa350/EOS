#ifndef __halGPIOTpl__
#define	__halGPIOTpl__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halGPIOTpl.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halGPIOTpl.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halGPIOTpl.h"

#endif


#endif // __halGPIOTpl__

