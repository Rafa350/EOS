#ifndef __halI2C_ex__
#define	__halI2CTpl__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halI2C_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halI2C_ex.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halI2C_ex.h"

#endif


#endif // __halI2C_ex__


