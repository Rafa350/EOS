#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosTimerService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    class LedLoopService;

    class MyApplication: public eos::Application {
        private:
            using DigInputEventCallback = eos::CallbackP1<MyApplication, const eos::DigInput::EventArgs&>;
            using GPIO_LED1 = board::led1::GPIO_LED;
            using GPIO_LED2 = board::led2::GPIO_LED;
            using GPIO_LED3 = board::led3::GPIO_LED;
            using GPIO_SW1 = board::sw1::GPIO_SW;
            using GPIO_SW2 = board::sw2::GPIO_SW;
            using GPIO_SW3 = board::sw3::GPIO_SW;
            using TMR_INP = htl::TMR_2;
            usint TMR_OUT = htl::TMR_3;

        private:
            eos::DigOutputService *_digOutputService;
            eos::DigInputService *_digInputService;
            eos::TimerService *_timerService;

            #ifdef EXIST_LED1
                eos::DigOutput *led1;
            #endif
            #ifdef EXIST_LED2
                eos::DigOutput *led2;
            #endif
            #ifdef EXIST_LED3
                eos::DigOutput *led3;
            #endif
            #ifdef EXIST_SW1
                eos::DigInput *sw1;
                DigInputEventCallback sw1EventCallback;
            #endif
            #ifdef EXIST_SW2
                eos::DigInput *sw2;
                DigInputEventCallback sw2EventCallback;
            #endif
            #ifdef EXIST_SW3
                eos::DigInput *sw3;
                DigInputEventCallback sw3EventCallback;
            #endif

        public:
            MyApplication();
            #ifdef EXIST_SW1
                void sw1EventHandler(const eos::DigInput::EventArgs &args);
            #endif
            #ifdef EXIST_SW2
                void sw2EventHandler(const eos::DigInput::EventArgs &args);
            #endif
            #ifdef EXIST_SW3
                void sw3EventHandler(const eos::DigInput::EventArgs &args);
            #endif

        protected:
            void onInitialize();
    };

}


#endif // __appApplication__
