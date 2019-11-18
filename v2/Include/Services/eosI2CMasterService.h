#ifndef __eosI2CMasterService__
#define __eosI2CMasterService__


#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosSemaphore.h"


// Numero maxim de transaccions en la cua
#ifndef eosI2CMasterService_TransactionQueueSize
#define eosI2CMasterService_TransactionQueueSize 10
#endif

// Modul de comunicacio I2C a gestionar 
#ifndef eosI2CMasterService_I2CModule
#define eosI2CMasterService_I2CModule HAL_I2C_I2C2
#endif

// Velocitat de comunicacio I2C
#ifndef eosI2CMasterService_I2CBaudRate
#define eosI2CMasterService_I2CBaudRate 100000
#endif


namespace eos {
    
    class Application;
    class I2CMasterTransaction;
          
    class I2CMasterService: public Service {
        public:
            struct Configuration {
                I2CModule module;
                int baudRate;
            };
        
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
            int baudRate;
            TransactionQueue transactionQueue;
            I2CMasterTransaction *transaction;
            BinarySemaphore semaphore;
            int index;
            int maxIndex;
            uint8_t check;
            uint8_t error;
            bool waitingSlaveACK;   
            bool writeMode;         
            State state;

        public:
            I2CMasterService(Application *application, const Configuration *cfg);            
            bool startTransaction(I2CMasterTransaction *transaction, int blockTime);
                           
        protected:
            void onInitialize() override;
            void onTask() override;     
    
        private:
            static void interruptCallback(I2CModule module, void *param);
            void stateMachine();   
    };
    
    
    class I2CMasterTransaction {
        public:
            enum class Protocol {        // Protocol de comunicacio
                raw,                     // -Modus I2C estandard
                packed                   // -Modus empaquetat (Longitut y verificacio))
            };
            enum class Result {
                ok,
                error
            };
            struct EventArgs {
                I2CMasterTransaction* transaction;
                Result result;
            };
        
        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;
            
        protected:
            uint8_t addr;
            uint8_t *txBuffer;
            uint8_t *rxBuffer;
            int txCount;
            int rxCount;
            int rxSize;
            Protocol protocol;
            IEventCallback *callback;

        public:
            I2CMasterTransaction(uint8_t addr, Protocol protocol, uint8_t *txBuffer, int txCount, IEventCallback *callback);
            I2CMasterTransaction(uint8_t addr, Protocol protocol, uint8_t *txBuffer, int txCount, uint8_t *rxBuffer, int rxSize, IEventCallback *callback);
            
            void *operator new(size_t size);
            void operator delete(void *p);
            
        friend I2CMasterService;
    };
}


#endif // __eosI2CMasterService__

