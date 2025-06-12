#ifndef __eosConfig__
#define __eosConfig__


#define USE_LED1
#define USE_LED2

#define USE_USB_DEVICE0


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


// Opcions de configuracio pel servei 'Forms'
//
#define eosOPTIONS_FORMS_MAX_INSTANCES           1    // Numero maxim d'instancies del servei
#define eosOPTIONS_FORMS_MAX_QUEUE_SIZE         50    // Numero maxim de missatges en la cua


// Opcions del display
//
#define FONT_USE_Arial10pt
#define FONT_USE_Arial12pt
#define FONT_USE_Arial24pt


#endif
