#pragma once
#ifndef __eosConfig__
#define __eosConfig__


#if defined(EOS_PLATFORM_PIC32MX) || defined(EOS_PLATFORM_PIC32MZ)
	#include "PIC32/eosConfig.h"

#elif defined(EOS_PLATFORM_STM32F7)
	#include "STM32F7/eosConfig.h"

#endif


#endif // __eosConfig__
