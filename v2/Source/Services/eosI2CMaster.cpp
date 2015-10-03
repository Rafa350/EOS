#include "Services/eosI2CMaster.hpp"
#include "System/eosInterrupts.h"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"
#include "System/eosSemaphore.hpp"

#include "peripheral/int/plib_int.h"
#include "Peripheral/i2c/plib_i2c.h"


const unsigned taskStackSize = 512;
const eos::TaskPriority taskPriority = eos::TaskPriority::normal;
const unsigned queueMaxItems = 20;
const unsigned baudRate = 100000;


typedef enum {                         // Estat de la transaccio
    transactionIdle,                   // -En espera de iniciar
    transactionSendAddress,            // -Transmeteix l'adressa
    transactionSendLength,             // -Transmeteix el byte de longitut
    transactionSendData,               // -Transmeteix un byte de dades
    transactionSendCheck,              // -Transmeteix el byte de verificacio
    transactionSendFinished,           // -Ha finalitzat la transmissio
    transactionStartReceive,           // -Inicia la recepcio de dades
    transactionReceiveLength,          // -Rebent un byte de longitut
    transactionReceiveData,            // -Rebent un byte de dades
    transactionReceiveCheck,           // -Rebent un byte de verificacio
    transactionAck,                    // -ACK transmitit
    transactionNak,                    // -NAK transmitit
    transactionWaitStop,               // -Esperant STOP
    transactionFinished                // -Finalitzada
} eosI2CTransactionState;

typedef struct __eosI2CTransaction {   // Dades internes d'una transaccio
    bool inUse;                        // -Indica si esta en us en el pool
    I2C_MODULE_ID id;                  // -Identificador de modul i2c
    eosSemaphoreHandle hSemaphore;     // -Semafor per notificar el fi de la transaccio
    eosI2CTransactionState state;      // -Estat de la transaccio
    uint8_t address;                   // -Adressa de l'esclau
    unsigned index;                    // -Index
    unsigned maxIndex;                 // -Valor maxim per 'index'
    bool waitingSlaveACK;              // -Esperant ACK/NAK del esclau
    bool writeMode;                    // -Indica si esta en modus escriptura
    uint8_t check;                     // -Byte de verificacio
    eosI2CMasterCallback onEndTransaction;  // -Event END_TRANSACTION
    eosI2CMasterCallback onError;      // -Event ON_ERROR
    void *context;                     // -Parametres del event
    uint8_t *txBuffer;                 // -Buffer de transmissio
    unsigned txCount;                  // -Numero de bytes a transmetre
    uint8_t *rxBuffer;                 // -Buffer de recepcio
    unsigned rxCount;                  // -Numero de bytes en el buffer de recepcio
    unsigned rxSize;                   // -Tamany del buffer de recepcio en bytes
    unsigned error;                    // -Codi d'error
} eosI2CTransaction;


eos::I2CMasterTransaction *transactionMap[5];


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eos::I2CMasterService::I2CMasterService(
 *              unsigned moduleId)
 *
 *       Entrada:
 *           moduleId: Identificador del modulI2C
 *
 *************************************************************************/

eos::I2CMasterService::I2CMasterService(
    unsigned moduleId) :
    task(taskStackSize, taskPriority, this),
    queue(queueMaxItems) {

    this->moduleId = moduleId;        
}


/*************************************************************************
 *
 *       Inicia una transaccio
 *
 *       Funcio:
 *           void eos::I2CMasterService::startTransaction(
 *               eosI2CMasterTransaction *transaction)
 *
 *       Entrada:
 *           transaction : La transaccio a iniciar
 *
 *************************************************************************/

void eos::I2CMasterService::startTransaction(
    eos::I2CMasterTransaction *transaction) {
    
    queue.put(transaction, 5000);
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eos::I2CMasterService::run()
 *
 *************************************************************************/

void eos::I2CMasterService::run() {

    halI2CMasterInitialize(moduleId, baudRate, interruptCallback, this);

    while (true) {
           
        eos::I2CMasterTransaction *transaction;
        while (queue.get(transaction, 0xFFFFFFFF)) {
        
            // Espera a que el bus estigui lliure
            //
            while (!halI2CMasterIsBusIdle(moduleId)) 
                eos::Task::delay(20);

            // Prepara la transaccio
            //
            hTransaction->writeMode = hTransaction->txBuffer && hTransaction->txCount;
            hTransaction->state = transactionSendAddress;
            hTransaction->hSemaphore = hService->hSemaphore;

            // Inicia la comunicacio. A partir d'aquest punt es
            // generen les interrupcions del modul I2C
            //
            transactionMap[moduleId] = hTransaction;
            halI2CMasterStart(moduleId);

            // Espera que finalitzi la transaccio
            //
            if (eosSemaphoreTake(hService->hSemaphore, eosI2CMasterService_TransactionTimeout)) {
                
                // Crida a la funcio callback, si esta definida
                //
                if (hTransaction->onEndTransaction != NULL)
                    hTransaction->onEndTransaction(hTransaction, hTransaction->context);
            }
            else {
                
                // Crida a la funcio callback, si esta definida
                //
                if (hTransaction->onError != NULL)
                    hTransaction->onError(hTransaction, hTransaction->context);
            }

            // Retart entre transaccions
            //
            eos::Task::delay(eosI2CMasterService_EndTransactionDelay);
            
            // Destrueix la transaccio
            //
            eosPoolFree(hTransaction);
            transactionMap[moduleId] = NULL;
        }
    }
}


void eos::I2CMasterService::interruptCallback(
    unsigned moduleId,
    void *param) {
    
    eos::I2CMasterService *service = param;
}


/*************************************************************************
 *
 *       Procesa els events de la comunicacio I2C
 *
 *       Funcio:
 *           void i2cInterrupt(
 *              I2C_MODULE_ID id)
 *
 *       Entrada:
 *           id: Identificador del module I2C
 *
 *       Notes:
 *           Transmissio/Recepcio en format de trama
 *           |LENGTH|DATA-1|DATA-2| . . . |DATA-n|CHECK|
 *
 *************************************************************************/

static void i2cInterrupt(
    I2C_MODULE_ID id) {

    eosI2CTransactionHandle hTransaction = transactionMap[id];
    if (hTransaction != NULL) {

        switch (hTransaction->state) {

            case transactionSendAddress:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                }

                else {

                    // Envia l'adressa del esclau
                    //
                    I2C_7_BIT_ADDRESS addr;
                    PLIB_I2C_ADDRESS_7_BIT_FORMAT(
                        addr, 
                        hTransaction->address, 
                        hTransaction->writeMode ? I2C_WRITE : I2C_READ);
                    PLIB_I2C_TransmitterByteSend(id, addr.byte);

                    hTransaction->index = 0;
                    hTransaction->check = addr.byte;

                    if (hTransaction->writeMode)
                        hTransaction->state = transactionSendLength;
                    else
                        hTransaction->state = transactionStartReceive;
                }
                break;

            case transactionSendLength:
            case transactionSendData:
            case transactionSendCheck:
            case transactionSendFinished:

                // Si hi ha colissio, reinicia la transmissio
                //
                if (PLIB_I2C_ArbitrationLossHasOccurred(id)) {
                    PLIB_I2C_ArbitrationLossClear(id);
                    while (!PLIB_I2C_BusIsIdle(id))
                        continue;
                    PLIB_I2C_MasterStart(id);
                    hTransaction->state = transactionSendAddress;
                }
            
                else {
                
                    // Si l'esclau ha respos ACK, continua amb els bytes pendents
                    //
                    if (PLIB_I2C_TransmitterByteWasAcknowledged(id) && 
                        (hTransaction->state != transactionSendFinished)) {

                        switch (hTransaction->state) {
                            case transactionSendLength:
                                hTransaction->check += hTransaction->txCount;
                                PLIB_I2C_TransmitterByteSend(id, hTransaction->txCount);
                                if (hTransaction->txCount > 0)
                                    hTransaction->state = transactionSendData;
                                else
                                    hTransaction->state = transactionSendCheck;
                                break;

                            case transactionSendData: {
                                uint8_t data = hTransaction->txBuffer[hTransaction->index++];
                                hTransaction->check += data;
                                PLIB_I2C_TransmitterByteSend(id, data);
                                if (hTransaction->index == hTransaction->txCount) 
                                    hTransaction->state = transactionSendCheck;
                                break;
                            }

                            case transactionSendCheck:
                                PLIB_I2C_TransmitterByteSend(id, hTransaction->check);
                                hTransaction->state = transactionSendFinished;
                                break;
                        }
                    }
                    
                    // En cas contrari finalitza la transmissio o continua
                    // la amb recepcio de dades desde l'esclau
                    //
                    else {

                        // Si s'ha definit el buffer de recepcio, es posa en modus lectura
                        // i inicia la transaccio de nou per rebre la resposta de l'esclau
                        //
                        if (hTransaction->rxBuffer && hTransaction->rxSize) {
                            PLIB_I2C_MasterStartRepeat(id);
                            hTransaction->writeMode = false;
                            hTransaction->state = transactionSendAddress;
                        }

                        // En cas contrari finalitza
                        //
                        else {
                            PLIB_I2C_MasterStop(id);
                            hTransaction->state = transactionWaitStop;
                        }
                    }
                }
                break;

            case transactionStartReceive:

                // Si l'escau ha respos ACK, llegeix un byte
                //
                if (PLIB_I2C_TransmitterByteWasAcknowledged(id)) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->state = transactionReceiveLength;
                }

                // En cas contrari finalitza la transmissio
                //
                else {
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionReceiveLength: {
                uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                hTransaction->maxIndex = min(hTransaction->rxSize, data);
                hTransaction->check += data;
                PLIB_I2C_ReceivedByteAcknowledge(id, true);
                hTransaction->waitingSlaveACK = true;
                if (hTransaction->maxIndex > 0)
                    hTransaction->state = transactionReceiveData;
                else
                    hTransaction->state = transactionReceiveCheck;
                break;
            }

            case transactionReceiveData:
                if (hTransaction->waitingSlaveACK) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->waitingSlaveACK = false;
                }
                else {
                    uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                    hTransaction->rxBuffer[hTransaction->index++] = data;
                    hTransaction->check += data;
                    PLIB_I2C_ReceivedByteAcknowledge(id, true);
                    hTransaction->waitingSlaveACK = true;
                    if (hTransaction->index == hTransaction->maxIndex)
                        hTransaction->state = transactionReceiveCheck;
                }
                break;

            case transactionReceiveCheck:
                if (hTransaction->waitingSlaveACK) {
                    PLIB_I2C_MasterReceiverClock1Byte(id);
                    hTransaction->waitingSlaveACK = false;
                }
                else  {
                    uint8_t data = PLIB_I2C_ReceivedByteGet(id);
                    if (data != hTransaction->check)
                        hTransaction->error = 1;
                    hTransaction->rxCount = hTransaction->index;
                    PLIB_I2C_MasterStop(id);
                    hTransaction->state = transactionWaitStop;
                }
                break;

            case transactionWaitStop:
                hTransaction->state = transactionFinished;
                eosSemaphoreISRGive(hTransaction->hSemaphore);
                break;
        }
    }
}
