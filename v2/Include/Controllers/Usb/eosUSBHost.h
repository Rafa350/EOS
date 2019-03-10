#ifndef __eosUSBHost__
#define	__eosUSBHost__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "Controllers/Usb/PIC32/eosUSBHost.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "Controllers/Usb/STM32/eosUSBHost.h"

#endif


#endif // __eosUSBHost__

