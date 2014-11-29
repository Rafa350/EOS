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


#ifndef __EOS_I2CMASTER_INTERNAL
struct __eosI2CMasterService {};
struct __eosI2CTransaction {};
#endif

typedef struct __eosI2CMasterService *eosHI2CMasterService;
typedef struct __eosI2CTransaction *eosHI2CTransaction;

typedef struct {                       // Parametres del servei
    I2C_MODULE_ID id;                  // -Modul I2C
    eosHTickService hTickService;      // -Handler del servei TICK
} eosI2CServiceParams;

typedef struct {                       // Parametres d'una transaccio
    unsigned address;                  // -Adressa del esclau
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes en el buffer de transmissio
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes rebuts
    eosCallback onEndTransaction;      // -Event END_TRANSACTION
    void *context;                     // -Parametre del event
} eosI2CTransactionParams;


extern eosHI2CMasterService eosI2CMasterServiceInitialize(eosI2CServiceParams *params);
extern void eosI2CMasterServiceTask(eosHI2CMasterService hService);
extern void eosI2CMasterServiceISRTick(eosHI2CMasterService hService);

extern eosHI2CTransaction eosI2CMasterStartTransaction(eosHI2CMasterService hService, eosI2CTransactionParams *params);


#endif

