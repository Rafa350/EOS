#ifndef __halSPI_ex__
#define	__halSPI_ex__


// EOS includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halSPI_ex.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halSPI_ex.h"

#elif defined(EOS_MSP432)
    #include "HAL/MSP432/halSPI_ex.h"

#endif


#endif // __halSPI_ex__

