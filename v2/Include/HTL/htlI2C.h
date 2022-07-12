#ifndef __htlI2C__
#define	__htlI2C__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HTL/PIC32/htlI2C.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HTL/STM32/htlI2C.h"
    
#elif defined(EOS_MSP432)
    #include "HTL/MSP432/htlI2C.h"

#endif


#endif // __htlI2C__


