#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosSemaphore.h"
#include "System/Core/eosQueue.h"


using namespace eos;


static const unsigned baudRate = 100000;


static const I2CMasterServiceConfiguration configuration = {
    .serviceConfiguration = {
        .serviceName = "I2CMasterService",
        .stackSize = 512,
        .priority = TaskPriority::normal,
    },
    .module = 0
};


I2CMasterService::TransactionAllocator I2CMasterService::transactionAllocator(20);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: Aplicacio a la que pertany el servei.
/// \param    init: parametres d'inicialitzacio.
///
I2CMasterService::I2CMasterService(
    Application *application,
    const I2CMasterServiceConfiguration &init) :
    
    module(init.module),
    Service(application, init.serviceConfiguration),
    transactionQueue(10) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transaccio.
/// \param    addr: Adressa I2C del desti.
/// \param    txBuffer: Buffer de dades de transmisio.
/// \param    txCount: Numero de bytes en el buffer de transmissio.
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxSize: Tamany del buffer de recepcio.
/// \param    blockTime: Temps maxim de bloqueig.
/// \param    notify: Semafor per notificar el final de la transaccio.
/// \return  True si tot es correcte, false en cas contrari.
///
bool I2CMasterService::startTransaction(
    uint8_t addr,
    void *txBuffer,
    unsigned txCount,
    void *rxBuffer,
    unsigned rxSize,
    unsigned blockTime,
    BinarySemaphore *notify) {
    
    Transaction *transaction = new Transaction();
    if (transaction != nullptr)  {
    
        transaction->addr = addr;
        transaction->txBuffer = (uint8_t*) txBuffer;
        transaction->txCount = txCount;
        transaction->rxBuffer = (uint8_t*) rxBuffer;
        transaction->rxSize = rxSize;
        transaction->rxCount = 0;
        transaction->notify = notify;

        if (transactionQueue.put(transaction, blockTime)) 
            return true;
        
        else {
            delete transaction;
            return false;
        }
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void I2CMasterService::onInitialize() {
    
    I2CMasterInitializeInfo info = {
        .module = module,
        .baudRate = 100000,
        .irqCallback = interruptCallback,
        .irqParam = this
    };
    
    halI2CMasterInitialize(&info);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void I2CMasterService::onTask() {
          
    if (transactionQueue.get(transaction, (unsigned) -1)) {

        // Espera a que el bus estigui lliure
        //
        while (!halI2CIsBusIdle(module)) 
            Task::delay(20);

        // Inicialitza la transaccio
        //
        writeMode = transaction->txBuffer && transaction->txCount;
        state = State::sendAddress;

        // Inicia la comunicacio. A partir d'aquest punt es
        // generen les interrupcions del modul I2C
        //
        halI2CMasterStart(module);

        // Espera que finalitzi la transaccio
        //
        if (semaphore.wait(eosI2CMasterService_TransactionTimeout)) {
        }
        else {
        }

        // Retart entre transaccions
        //
        Task::delay(eosI2CMasterService_EndTransactionDelay);

        // Notifica el final de la transaccio
        //
        if (transaction->notify != nullptr)
            transaction->notify->give();

        // Destrueix la transaccio
        //
        delete transaction;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els events de la comunicacio I2C. S'executa en el
///           contexte de la interrupcio I2C.
/// \param    module: Identificador del module I2C
/// \param    param: Parametre. En aquest cas el servei.
///
void I2CMasterService::interruptCallback(
    I2CModule module, 
    void* param) {

    I2CMasterService *service = static_cast<I2CMasterService*>(param);
    service->stateMachine();
}


/// ----------------------------------------------------------------------
/// \brief Maquina d'estats per procesar les comunicacions. S'executa en
///        el contexte de la interrupcio I2C.
///
/// Transmissio/Recepcio en format de trama
/// |LENGTH|DATA-1|DATA-2| . . . |DATA-n|CHECK|
///
void I2CMasterService::stateMachine() {
    
    switch (state) {

        case State::sendAddress:

            // Si hi ha colissio, reinicia la transmissio
            //
            if (halI2CArbitrationLossHasOccurred(module)) {
                halI2CArbitrationLossClear(module);
                while (!halI2CIsBusIdle(module))
                    continue;
                halI2CMasterStart(module);
            }

            else {

                // Envia l'adressa del esclau
                //
                halI2CTransmitterByteSend(module, transaction->addr | (writeMode ? 0 : 1));

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
            if (halI2CArbitrationLossHasOccurred(module)) {
                halI2CArbitrationLossClear(module);
                while (!halI2CIsBusIdle(module))
                    continue;
                halI2CMasterStart(module);
                state = State::sendAddress;
            }

            else {

                // Si l'esclau ha respos ACK, continua amb els bytes pendents
                //
                if (halI2CTransmitterByteWasAcknowledged(module) && 
                    (state != State::sendFinished)) {

                    switch (state) {
                        case State::sendLength:
                            check += transaction->txCount;
                            halI2CTransmitterByteSend(module, transaction->txCount);
                            if (transaction->txCount > 0)
                                state = State::sendData;
                            else
                                state = State::sendCheck;
                            break;

                        case State::sendData: {
                            uint8_t data = transaction->txBuffer[index++];
                            check += data;
                            halI2CTransmitterByteSend(module, data);
                            if (index == transaction->txCount) 
                                state = State::sendCheck;
                            break;
                        }

                        case State::sendCheck:
                            halI2CTransmitterByteSend(module, check);
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
                        halI2CMasterStartRepeat(module);
                        writeMode = false;
                        state = State::sendAddress;
                    }

                    // En cas contrari finalitza
                    //
                    else {
                        halI2CMasterStop(module);
                        state = State::waitStop;
                    }
                }
            }
            break;

        case State::startReceive:

            // Si l'escau ha respos ACK, llegeix un byte
            //
            if (halI2CTransmitterByteWasAcknowledged(module)) {
                halI2CMasterReceiverClock1Byte(module);
                state = State::receiveLength;
            }

            // En cas contrari finalitza la transmissio
            //
            else {
                halI2CMasterStop(module);
                state = State::waitStop;
            }
            break;

        case State::receiveLength: {
            uint8_t data = halI2CReceivedByteGet(module);
            maxIndex = Math::min(transaction->rxSize, (unsigned) data);
            check += data;
            halI2CReceivedByteAcknowledge(module, true);
            waitingSlaveACK = true;
            if (maxIndex > 0)
                state = State::receiveData;
            else
                state = State::receiveCheck;
            break;
        }

        case State::receiveData:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(module);
                waitingSlaveACK = false;
            }
            else {
                uint8_t data = halI2CReceivedByteGet(module);
                transaction->rxBuffer[index++] = data;
                check += data;
                halI2CReceivedByteAcknowledge(module, true);
                waitingSlaveACK = true;
                if (index == maxIndex)
                    state = State::receiveCheck;
            }
            break;

        case State::receiveCheck:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(module);
                waitingSlaveACK = false;
            }
            else  {
                uint8_t data = halI2CReceivedByteGet(module);
                if (data != check)
                    error = 1;
                transaction->rxCount = index;
                halI2CMasterStop(module);
                state = State::waitStop;
            }
            break;

        case State::waitStop:
            state = State::finished;
            semaphore.releaseISR();
            break;
    }
}
