#ifndef __EOS_SELECTOR_HPP
#define __EOS_SELECTOR_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "Services/eosService.hpp"

#include <stdint.h>


namespace eos {

    class Application;
    class I2CMasterService;

    typedef int16_t SelectorPosition;
    typedef uint8_t SelectorState;

    class SelectorService: public Service {
        private:
            typedef ICallbackP2<SelectorPosition, SelectorState> ISelectorServiceEvent;

        private:
            uint8_t addr;
            I2CMasterService *i2cService;
            SelectorPosition position;
            SelectorState state;
            ISelectorServiceEvent *evNotify;

        public:
            SelectorService(Application *application, I2CMasterService *i2cService, uint8_t addr);
            ~SelectorService();

            template <class cls>
            void setNotifyEventHandler(cls *instance, void (cls::*method)(SelectorPosition, SelectorState)) {
                if (evNotify != nullptr)
                    delete evNotify;
                evNotify = new CallbackP2<cls, SelectorPosition, SelectorState>(instance, method);
            }

        private:
            void run(Task *task);
    };
}


#endif
