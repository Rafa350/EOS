#ifndef __EOS_HAL_SPI_H
#define __EOS_HAL_SPI_H


#include "eos.h"


#if defined(EOS_PIC32MX) || defined(EOS_PIC32MZ)
	#include "hal/PIC32/halSPI.h"

#elif defined(EOS_STM32F4)
	#include "hal/STM32/halSPI.h"

#endif



#endif
