#ifndef __EOS_SELECTOR_HPP
#define __EOS_SELECTOR_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosI2CMaster.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class SelectorService;
    typedef SelectorService *SelectorServiceHandle;
    
    class SelectorService: private IRunable {        
        private:
            typedef ICallbackP2<int16_t, uint8_t> ISelectorServiceEvent;
            
        private:
            Task task;
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            int16_t position;
            uint8_t state;
            ISelectorServiceEvent *evChange;
            
        public:
            SelectorService(I2CMasterServiceHandle i2cService, uint8_t addr);
            ~SelectorService();
            
            template <class cls>
            void setChangeEvent(cls *instance, void (cls::*method)(int16_t position, uint8_t state)) { 
                
                evChange = new CallbackP2<cls, int16_t, uint8_t>(instance, method); 
            }
        private:
            void run();
    };
}


#endif
