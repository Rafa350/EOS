#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_DISPLAY
#define USE_TOUCHPAD_FT5336

#include "board/board.h"


// Opcions de configuracio pel servei 'DigInput'
//
#define eosOPTIONS_UseDigInputService                    1
#define eosDigInputService_MaxInputs                    16


// Opcions de configuracio pel servei 'DigOutput'
//
#define eosOPTIONS_UseDigOutputService                   1
#define eosDigOutputService_MaxOutputs                  16


// Opcions de configuracio pel servei 'I2CMaster'
//
#define eosOPTIONS_UseI2CMasterService                   1
#define eosI2CMasterService_MaxInstances                 2
#define eosI2CMasterService_MaxTransactions             20
#define eosI2CMasterService_EndTransactionDelay         15
#define eosI2CMasterService_TransactionTimeout        1000



#endif
