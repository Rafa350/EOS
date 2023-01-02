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
            using INPSRV_TMR = config::digInputService::TMR;
            using OUTSRV_TMR = config::digOutputService::TMR;

            using DigInputChangedEventCallback = eos::CallbackP1<MyApplication, const eos::DigInput::ChangedEventArgs&>;

        private:
            eos::DigOutputService *_digOutputService;
            eos::DigInputService *_digInputService;

            #ifdef EXIST_LED1
                eos::DigOutput *_led1;
            #endif
            #ifdef EXIST_LED2
                eos::DigOutput *_led2;
            #endif
            #ifdef EXIST_LED3
                eos::DigOutput *_led3;
            #endif
            #ifdef EXIST_SW1
                eos::DigInput *_sw1;
                DigInputChangedEventCallback _sw1ChangedEventCallback;
            #endif
            #ifdef EXIST_SW2
                eos::DigInput *_sw2;
                DigInputChangedEventCallback _sw2ChangedEventCallback;
            #endif
            #ifdef EXIST_SW3
                eos::DigInput *_sw3;
                DigInputChangedEventCallback _sw3ChangedEventCallback;
            #endif

        protected:
            void onInitialize();
            #ifdef EXIST_SW1
                void sw1ChangedEventHandler(const eos::DigInput::ChangedEventArgs &args);
            #endif
            #ifdef EXIST_SW2
                void sw2ChangedEventHandler(const eos::DigInput::ChangedEventArgs &args);
            #endif
            #ifdef EXIST_SW3
                void sw3ChangedEventHandler(const eos::DigInput::ChangedEventArgs &args);
            #endif
            static void digInputServiceTMRInterruptFunction(htl::TMRInterruptParam);
            static void digOutputServiceTMRInterruptFunction(htl::TMRInterruptParam);

        public:
            MyApplication();
    };

}


#endif // __appApplication__
