#pragma once
#ifndef __eosBoard__
#define __eosBoard__


#if defined(HARDWARE_CUSTOM)
    #include "Board/eosBoard_Custom.h"

#elif defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #include "Board/eosBoard_PIC32_USB_STARTER_KIT_I.h"

#elif defined(HARDWARE_PIC32_ETH_STARTER_KIT)
    #include "Board/eosBoard_PIC32_ETH_STARTER_KIT.h"

#elif defined(HARDWARE_STM32F429I_DISC1)
    #include "Board/eosBoard_STM32F429I_DISC1.h"

#elif defined(HARDWARE_STM32F746G_DISCO)
    #include "Board/eosBoard_STM32F746G_DISCO.h"

#elif defined(HARDWARE_STM32F769I_DISCO)
    #include "Board/eosBoard_STM32F769I_DISCO.h"

#elif defined(HARDWARE_NUCLEO_F030R8)
    #include "Board/eosBoard_NUCLEO_F030R8.h"

#elif defined(HARDWARE_PINGUINO)
    #include "Board/eosBoard_PINGUINO.h"
    
#elif defined(HARDWARE_NONE)    

#else
    #error "Undefined HARDWARE_XXXX"

#endif


#endif // __eosBoard__
