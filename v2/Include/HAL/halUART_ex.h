#ifndef __halUARTTpl__
#define	__halUARTTpl__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halUARTTpl.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halUARTTpl.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halUARTTpl.h"

#endif


#endif // __halUARTTpl__

