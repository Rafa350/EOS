#ifndef __EOS_I2CMASTER_HPP
#define __EOS_I2CMASTER_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"
#include "System/eosSemaphore.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
       
    class I2CMasterService: IRunable {
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
                bool inUse;
                uint8_t addr;
                uint8_t *txBuffer;
                uint8_t *rxBuffer;
                unsigned txCount;
                unsigned rxCount;
                unsigned rxSize;
                BinarySemaphore *semaphore;
            };

            typedef Queue<Transaction*> TransactionQueue;

        private:
            unsigned moduleId;
            Task task;
            TransactionQueue queue;
            Transaction *transaction;
            Transaction transactions[10];
            BinarySemaphore semaphore;
            unsigned index;
            unsigned maxIndex;
            uint8_t check;
            uint8_t error;
            bool waitingSlaveACK;   
            bool writeMode;         
            State state;
            
        public:
            I2CMasterService(unsigned moduleId);
            inline bool startTransaction(uint8_t addr, void *txBuffer, unsigned txCount, unsigned timeout) {
                return startTransaction(addr, txBuffer, txCount, nullptr, 0, timeout);
            }
            bool startTransaction(uint8_t addr, void *txBuffer, unsigned txCount, void *rxBuffer, unsigned rxSize, unsigned timeout);
        private:
            static void interruptCallback(unsigned moduleId, void *param);
            void stateMachine();
            void run();
    };
}


#endif

