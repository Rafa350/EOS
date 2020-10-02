#ifndef __eosConfig__
#define __eosConfig__


// Configuracio dels leds
//
#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_LEDS_LED3

// Configuracio dels switch
//
#define USE_SWITCHES_SW1
#define USE_SWITCHES_SW2
#define USE_SWITCHES_SW3


// Opcions del servei I2CMaster
//
#define eosI2CMasterService_TransactionQueueSize   10
#define eosI2CMasterService_TransactionTimeout     1000
#define eosI2CMasterService_EndTransactionDelay    100


#include "board/eosBoard.h"


#endif // __eosConfig__
