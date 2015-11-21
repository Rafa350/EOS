#ifndef __EOS_SELECTOR_HPP
#define __EOS_SELECTOR_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosI2CMaster.hpp"
#include "System/eosCallbacks.hpp"


#define EV_SelectorService_onChange(cls, instance, method) \
    new eos::CallbackP2<cls, int16_t, uint8_t>(instance, method)


namespace eos {
    
    class SelectorService;
    typedef SelectorService *SelectorServiceHandle;
    
    typedef ICallbackP2<int16_t, uint8_t> ISelectorServiceEvent;

    class SelectorService: private IRunable {        
        private:
            Task task;
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            int16_t position;
            uint8_t state;
            ISelectorServiceEvent *evChange;
            
        public:
            SelectorService(I2CMasterServiceHandle i2cService, uint8_t addr);
            inline void setChangeEvent(ISelectorServiceEvent *event) { evChange = event; }
        private:
            void run();
    };
}


#endif
