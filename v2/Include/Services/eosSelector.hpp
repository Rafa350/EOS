#ifndef __EOS_SERVICES_SELECTOR_HPP
#define __EOS_SERVICES_SELECTOR_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {
    
    class SelectorService;
    typedef SelectorService *SelectorServiceHandle;
    
    struct SelectorNotification {
        int position;
        unsigned state;
    };
    
    class SelectorService: private IRunable {        
        private:
            typedef ICallbackP1<SelectorNotification&> ISelectorServiceEvent;
            
        private:
            Task task;
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            int position;
            unsigned state;
            ISelectorServiceEvent *evNotify;
            
        public:
            SelectorService(I2CMasterServiceHandle i2cService, uint8_t addr);
            ~SelectorService();
            
            template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(SelectorNotification&)) { 
                
                evNotify = new CallbackP1<cls, SelectorNotification&>(instance, method); 
            }
        private:
            void run();
    };
}


#endif
