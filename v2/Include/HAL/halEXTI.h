#ifndef __halEXTI__
#define	__halEXTI__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halEXTI.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halEXTI.h"
#endif
    

#endif // __halEXTI__

