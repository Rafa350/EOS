#ifndef __eosConfig__
#define __eosConfig__


// Configuracio dels leds
//
#define USE_LEDS_LED1
#define USE_LEDS_LED2
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
	#define USE_LEDS_LED3
#endif

// Configuracio dels switch
//
#define USE_SWITCHES_SW1
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define USE_SWITCHES_SW2
#endif
#if defined(HARDWARE_PIC32_USB_STARTER_KIT_I)
#define USE_SWITCHES_SW3
#endif


// Opcions del servei I2CMaster
//
#define eosI2CMasterService_TransactionQueueSize   10
#define eosI2CMasterService_TransactionTimeout     1000
#define eosI2CMasterService_EndTransactionDelay    100


#include "board/board.h"


#endif // __eosConfig__
