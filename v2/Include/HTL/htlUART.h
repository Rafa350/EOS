#ifndef __halUART_ex__
#define	__halUART_ex__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halUART_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halUART_ex.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halUART_ex.h"

#endif


#endif // __halUART_ex__

