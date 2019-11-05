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
    
    enum class I2CProtocolType {        // Protocol de comunicacio
        Raw,                            // -Modus I2C estandard
        Packed                          // -Modus empaquetat (Longitut y verificacio))
    };
    
    struct I2CMasterServiceConfiguration {
        ServiceConfiguration serviceConfiguration;
        I2CModule module;
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
            
            struct Transaction {
                uint8_t addr;
                uint8_t *txBuffer;
                uint8_t *rxBuffer;
                unsigned txCount;
                unsigned rxCount;
                unsigned rxSize;
                I2CProtocolType protocolType;
                //BinarySemaphore *notify;
                
                inline void *operator new (size_t size) { return transactionAllocator.allocate(size); }
                inline void operator delete(void *p) { transactionAllocator.deallocate(static_cast<Transaction*>(p)); }
            };

            typedef Queue<Transaction*> TransactionQueue;
            typedef PoolAllocator<Transaction> TransactionAllocator;

        private:
            static TransactionAllocator transactionAllocator;
            I2CModule module;
            TransactionQueue transactionQueue;
            Transaction *transaction;
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
            
            inline bool startTransaction(uint8_t addr, void *txBuffer, unsigned txCount, 
                                         unsigned blockTime, BinarySemaphore *notify) {
                return startTransaction(addr, txBuffer, txCount, nullptr, 0, blockTime, notify);
            }
            bool startTransaction(uint8_t addr, void *txBuffer, unsigned txCount, 
                                  void *rxBuffer, unsigned rxSize, 
                                  unsigned blockTime, BinarySemaphore *notify);
    };
}


#endif // __eosI2CMasterService__

