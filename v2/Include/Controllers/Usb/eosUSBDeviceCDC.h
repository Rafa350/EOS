#ifndef __eosUSBDeviceCDC__
#define	__eosUSBDeviceCDC__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "Controllers/Usb/PIC32/eosUSBDeviceCDC.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "Controllers/Usb/STM32/eosUSBDeviceCDC.h"

#endif


#endif // __eosUSBDeviceCDC__

