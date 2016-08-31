#ifndef __EOS_SERVICES_SELECTOR_HPP
#define __EOS_SERVICES_SELECTOR_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {
    
    class SelectorService;
    typedef SelectorService *SelectorServiceHandle;
    
    typedef int16_t SelectorPosition;
    typedef uint8_t SelectorState;
    
    class SelectorService: private IRunable {        
        private:
            typedef ICallbackP2<SelectorPosition, SelectorState> ISelectorServiceEvent;
            
        private:
            Task task;
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            SelectorPosition position;
            SelectorState state;
            ISelectorServiceEvent *evNotify;
            
        public:
            SelectorService(I2CMasterServiceHandle i2cService, uint8_t addr);
            ~SelectorService();
            
            template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(SelectorPosition, SelectorState)) { 
                
                evNotify = new CallbackP2<cls, SelectorPosition, SelectorState>(instance, method); 
            }
        private:
            void run();
    };
}


#endif
