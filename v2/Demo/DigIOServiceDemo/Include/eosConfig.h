#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
	#define USE_LEDS_LED3
#endif

#define USE_SWITCHES_SW1
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #define USE_SWITCHES_SW2
#endif
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
    #define USE_SWITCHES_SW3
#endif

#define xUSE_APPLICATION_TICK
#define APPLICATION_TICK_PERIOD     10


#include "board/eosBoard.h"


// Configuracio del servei DigInputs
//
#define DigInputService_Enabled                  1    // Servei activat
#define DigInputService_CommandQueueSize        10    // Tamany de la cua de comandes
#define DigInputService_SafeMode                 1    // Modus segur

// Configuracio del servei DigOutputs
//
#define DigOutputService_Enabled                 1    // Servei activat
#define DigOutputService_CommandQueueSize        5    // Tamany de la cua de comandes
#define DigOutputService_SafeMode                1    // Modus segur


#endif // __eosConfig__
