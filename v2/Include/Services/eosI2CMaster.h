#ifndef __EOS_I2CMASTER_H
#define __EOS_I2CMASTER_H


#ifndef __EOS_H
#include "eos.h"
#endif

#include "peripheral/i2c/plib_i2c.h"


typedef struct __eosI2CMasterService *eosI2CMasterServiceHandle;
typedef struct __eosI2CTransaction *eosI2CTransactionHandle;

typedef void (*eosI2CMasterCallback)(eosI2CTransactionHandle hTransaction, void *context);

typedef struct {                       // Parametres del servei
    I2C_MODULE_ID id;                  // -Modul I2C
    unsigned priority;                 // -Prioritat de la tasca del servei
} eosI2CServiceParams;

typedef struct {                       // Parametres d'una transaccio
    unsigned address;                  // -Adressa del esclau
    uint8_t *txBuffer;                 // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes en el buffer de transmissio
    uint8_t *rxBuffer;                 // -Buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio
    eosI2CMasterCallback onEndTransaction;  // -Event END_TRANSACTION
    eosI2CMasterCallback onError;      // -Event ON_ERROR
    void *context;                     // -Parametre del event
} eosI2CTransactionParams;


extern eosI2CMasterServiceHandle eosI2CMasterServiceInitialize(eosI2CServiceParams *params);
extern eosI2CTransactionHandle eosI2CMasterStartTransaction(eosI2CMasterServiceHandle hService, eosI2CTransactionParams *params);
extern unsigned eosI2CMasterGetTransactionResult(eosI2CTransactionHandle hTransaction);


#endif

