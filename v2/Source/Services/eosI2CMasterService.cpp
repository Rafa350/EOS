#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosSemaphore.h"
#include "System/Core/eosQueue.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    application: Aplicacio a la que pertany el servei.
/// \param    cfg: Parametres de configuracio.
///
I2CMasterService::I2CMasterService(
    Application *application,
    const Configuration &cfg):
    
    Service(application),
    module(cfg.module),
    transactionQueue(eosI2CMasterService_TransactionQueueSize) {

    initializeHardware(cfg);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor del objecte.
///
I2CMasterService::~I2CMasterService() {

    deinitializeHardware();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el hardware.
/// \param    cfg: Parametres de configuracio.
///
void I2CMasterService::initializeHardware(
    const Configuration& cfg) {
    
    I2CMasterInitializeInfo info = {
        .module = module,
        .baudRate = cfg.baudRate,
        .irqCallback = interruptCallback,
        .irqParam = this
    };
    
    halI2CMasterInitialize(&info);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el hardware.
///
void I2CMasterService::deinitializeHardware() {
    
    halI2CMasterDeinitialize(module);
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transaccio.
/// \param    addr: Adressa I2C.
/// \param    protocol: Protocol de comunicacio.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txCount: Numero de bytes en el buffer de transmissio
/// \param    callback: Callback per notificacions.
/// \return   True si tot es correcte. False si no s'ha pogut iniciar 
///           la transaccio.
///
bool I2CMasterService::startTransaction(
    uint8_t addr, 
    TransactionProtocol protocol, 
    const void *txBuffer, 
    int txCount, 
    ITransactionEventCallback *callback) {
    
    Transaction *transaction = transactionAllocator.allocate();
    if (transaction != nullptr) {
        transaction->addr = addr;
        transaction->protocol = protocol;
        transaction->txBuffer = static_cast<const uint8_t*>(txBuffer);
        transaction->txCount = txCount;
        transaction->callback = callback;
        return transactionQueue.put(transaction, 1000);
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transaccio.
/// \param    addr: Adressa I2C de 8 bits.
/// \param    protocol: Protocol de comunicacio.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txCount: Numero de bytes en el buffer de transmissio
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxSize: Tamany del buffer de recepcio.
/// \param    callback: Callback per notificacions.
/// \return   True si tot es correcte. False si no s'ha pogut
///           iniciar la transaccio.
///
bool I2CMasterService::startTransaction(
    uint8_t addr, 
    TransactionProtocol protocol, 
    const void *txBuffer, 
    int txCount, 
    void *rxBuffer, 
    int rxSize, 
    ITransactionEventCallback *callback) {
    
    Transaction *transaction = transactionAllocator.allocate();
    if (transaction != nullptr) {
        transaction->addr = addr;
        transaction->protocol = protocol;
        transaction->txBuffer = (uint8_t*)txBuffer;
        transaction->txCount = txCount;
        transaction->rxBuffer = (uint8_t*)rxBuffer;
        transaction->rxSize = rxSize;
        transaction->callback = callback;
        return transactionQueue.put(transaction, 1000);
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void I2CMasterService::onInitialize() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void I2CMasterService::onTask() {
          
    // Espara indefinidament que hagi una transaccio e la cua
    //
    if (transactionQueue.get(transaction, -1)) {

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
        if (transaction->callback != nullptr) {
            I2CMasterService::TransactionEventArgs args;
            args.txBuffer = (void*) transaction->txBuffer;
            args.txCount = transaction->txCount;
            args.rxBuffer = (void*) transaction->rxBuffer;
            args.rxCount = transaction->rxCount;
            args.result = I2CMasterService::TransactionResult::ok;
            transaction->callback->execute(args);
        }

        // Destrueix la transaccio
        //
        transactionAllocator.deallocate(transaction);
        
        Task::delay(25); // Provisional
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
/// \brief    Maquina d'estats per procesar les comunicacions. S'executa en
///           el contexte de la interrupcio I2C.
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

            // Si l'esclau ha respos ACK, llegeix un byte
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
            maxIndex = Math::min(transaction->rxSize, (int) data);
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
