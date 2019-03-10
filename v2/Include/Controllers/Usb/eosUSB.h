#ifndef __eosUSB__
#define	__eosUSB__


// EOS includes
//
#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "Controllers/Usb/PIC32/eosUSB.h"

#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
	#include "Controllers/Usb/STM32/eosUSB.h"

#endif


#endif // __eosUSB__

