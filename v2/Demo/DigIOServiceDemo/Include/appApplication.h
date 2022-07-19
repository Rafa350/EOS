#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
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
            using TMR_INP = DigInputService_Timer;
            using TMR_OUT = DigOutputService_Timer;

        private:
            eos::DigOutputService *_digOutputService;
            eos::DigInputService *_digInputService;

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

        protected:
            void onInitialize();
            static void tmrInpInterruptFunction(htl::TMREvent, htl::TMRInterruptParam);
            static void tmrOutInterruptFunction(htl::TMREvent, htl::TMRInterruptParam);

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
    };

}


#endif // __appApplication__
