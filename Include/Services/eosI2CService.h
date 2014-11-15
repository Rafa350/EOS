#ifndef __EOS_I2SSERVICE_H
#define __EOS_I2CSERVICE_H


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
struct __I2CMasterService {};
struct __I2CTransaction {};
#endif

typedef struct __I2CMasterService *eosHI2CMasterService;
typedef struct __I2CTransaction *eosHI2CTransaction;

typedef struct {                       // Parametres del servei
    I2C_MODULE_ID id;                  // -Modul I2C
    eosHTickService hTickService;      // -Handler del servei TICK
} eosI2CServiceParams;

typedef enum {                         // Tipus de transaccio
    type_Send,                         // -Transmissio al escalu
    type_Receive,                      // -Recepcio des de l'escalu
    type_SendAndReceive                // -Combinat de transmissio i recepcio
} TransactionType;

typedef struct {                       // Parametres d'una transaccio
    TransactionType type;              // -Tipus de transaccio
    BYTE *txData;                      // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes en el buffer de transmissio
    BYTE *rxData;                      // -Buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes rebuts
} eosI2CTransactionParams;


extern eosResult eosI2CMasterServiceInitialize(eosI2CServiceParams *params, eosHI2CMasterService *hService);
extern void eosI2CMasterServiceTask(eosHI2CMasterService hService);
extern void eosI2CMasterServiceISRTick(eosHI2CMasterService hService);

extern eosResult eosI2CMasterStartTransaction(eosHI2CMasterService hService, eosI2CTransactionParams *params, eosHI2CTransaction *hTransaction);
extern eosResult eosI2CMasterCancelTransaction(eosHI2CTransaction hTransaction);
extern BOOL eosI2CMasterTransactionIsPending(eosHI2CMasterService hTransaction);


#endif

