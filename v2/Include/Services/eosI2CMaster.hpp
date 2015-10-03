#ifndef __EOS_I2CMASTER_HPP
#define __EOS_I2CMASTER_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosQueue.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class I2CMasterTransaction;
    
    typedef Queue<I2CMasterTransaction*> TransactionQueue;

    class I2CMasterService: IRunable {
        private:
            unsigned moduleId;
            Task task;
            TransactionQueue queue;
            
        public:
            I2CMasterService(unsigned moduleId);
            void startTransaction(I2CMasterTransaction *transaction);
        private:
            void run();
            static void interruptCallback(unsigned moduleId, void *param);
    };

    class I2CMasterTransaction {
        public:
            I2CMasterTransaction(uint8_t addr, uint8_t *txBuffer, unsigned txCount, uint8_t *rxBuffer, unsigned rxSize);
    };

}


#endif

