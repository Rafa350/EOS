#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_DISPLAY


#include "Board/eosBoard.h"


// Opcions de configuracio pel servei 'DigInput'
//
#define eosDigInputService_Enabled                       1
#define eosDigInputService_MaxInputs                    16


// Opcions de configuracio pel servei 'DigOutput'
//
#define DigOutputService_Enabled                         1
#define eosDigOutputService_MaxOutputs                  16


// Opcions de configuracio pel servei 'I2CMaster'
//
#define eosI2CMasterService_Enabled                      1
#define eosI2CMasterService_MaxInstances                 2
#define eosI2CMasterService_MaxTransactions             20
#define eosI2CMasterService_EndTransactionDelay         15
#define eosI2CMasterService_TransactionTimeout        1000


// Opcions de configuracio del servei 'HTTP'
//
#define eosHTTPService_Enabled                           1

#define eosHTTPService_Port                             80

#define eosHTTPService_Addr0                	       192
#define eosHTTPService_Addr1						   168
#define eosHTTPService_Addr2                             1
#define eosHTTPService_Addr3                           240

#define eosHTTPService_Mask0                           255
#define eosHTTPService_Mask1                           255
#define eosHTTPService_Mask2                           255
#define eosHTTPService_Mask3                             0

#define eosHTTPService_Gateway0                        192
#define eosHTTPService_Gateway1                        168
#define eosHTTPService_Gateway2                          1
#define eosHTTPService_Gateway3                        254


#endif // __eosConfig__
