#ifndef __eosKeyboardService__
#define __eosKeyboardService__


#include "eos.h"
#include "System/eosCallbacks.h"
#include "Services/eosService.h"


#ifndef eosKeyboardService_StackSize
#define eosKeyboardService_StackSize 512
#endif

#ifndef eosKeyboardService_TaskPriority
#define eosKeyboardService_TaskPriority TaskPriority::normal
#endif


namespace eos {

    class Application;
    class I2CMasterService;

    typedef uint8_t KeyboardState;

    class KeyboardService: public Service {
        private:
            typedef ICallbackP1<KeyboardState> IEventCallback;

        private:
            int i2cAddress;
            I2CMasterService *i2cService;
            KeyboardState state;
            IEventCallback *eventCallback;

        public:
            KeyboardService(Application *application, I2CMasterService *i2cService, int i2cAddress);

            inline void setEventCallback(IEventCallback *callback) { eventCallback = callback; }

        protected:
            void onInitialize() override;
            void onTask() override;
    };
}


#endif // __eosKeyboardService__
