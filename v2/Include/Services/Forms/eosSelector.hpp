#ifndef __EOS_SELECTOR_HPP
#define __EOS_SELECTOR_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {

    class SelectorService: public IRunable {        
        private:
            Task task;
            uint8_t addr;
            I2CMasterService *i2cService;
            uint16_t position;
            uint8_t state;
            
        public:
            SelectorService(I2CMasterService *i2cService, uint8_t addr);
        private:
            void run();
    };
}


#endif
