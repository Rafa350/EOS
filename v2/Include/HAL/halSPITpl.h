#ifndef __halSPITpl__
#define	__halSPITpl__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halSPITpl.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halSPITpl.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halSPITpl.h"

#endif


#endif // __halSPITpl__

