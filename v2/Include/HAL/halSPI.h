#ifndef __halSPI__
#define __halSPI__


// HAL includes
//
#include "HAL/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halSPI.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "HAL/STM32/halSPI.h"

#endif



#endif // __halSPI__
