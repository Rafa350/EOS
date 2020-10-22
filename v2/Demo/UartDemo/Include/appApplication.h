#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosUARTService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    using namespace eos;

    class MyAppLoopService;

    class MyApplication: public Application {
        private:
            typedef CallbackP1<MyApplication, const DigInput::EventArgs&> DigInputEventCallback;

        private:
            DigOutputService* digOutputService;
            DigInputService* digInputService;
            UARTService* uartService;
            MyAppLoopService* loopService;

    #ifdef EXIST_LEDS_LED1
            DigOutput* led1;
    #endif
    #ifdef EXIST_LEDS_LED2
            DigOutput* led2;
    #endif
    #ifdef EXIST_LEDS_LED3
            DigOutput* led3;
    #endif
    #ifdef EXIST_SWITCHES_SW1
            DigInput* sw1;
            DigInputEventCallback sw1EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW2
            DigInput* sw2;
            DigInputEventCallback sw2EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW3
            DigInput* sw3;
            DigInputEventCallback sw3EventCallback;
    #endif

        public:
            MyApplication();
    #ifdef EXIST_SWITCHES_SW1
            void sw1EventHandler(const DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW2
            void sw2EventHandler(const DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW3
            void sw3EventHandler(const DigInput::EventArgs &args);
    #endif
            inline UARTService* getUARTService() const { return uartService; }

        protected:
            void onInitialize();

        private:
            void initializeHardware();
            void initializeServices();
    };

}


#endif // __appApplication__
