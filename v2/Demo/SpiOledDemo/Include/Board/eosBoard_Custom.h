#pragma once
#ifndef __eosBoard_Custom__
#define __eosBoard_Custom__


#if defined(HARDWARE_CUSTOM_PIC32_USB_STARTER_KIT_I)
    #include "Board/eosBoard_Custom_PIC32_USB_STARTER_KIT_I.h"

#elif defined(HARDWARE_CUSTOM_STM32F746G_DISCO)
    #include "Board/eosBoard_Custom_STM32F746G_DISCO.h"

#elif defined(HARDWARE_CUSTOM_STM32F429I_DISC1)
    #include "Board/eosBoard_Custom_STM32F429I_DISC1.h"

#elif defined(HARDWARE_CUSTOM_NUCLEO_G071RB)
    #include "Board/eosBoard_Custom_NUCLEO_G071RB.h"

#endif


#endif // __eosBoard_Custom__
