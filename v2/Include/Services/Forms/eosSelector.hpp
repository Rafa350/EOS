#ifndef __EOS_SELECTOR_HPP
#define __EOS_SELECTOR_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosI2CMaster.hpp"
#include "System/eosCallbacks.hpp"


#define EV_SelectorService_onChange(cls, instance, method) \
    new eos::CallbackP2<cls, uint16_t, uint8_t>(instance, method)


namespace eos {
    
    class SelectorService;
    typedef ICallbackP2<uint16_t, uint8_t> ISelectorServiceEvent;

    class SelectorService: public IRunable {        
        private:
            Task task;
            uint8_t addr;
            I2CMasterService *i2cService;
            uint16_t position;
            uint8_t state;
            ISelectorServiceEvent *onChange;
            
        public:
            SelectorService(I2CMasterService *i2cService, uint8_t addr);
            inline void setOnChange(ISelectorServiceEvent *event) { onChange = event; }
        private:
            void run();
    };
}


#endif
