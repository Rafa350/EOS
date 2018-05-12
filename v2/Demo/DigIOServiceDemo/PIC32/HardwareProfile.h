#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


#if defined(HARDWARE_CUSTOM)
    #include "HardwareProfile_Custom.h"
#elif defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #include "HardwareProfile_PIC32_USB_Starter_Kit_I.h"
#else
    #error "No se definio HARDWARE_XXXX"
#endif


#endif