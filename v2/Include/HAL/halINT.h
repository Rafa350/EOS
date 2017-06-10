#ifndef __EOS_HAL_INT_H
#define __EOS_HAL_INT_H


#include "eos.h"

#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halINT.h"

#elif defined(EOS_STM32F4)
	#include "HAL/STM32/halINT.h"

#endif


#endif
