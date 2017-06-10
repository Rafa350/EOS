#ifndef __EOS_HAL_GPIO_H
#define	__EOS_HAL_GPIO_H


#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "HAL/PIC32/halGPIO.h"
    #include "HAL/PIC32/halCN.h"

#elif defined(EOS_STM32F4)
	#include "hal/STM32/halGPIO.h"

#endif


#endif

