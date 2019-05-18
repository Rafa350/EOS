#ifndef __halGPIO__
#define	__halGPIO__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halGPIO.h"
    #include "HAL/PIC32/halCN.h"
    #ifdef __cplusplus  
        #include "HAL/PIC32/halGPIOTpl.h"
    #endif

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halGPIO.h"
    #ifdef __cplusplus  
        #include "HAL/STM32/halGPIOTpl.h"
    #endif

#endif


#endif // __halGPIO__

