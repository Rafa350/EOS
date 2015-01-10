#ifndef __EOS_I2CMASTER_H
#define __EOS_I2CMASTER_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_I2C_H
#include "peripheral/i2c/plib_i2c.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif


#define eos_ERROR_I2C_INVALID_MODULE   (eos_ERROR_USER + 0)
#define eos_ERROR_I2C_TOO_SERVICES     (eos_ERROR_USER + 1)
#define eos_ERROR_I2C_TOO_TRANSACTIONS (eos_ERROR_USER + 2)


typedef struct __eosI2CMasterService *eosI2CMasterServiceHandle;
typedef struct __eosI2CTransaction *eosI2CTransactionHandle;

typedef void (*eosI2CMasterCallback)(eosI2CTransactionHandle hTransaction);

typedef struct {                       // Parametres del servei
    I2C_MODULE_ID id;                  // -Modul I2C
    eosTickServiceHandle hTickService; // -Handler del servei TICK
} eosI2CServiceParams;

typedef struct {                       // Parametres d'una transaccio
    unsigned address;                  // -Adressa del esclau
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes en el buffer de transmissio
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio
    eosI2CMasterCallback onEndTransaction;  // -Event END_TRANSACTION
    void *context;                     // -Parametre del event
} eosI2CTransactionParams;


extern eosI2CMasterServiceHandle eosI2CMasterServiceInitialize(eosI2CServiceParams *params);
extern bool eosI2CMasterIsReady(eosI2CMasterServiceHandle hService);
extern void eosI2CMasterServiceTask(eosI2CMasterServiceHandle hService);
extern void eosI2CMasterServiceTick(eosI2CMasterServiceHandle hService);

extern eosI2CTransactionHandle eosI2CMasterStartTransaction(eosI2CMasterServiceHandle hService, eosI2CTransactionParams *params);
extern void *eosI2CMasterGetTransactionContext(eosI2CTransactionHandle hTransaction);
extern unsigned eosI2CMasterGetTransactionResult(eosI2CTransactionHandle hTransaction);


#endif

