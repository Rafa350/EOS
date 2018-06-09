#ifndef __hardwareProfile__
#define __hardwareProfile__


#if defined(HARDWARE_CUSTOM)
    #include "HardwareProfile_Custom.h"

#elif defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #include "board/HardwareProfile_PIC32_USB_Starter_Kit_I.h"

#elif defined(HARDWARE_STM32F429I_DISC1)
    #include "board/HardwareProfile_STM32F429I-DISC1.h"

#else
    #error "No se definio HARDWARE_XXXX"
#endif


#endif // __hardwareProfile__