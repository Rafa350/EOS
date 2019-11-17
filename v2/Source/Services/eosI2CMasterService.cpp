#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosSemaphore.h"
#include "System/Core/eosQueue.h"


using namespace eos;


static const unsigned baudRate = 100000;


static PoolAllocator<I2CMasterTransaction> transactionAllocator(eosI2CMasterService_TransactionQueueSize);


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte. 
///
I2CMasterService::Configuration::Configuration():

    module(eosI2CMasterService_I2CModule),
    baudRate(eosI2CMasterService_I2CBaudRate) { 
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del servei.
/// \param    application: Aplicacio a la que pertany el servei.
/// \param    cfg: Parametres de configuracio.
///
I2CMasterService::I2CMasterService(
    Application *application,
    const Configuration *cfg) :
    
    Service(application),
    transactionQueue(eosI2CMasterService_TransactionQueueSize) {

    if (cfg != nullptr)
        this->cfg = *cfg;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transaccio.
/// \param    transaction: La transaccio.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si la transaccio s'ha afeigit a la cua, false en cas contrari.
/// \remarks  Un cop la transaccio es a la cua, el servei pren posessio
///           de la transaccio, i es responsabilitat seva la destruccio.
///
bool I2CMasterService::startTransaction(
    I2CMasterTransaction *transaction,
    int blockTime) {
    
    return transactionQueue.put(transaction, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void I2CMasterService::onInitialize() {
    
    I2CMasterInitializeInfo info = {
        .module = cfg.module,
        .baudRate = cfg.baudRate,
        .irqCallback = interruptCallback,
        .irqParam = this
    };
    
    halI2CMasterInitialize(&info);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void I2CMasterService::onTask() {
          
    if (transactionQueue.get(transaction, -1)) {

        // Espera a que el bus estigui lliure
        //
        while (!halI2CIsBusIdle(cfg.module)) 
            Task::delay(20);

        // Inicialitza la transaccio
        //
        writeMode = transaction->txBuffer && transaction->txCount;
        state = State::sendAddress;

        // Inicia la comunicacio. A partir d'aquest punt es
        // generen les interrupcions del modul I2C
        //
        halI2CMasterStart(cfg.module);

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
            I2CMasterTransaction::EventArgs args;
            args.transaction = transaction;
            args.result = I2CMasterTransaction::Result::ok;
            transaction->callback->execute(args);
        }

        // Destrueix la transaccio
        //
        delete transaction;
        
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
            if (halI2CArbitrationLossHasOccurred(cfg.module)) {
                halI2CArbitrationLossClear(cfg.module);
                while (!halI2CIsBusIdle(cfg.module))
                    continue;
                halI2CMasterStart(cfg.module);
            }

            else {

                // Envia l'adressa del esclau
                //
                halI2CTransmitterByteSend(cfg.module, transaction->addr | (writeMode ? 0 : 1));

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
            if (halI2CArbitrationLossHasOccurred(cfg.module)) {
                halI2CArbitrationLossClear(cfg.module);
                while (!halI2CIsBusIdle(cfg.module))
                    continue;
                halI2CMasterStart(cfg.module);
                state = State::sendAddress;
            }

            else {

                // Si l'esclau ha respos ACK, continua amb els bytes pendents
                //
                if (halI2CTransmitterByteWasAcknowledged(cfg.module) && 
                    (state != State::sendFinished)) {

                    switch (state) {
                        case State::sendLength:
                            check += transaction->txCount;
                            halI2CTransmitterByteSend(cfg.module, transaction->txCount);
                            if (transaction->txCount > 0)
                                state = State::sendData;
                            else
                                state = State::sendCheck;
                            break;

                        case State::sendData: {
                            uint8_t data = transaction->txBuffer[index++];
                            check += data;
                            halI2CTransmitterByteSend(cfg.module, data);
                            if (index == transaction->txCount) 
                                state = State::sendCheck;
                            break;
                        }

                        case State::sendCheck:
                            halI2CTransmitterByteSend(cfg.module, check);
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
                        halI2CMasterStartRepeat(cfg.module);
                        writeMode = false;
                        state = State::sendAddress;
                    }

                    // En cas contrari finalitza
                    //
                    else {
                        halI2CMasterStop(cfg.module);
                        state = State::waitStop;
                    }
                }
            }
            break;

        case State::startReceive:

            // Si l'esclau ha respos ACK, llegeix un byte
            //
            if (halI2CTransmitterByteWasAcknowledged(cfg.module)) {
                halI2CMasterReceiverClock1Byte(cfg.module);
                state = State::receiveLength;
            }

            // En cas contrari finalitza la transmissio
            //
            else {
                halI2CMasterStop(cfg.module);
                state = State::waitStop;
            }
            break;

        case State::receiveLength: {
            uint8_t data = halI2CReceivedByteGet(cfg.module);
            maxIndex = Math::min(transaction->rxSize, (int) data);
            check += data;
            halI2CReceivedByteAcknowledge(cfg.module, true);
            waitingSlaveACK = true;
            if (maxIndex > 0)
                state = State::receiveData;
            else
                state = State::receiveCheck;
            break;
        }

        case State::receiveData:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(cfg.module);
                waitingSlaveACK = false;
            }
            else {
                uint8_t data = halI2CReceivedByteGet(cfg.module);
                transaction->rxBuffer[index++] = data;
                check += data;
                halI2CReceivedByteAcknowledge(cfg.module, true);
                waitingSlaveACK = true;
                if (index == maxIndex)
                    state = State::receiveCheck;
            }
            break;

        case State::receiveCheck:
            if (waitingSlaveACK) {
                halI2CMasterReceiverClock1Byte(cfg.module);
                waitingSlaveACK = false;
            }
            else  {
                uint8_t data = halI2CReceivedByteGet(cfg.module);
                if (data != check)
                    error = 1;
                transaction->rxCount = index;
                halI2CMasterStop(cfg.module);
                state = State::waitStop;
            }
            break;

        case State::waitStop:
            state = State::finished;
            semaphore.releaseISR();
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    addr: Adressa I2C de 8 bits.
/// \param    protocol: Protocol de comunicacio.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txCount: Numero de bytes en el buffer de transmissio
/// \param    callback: Callback per notificacions.
///
I2CMasterTransaction::I2CMasterTransaction(
    uint8_t addr, 
    Protocol protocol, 
    uint8_t *txBuffer, 
    int txCount, 
    IEventCallback* callback):

    addr(addr),
    txBuffer(txBuffer),
    txCount(txCount),
    rxBuffer(nullptr),
    rxCount(0),
    rxSize(0),
    callback(callback) {    
}


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    addr: Adressa I2C de 8 bits.
/// \param    protocol: Protocol de comunicacio.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txCount: Numero de bytes en el buffer de transmissio
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxSize: Tamany del buffer de recepcio.
/// \param    callback: Callback per notificacions.
///
I2CMasterTransaction::I2CMasterTransaction(
    uint8_t addr, 
    Protocol protocol, 
    uint8_t *txBuffer, 
    int txCount, 
    uint8_t *rxBuffer,
    int rxSize,
    IEventCallback* callback):

    addr(addr),
    txBuffer(txBuffer),
    txCount(txCount),
    rxBuffer(rxBuffer),
    rxCount(0),
    rxSize(rxSize),
    callback(callback) {    
}


/// ----------------------------------------------------------------------
/// \brief   Operador new.
///
void *I2CMasterTransaction::operator new (
    size_t size) {
    
    return transactionAllocator.allocate(size);
}


/// ----------------------------------------------------------------------
/// \brief   Operador delete.
///
void I2CMasterTransaction::operator delete(
    void *p) {
    
    transactionAllocator.deallocate(static_cast<I2CMasterTransaction*>(p));
}
