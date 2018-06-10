#ifndef __board__
#define __board__


#if defined(HARDWARE_CUSTOM)
    #include "Board_Custom.h"

#elif defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #include "board/Board_PIC32_USB_STARTER_Kit_I.h"

#elif defined(HARDWARE_STM32F429I_DISC1)
    #include "board/Board_STM32F429I_DISC1.h"

#elif defined(HARDWARE_STM32F746G_DISC)
    #include "board/Board_STM32F746G_DISC.h"

#else
    #error "No se definio HARDWARE_XXXX"

#endif


#endif // __board__
