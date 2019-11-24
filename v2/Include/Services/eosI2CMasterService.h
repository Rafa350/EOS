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
          
    /// \brief Clase que gestiona el servei de comunicacions I2C
    ///
    class I2CMasterService: public Service {      
        public:
            struct Configuration {
                I2CModule module;
                int baudRate;
            };
            
            /// \brief Protocol a utilitzar en la transaccio.
            ///
            enum class TransactionProtocol {
                raw,
                packet
            };

            /// \brief Resultat de la transaccio.
            ///
            enum class TransactionResult {
                ok,
                error
            };

            /// \brief Parametres del event.
            ///
            struct TransactionEventArgs {
                void *txBuffer;
                int txCount;
                void *rxBuffer;
                int rxCount;
                TransactionResult result;
            };

        private:
            /// \brief Estats de la maquina d'estats que procesa la transaccio
            enum class State {          
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
            
            typedef ICallbackP1<const TransactionEventArgs&> ITransactionEventCallback;

            /// \brief Estructura per gestionar les transaccions.
            ///
            struct Transaction {
                uint8_t addr;
                const uint8_t *txBuffer;
                uint8_t *rxBuffer;
                int txCount;
                int rxCount;
                int rxSize;
                TransactionProtocol protocol;
                ITransactionEventCallback *callback;
            };
            
            typedef PoolAllocator<Transaction, 20> TransactionAllocator;
            typedef Queue<Transaction*> TransactionQueue;

        private:
            I2CModule module;
            TransactionAllocator transactionAllocator;
            TransactionQueue transactionQueue;
            Transaction *transaction;
            BinarySemaphore semaphore;
            int index;
            int maxIndex;
            uint8_t check;
            uint8_t error;
            bool waitingSlaveACK;   
            bool writeMode;         
            State state;

        public:
            I2CMasterService(Application *application, const Configuration &cfg);        
            ~I2CMasterService();
            
            bool startTransaction(uint8_t addr, TransactionProtocol protocol, void const *txBuffer, int txCount, ITransactionEventCallback *callback);
            bool startTransaction(uint8_t addr, TransactionProtocol protocol, void const *txBuffer, int txCount, void *rxBuffer, int rxSize, ITransactionEventCallback *callback);
                           
        protected:
            void onInitialize() override;
            void onTask() override;     
    
        private:
            void initializeHardware(const Configuration &cfg);
            void deinitializeHardware();
            static void interruptCallback(I2CModule module, void *param);
            void stateMachine();   
    };
    
}


#endif // __eosI2CMasterService__

