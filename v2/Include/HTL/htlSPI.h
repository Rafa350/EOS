#ifndef __htlSPI__
#define	__htlSPI__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HTL/PIC32/htlSPI.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HTL/STM32/htlSPI.h"

#elif defined(EOS_MSP432)
    #include "HTL/MSP432/htlSPI.h"

#endif


#endif // __htlSPI__

