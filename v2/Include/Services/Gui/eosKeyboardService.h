#ifndef __EOS_KEYBOARD_H
#define __EOS_KEYBOARD_H


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/eosService.h"

#include <stdint.h>


namespace eos {

    class Application;
    class I2CMasterService;

    typedef uint8_t KeyboardState;

    class KeyboardService: public Service {
        private:
            typedef ICallbackP1<KeyboardState> IKeyboardServiceEvent;

        private:
            uint8_t addr;
            I2CMasterService *i2cService;
            KeyboardState state;
            IKeyboardServiceEvent *evNotify;

        public:
            KeyboardService(Application *application, I2CMasterService *i2cService, uint8_t addr);
            ~KeyboardService();

            template <class cls>
            void setNotifyEventHandler(cls *instance, void (cls::*method)(KeyboardState)) {
                if (evNotify != nullptr)
                    delete evNotify;
                evNotify = new CallbackP1<cls, KeyboardState>(instance, method);
            }

        private:
            void run(Task *task);
    };
}


#endif