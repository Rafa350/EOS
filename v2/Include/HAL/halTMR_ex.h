#ifndef __halTMR_ex__
#define	__halTMR_ex__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halTMR_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halTMR_ex.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halTMR_ex.h"

#endif


#endif // __halTMR_ex__

