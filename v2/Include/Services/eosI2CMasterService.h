#ifndef __eosI2CMasterService__
#define __eosI2CMasterService__


#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosSemaphore.h"


namespace eos {
    
    class Application;
    class I2CMasterTransaction;
    
    enum class I2CProtocolType {        // Protocol de comunicacio
        Raw,                            // -Modus I2C estandard
        Packed                          // -Modus empaquetat (Longitut y verificacio))
    };
    
    struct I2CMasterServiceConfiguration {
        ServiceConfiguration serviceConfiguration;
        I2CModule module;
    };
    
    struct I2CMasterTransactionConfiguration {
        uint8_t addr;
        uint8_t *txBuffer;
        int txCount;
        uint8_t *rxBuffer;
        int rxSize;
        I2CProtocolType protocol;
    };
          
    struct I2CMasterTransactionEventArgs {
        I2CMasterTransaction* transaction;
    };
    
    class I2CMasterService: public Service {
        private:
            enum class State {          // Estat de la transaccio
                idle,                   // -En espera de iniciar
                sendAddress,            // -Transmeteix l'adressa
                sendLength,             // -Transmeteix el byte de longitut
                sendData,               // -Transmeteix un byte de dades
                sendCheck,              // -Transmeteix el byte de verificacio
                sendFinished,           // -Ha finalitzat la transmissio
                startReceive,           // -Inicia la recepcio de dades
                receiveLength,          // -Rebent un byte de longitut
                receiveData,            // -Rebent un byte de dades
                receiveCheck,           // -Rebent un byte de verificacio
                ack,                    // -ACK transmitit
                nak,                    // -NAK transmitit
                waitStop,               // -Esperant STOP
                finished                // -Finalitzada
            };        
            
            typedef Queue<I2CMasterTransaction*> TransactionQueue;

        private:
            I2CModule module;
            TransactionQueue transactionQueue;
            I2CMasterTransaction *transaction;
            BinarySemaphore semaphore;
            unsigned index;
            unsigned maxIndex;
            uint8_t check;
            uint8_t error;
            bool waitingSlaveACK;   
            bool writeMode;         
            State state;
            
        private:
            static void interruptCallback(I2CModule module, void *param);
            void stateMachine();
            
        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            I2CMasterService(Application *application, const I2CMasterServiceConfiguration &init);
            bool startTransaction(I2CMasterTransaction *transaction, int blockTime);
    };
    
    class I2CMasterTransaction {
        private:
            typedef ICallbackP1<const I2CMasterTransactionEventArgs&> II2CMasterTransactionEventCallback;
            
        protected:
            uint8_t addr;
            uint8_t *txBuffer;
            uint8_t *rxBuffer;
            int txCount;
            int rxCount;
            int rxSize;
            I2CProtocolType protocolType;
            II2CMasterTransactionEventCallback *callback;

        public:
            I2CMasterTransaction(const I2CMasterTransactionConfiguration &init, II2CMasterTransactionEventCallback *callback);
            
            void *operator new(size_t size);
            void operator delete(void *p);

            
        friend I2CMasterService;
    };
}


#endif // __eosI2CMasterService__

