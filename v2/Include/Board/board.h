#ifndef __board__
#define __board__


#if defined(HARDWARE_CUSTOM)
    #include "board_Custom.h"

#elif defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #include "board/board_PIC32_USB_STARTER_Kit_I.h"

#elif defined(HARDWARE_STM32F429I_DISC1)
    #include "board/board_STM32F429I_DISC1.h"

#elif defined(HARDWARE_STM32F746G_DISCO)
    #include "board/board_STM32F746G_DISCO.h"

#elif defined(HARDWARE_STM32F769I_DISCO)
    #include "board/board_STM32F769I_DISCO.h"

#else
    #error "No se definio HARDWARE_XXXX"

#endif


#endif // __board__