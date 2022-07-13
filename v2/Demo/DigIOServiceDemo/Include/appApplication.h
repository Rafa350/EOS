#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosTimerService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    using namespace eos;

    class LedLoopService;

    class MyApplication: public Application {
        private:
            typedef CallbackP1<MyApplication, const DigInput::EventArgs&> DigInputEventCallback;
            typedef LEDS_LED1_TYPE GPIO_LED1;
            typedef LEDS_LED2_TYPE GPIO_LED2;
            typedef LEDS_LED3_TYPE GPIO_LED3;
            typedef SWITCHES_SW1_TYPE GPIO_SW1;
            typedef SWITCHES_SW2_TYPE GPIO_SW2;
            typedef SWITCHES_SW3_TYPE GPIO_SW3;

        private:
            DigOutputService *_digOutputService;
            DigInputService *_digInputService;
            TimerService *_timerService;

    #ifdef EXIST_LEDS_LED1
            DigOutput *led1;
    #endif
    #ifdef EXIST_LEDS_LED2
            DigOutput *led2;
    #endif
    #ifdef EXIST_LEDS_LED3
            DigOutput *led3;
    #endif
    #ifdef EXIST_SWITCHES_SW1
            DigInput *sw1;
            DigInputEventCallback sw1EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW2
            DigInput *sw2;
            DigInputEventCallback sw2EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW3
            DigInput *sw3;
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

        protected:
            void onInitialize();
    };

}


#endif // __appApplication__
