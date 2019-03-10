#ifndef __eosUSBDevice__
#define	__eosUSBDevice__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "Controllers/Usb/PIC32/eosUSBDevice.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "Controllers/Usb/STM32/eosUSBDevice.h"

#endif


#endif // __eosUSBDevice__

