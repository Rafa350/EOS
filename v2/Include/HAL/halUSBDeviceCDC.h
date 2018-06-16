#ifndef __halUSBDeviceCDC__
#define	__halUSBDeviceCDC__


// EOS includes
//
#include "eos.h"
#include "hal/hal.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halUSBDeviceCDC.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "hal/STM32/halUSBDeviceCDC.h"

#endif


#endif // __halUSBDeviceCDC__

