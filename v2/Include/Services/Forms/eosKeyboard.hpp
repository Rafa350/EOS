#ifndef __EOS_KEYBOARD_HPP
#define __EOS_KEYBOARD_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif

#ifndef __EOS_TASK_HPP
#include "System/Core/eosTask.hpp"
#endif

#ifndef __EOS_CALLBACKS_HPP
#include "System/Core/eosCallbacks.hpp"
#endif

#ifndef __EOS_I2CMASTER_HPP
#include "Services/eosI2CMaster.hpp"
#endif


namespace eos {
    
    class KeyboardService;
    typedef KeyboardService *KeyboardServiceHandle;
    
    struct KeyboardNotification {
        unsigned state;
    };
    
    class KeyboardService: private IRunable {        
        private:
            typedef ICallbackP1<KeyboardNotification&> IKeyboardServiceEvent;
            
        private:
            Task task;
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            unsigned state;
            IKeyboardServiceEvent *evNotify;
            
        public:
            KeyboardService(I2CMasterServiceHandle i2cService, uint8_t addr);
            ~KeyboardService();
            
            template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(KeyboardNotification&)) { 
                
                evNotify = new CallbackP1<cls, KeyboardNotification&>(instance, method); 
            }
        private:
            void run();
    };
}


#endif
