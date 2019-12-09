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
            typedef CallbackP1<MyApplication, const TimerCounter::EventArgs&> TimerEventCallback;

        private:
            LedLoopService* ledLoopService;
            DigOutputService* digOutputService;
            DigInputService* digInputService;
            TimerService* timerService;
            TimerCounter* timer1;
            TimerCounter* timer2;
            TimerEventCallback timerEventCallback;
            
    #ifdef EXIST_LEDS_LED1
            DigOutput *digOutput1;
    #endif
    #ifdef EXIST_LEDS_LED2
            DigOutput *digOutput2;
    #endif
    #ifdef EXIST_LEDS_LED3
            DigOutput *digOutput3;
    #endif
    #ifdef EXIST_SWITCHES_SW1
            DigInput *digInput1;
            DigInputEventCallback digInput1EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW2
            DigInput *digInput2;
            DigInputEventCallback digInput2EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW3
            DigInput *digInput3;
            DigInputEventCallback digInput3EventCallback;
    #endif

        public:
            MyApplication();
            void timerEventHandler(const TimerCounter::EventArgs& args);
    #ifdef EXIST_SWITCHES_SW1
            void digInput1EventHandler(const DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW2
            void digInput2EventHandler(const DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW3
            void digInput3EventHandler(const DigInput::EventArgs &args);
    #endif

    #ifdef EXIST_LEDS_LED1
            DigOutput *getLed1() const { return digOutput1; }
    #endif
    #ifdef EXIST_LEDS_LED2
            DigOutput *getLed2() const { return digOutput2; }
    #endif
    #ifdef EXIST_LEDS_LED3
            DigOutput *getLed3() const { return digOutput3; }
    #endif

        protected:
            void onInitialize();
    };

}


#endif // __appApplication__
