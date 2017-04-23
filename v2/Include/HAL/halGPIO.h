#ifndef __EOS_HAL_GPIO_H
#define	__EOS_HAL_GPIO_H


#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "hal/halGPIO_PIC32.h"

#elif defined(EOS_STM32F4)
	#include "hal/halGPIO_STM32F4.h"

#endif


#endif

