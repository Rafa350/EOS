#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


#define HARDWARE_STM32F429I_DISC1


#if defined(HARDWARE_CUSTOM)
#include "HardwareProfile_Custom.h"

#elif defined(HARDWARE_STM32F429I_DISC1)
#include "HardwareProfile_STM32F429I-DISC1.h"

#else
#error "No se definio HARDWARE_XXXX"
#endif


#endif
