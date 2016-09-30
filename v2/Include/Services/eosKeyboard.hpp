#ifndef __EOS_SERVICES_KEYBOARD_HPP
#define __EOS_SERVICES_KEYBOARD_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/eosService.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {
    
    class Application;
       
    typedef uint8_t KeyboardState;
    
    class KeyboardService: public Service {        
        private:
            typedef ICallbackP1<KeyboardState> IKeyboardServiceEvent;
            
        private:
            uint8_t addr;
            I2CMasterServiceHandle i2cService;
            KeyboardState state;
            IKeyboardServiceEvent *evNotify;
            
        public:
            KeyboardService(Application *application, I2CMasterServiceHandle i2cService, uint8_t addr);
            ~KeyboardService();
            
            template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(KeyboardState)) { 
                
                evNotify = new CallbackP1<cls, KeyboardState>(instance, method); 
            }
            
        private:
            void run();
    };
}


#endif
