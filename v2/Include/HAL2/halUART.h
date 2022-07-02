#ifndef __hal2UART__
#define	__hal2UART__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL2/PIC32/halUART.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL2/STM32/halUART.h"

#endif


#endif // __hal2UART__

