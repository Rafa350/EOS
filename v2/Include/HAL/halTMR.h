#ifndef __halTMR__
#define	__halTMR__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halTMR.h"
    
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "hal/STM32/halTMR.h"

#endif


#endif // __halTMR__