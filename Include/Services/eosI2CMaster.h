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


#ifndef __EOS_I2CMASTER_INTERNAL
struct __eosI2CMasterService {};
struct __eosI2CTransaction {};
#endif

typedef struct __eosI2CMasterService *eosHI2CMasterService;
typedef struct __eosI2CTransaction *eosHI2CTransaction;

typedef struct {                       // Parametres del servei
    I2C_MODULE_ID id;                  // -Modul I2C
    unsigned queueSize;                // -Tamany de la cua de transaccions
    eosHTickService hTickService;      // -Handler del servei TICK
} eosI2CServiceParams;

typedef enum {                         // Tipus de transaccio
    ttRead,                            // -Lectura
    ttWrite,                           // -Escriptura
    ttWriteRead                        // -Escriptura i lectura posterior
} TransactionType;

typedef struct {                       // Parametres d'una transaccio
    unsigned address;                  // -Adressa del esclau
    TransactionType type;              // -Tipus de transaccio
    BYTE *txBuffer;                    // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes en el buffer de transmissio
    BYTE *rxBuffer;                    // -Buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes rebuts
    eosCallback onEndTransaction;      // -Event END_TRANSACTION
    void *context;                     // -Parametre del event
} eosI2CTransactionParams;


extern eosResult eosI2CMasterServiceInitialize(eosI2CServiceParams *params, eosHI2CMasterService *hService);
extern void eosI2CMasterServiceTask(eosHI2CMasterService hService);
extern void eosI2CMasterServiceISRTick(eosHI2CMasterService hService);

extern eosResult eosI2CMasterStartTransaction(eosHI2CMasterService hService, eosI2CTransactionParams *params, eosHI2CTransaction *hTransaction);
extern eosResult eosI2CMasterCancelTransaction(eosHI2CTransaction hTransaction);
extern bool eosI2CMasterTransactionIsPending(eosHI2CTransaction hTransaction);


#endif

