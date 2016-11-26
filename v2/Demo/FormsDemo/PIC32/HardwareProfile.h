#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#define HARDWARE_CUSTOM

#if defined(HARDWARE_CUSTOM)
#include "HardwareProfile_Custom.h"
#else
#error "No se definio HARDWARE_XXXX"
#endif


#endif