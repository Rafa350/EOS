#ifndef __EOS_HAL_INT_H
#define __EOS_HAL_INT_H


#include "eos.h"

#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "hal/halINT_PIC32.h"

#elif defined(EOS_STM32F4)
	#include "hal/halINT_STM32F.h"

#endif


#endif