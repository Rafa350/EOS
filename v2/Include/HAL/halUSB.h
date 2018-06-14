#ifndef __halUSB__
#define	__halUSB__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halUSB.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "hal/STM32/halUSB.h"

#endif


#endif // __halUSB__

