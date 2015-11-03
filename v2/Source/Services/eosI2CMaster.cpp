#include "Services/eosI2CMaster.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"
#include "System/eosSemaphore.hpp"
#include "HAL/halI2C.h"


#define min(a, b)    (a) < (b) ? a : b


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;
const unsigned queueMaxItems = 20;
const unsigned baudRate = 100000;


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           I2CMasterService::I2CMasterService(
 *              unsigned moduleId)
 *
 *       Entrada:
 *           moduleId: Identificador del modulI2C
 *
 *************************************************************************/

I2CMasterService::I2CMasterService(
    unsigned moduleId) :
    task(taskStackSize, taskPriority, this),
    queue(queueMaxItems) {

    this->moduleId = moduleId; 
    
    for (unsigned i = 0; i < sizeof(transactions) / sizeof(transactions[0]); i++)
        transactions[i].inUse = false;
}


/*************************************************************************
 *
 *       Inicia una transaccio
 *
 *       Funcio:
 *           bool I2CMasterService::startTransaction(
 *               uint8_t addr,
 *               void *txBuffer,
 *               unsigned txCount,
 *               void *rxBuffer,
 *               unsigned rxSize,
 *               unsignjed blockTime,
 *               BinarySemaphore *notify) 
 *
 *       Entrada:
 *           addr     : Adressa I2C del desti
 *           txBuffer : Buffer de dades de transmisio
 *           txCount  : Numero de bytes en el buffer de transmissio
 *           rxBuffer : Buffer de recepcio
 *           rxSize   : Tamany del buffer de recepcio
 *           blockTime: Temps maxim de bloqueig
 *           notify   : Semafor per notificar el final de la transaccio
 * 
 *       Retorn:
 *           True si tot es correcte, false en cas contrari
 *
 *************************************************************************/

bool I2CMasterService::startTransaction(
    uint8_t addr,
    void *txBuffer,
    unsigned txCount,
    void *rxBuffer,
    unsigned rxSize,
    unsigned blockTime,
    BinarySemaphore *notify) {
    
    for (unsigned i = 0; i < sizeof(transactions) / sizeof(transactions[0]); i++) {
        Transaction *transaction = &transactions[i];
        if (!transaction->inUse) {
            transaction->inUse = true;
            transaction->addr = addr;
            transaction->txBuffer = (uint8_t*) txBuffer;
            transaction->txCount = txCount;
            transaction->rxBuffer = (uint8_t*) rxBuffer;
            transaction->rxSize = rxSize;
            transaction->rxCount = 0;
            transaction->notify = notify;
            queue.put(transaction, blockTime);
            return true;
        }
    }
    
    return false;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void I2CMasterService::run()
 *
 *************************************************************************/

void I2CMasterService::run() {

    halI2CMasterInitialize(
        moduleId, 
        baudRate, 
        interruptCallback, 
        (I2CInterruptParam) this);

    while (true) {
           
        while (queue.get(transaction, 0xFFFFFFFF)) {
        
            // Espera a que el bus estigui lliure
            //
            while (!halI2CIsBusIdle(moduleId)) 
                Task::delay(20);

            // Inicialitza la transaccio
            //
            writeMode = transaction->txBuffer && transaction->txCount;
            state = State::sendAddress;

            // Inicia la comunicacio. A partir d'aquest punt es
            // generen les interrupcions del modul I2C
            //
            halI2CMasterStart(moduleId);

            // Espera que finalitzi la transaccio
            //
            if (semaphore.take(eosI2CMasterService_TransactionTimeout)) {
            }
            else {
            }

            // Retart entre transaccions
            //
            Task::delay(eosI2CMasterService_EndTransactionDelay);
            
            // Finalitza el us de la transaccio
            //
            if (transaction->notify != nullptr)
                transaction->notify->give();
            transaction->inUse = false;
        }
    }
}


/*************************************************************************
 *
 *       Procesa els events de la comunicacio I2C
 *
 *       Funcio:
 *           void I2CMasterService::interruptCallback(
 *              unsigned moduleId, 
 *              void* param)
 *
 *       Entrada:
 *           moduleId: Identificador del module I2C
 *           param   : Parametre. En aquest cas el servei
 *
 *       Notes:
 *           Transmissio/Recepcio en format de trama
 *           |LENGTH|DATA-1|DATA-2| . . . |DATA-n|CHECK|
 *
 *************************************************************************/

void I2CMasterService::interruptCallback(
    unsigned moduleId, 
    void* param) {

    I2CMasterService *service = (I2CMasterService*) param;
    service->stateMachine();
}


/*************************************************************************
 *
 *       Maquina d'estats per porocesar les comunicacions
 * 
 *       Funcio::
 *           void I2CMasterService::stateMachine() 
 *
 *************************************************************************/

void I2CMasterService::stateMachine() {
    
    switch (state) {

        case State::sendAddress:

            // Si hi ha colissio, reinicia la transmissio
            //
            if (halI2CArbitrationLossHasOccurred(moduleId)) {
                halI2CArbitrationLossClear(moduleId);
                while (!halI2CIsBusIdle(moduleId))
                    continue;
                halI2CMasterStart(moduleId);
            }

            else {

                // Envia l'adressa del esclau
                //
                halI2CTransmitterByteSend(moduleId, transaction->addr | (writeMode ? 0 : 1));

                index = 0;
                check = transaction->addr;

                if (writeMode)
                    state = State::sendLength;
                else
                    state = State::startReceive;
            }
            break;

        case State::sendLength:
        case State::sendData:
        case State::sendCheck:
        case State::sendFinished:

            // Si hi ha colissio, reinicia la transmissio
            //
            if (halI2CArbitrationLossHasOccurred(moduleId)) {
                halI2CArbitrationLossClear(moduleId);
                while (!halI2CIsBusIdle(moduleId))
                    continue;
                halI2CMasterStart(moduleId);
                state = State::sendAddress;
            }

            else {

                // Si l'esclau ha respos ACK, continua amb els bytes pendents
                //
                if (halI2CTransmitterByteWasAcknowledged(moduleId) && 
                    (state != State::sendFinished)) {

                    switch (state) {
                        case State::sendLength:
                            check += transaction->txCount;
                            halI2CTransmitterByteSend(moduleId, transaction->txCount);
                            if (transaction->txCount > 0)
                                state = State::sendData;
                            else
                                state = State::sendCheck;
                            break;

                        case State::sendData: {
                            uint8_t data = transaction->txBuffer[index++];
                            check += data;
                            halI2CTransmitterByteSend(moduleId, data);
                            if (index == transaction->txCount) 
                                state = State::sendCheck;
                            break;
                        }

                        case State::sendCheck:
                            halI2CTransmitterByteSend(moduleId, check);
                            state = State::sendFinished;
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
                    if (transaction->rxBuffer && transaction->rxSize) {
                        halI2CMasterStartRepeat(moduleId);
                        writeMode = false;
                        state = State::sendAddress;
                    }

                    // En cas contrari finalitza
                    //
                    else {
                        halI2CMasterStop(moduleId);
                        state = State::waitStop;
                    }
                }
            }
            break;

        case State::startReceive:

            // Si l'escau ha respos ACK, llegeix un byte
            //
            if (halI2CTransmitterByteWasAcknowledged(moduleId)) {
                halI2CMasterReceiverClock1Byte(moduleId);
                state = State::receiveLength;
            }

            // En cas contrari finalitza la transmissio
            //
            else {
                halI2CMasterStop(moduleId);
                state = State::waitStop;
            }
            break;

        case State::receiveLength: {
            uint8_t data = halI2CReceivedByteGet(moduleId);
            maxIndex = min(transaction->rxSize, data);
            check += data;
            halI2CReceivedByteAcknowledge(moduleId, true);
            waitingSlaveACK = true;
            if (maxIndex > 0)
                state = State::receiveData;
            else
                state = State::receiveCheck;
            break;
        }

        case State::receiveData:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(moduleId);
                waitingSlaveACK = false;
            }
            else {
                uint8_t data = halI2CReceivedByteGet(moduleId);
                transaction->rxBuffer[index++] = data;
                check += data;
                halI2CReceivedByteAcknowledge(moduleId, true);
                waitingSlaveACK = true;
                if (index == maxIndex)
                    state = State::receiveCheck;
            }
            break;

        case State::receiveCheck:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(moduleId);
                waitingSlaveACK = false;
            }
            else  {
                uint8_t data = halI2CReceivedByteGet(moduleId);
                if (data != check)
                    error = 1;
                transaction->rxCount = index;
                halI2CMasterStop(moduleId);
                state = State::waitStop;
            }
            break;

        case State::waitStop:
            state = State::finished;
            semaphore.giveISR();
            break;
    }
}
