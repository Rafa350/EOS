#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {
    
    class LedLoopService;

    class MyApplication: public eos::Application {
        private:
            typedef eos::CallbackP1<MyApplication, const eos::DigInput::EventArgs&> DigInputEventCallback;

        private:
            LedLoopService *ledLoopService;
            eos::DigOutputService *digOutputService;
            eos::DigInputService *digInputService;
            
    #ifdef EXIST_LEDS_LED1
            eos::DigOutput *digOutput1;
    #endif
    #ifdef EXIST_LEDS_LED2
            eos::DigOutput *digOutput2;
    #endif
    #ifdef EXIST_LEDS_LED3
            eos::DigOutput *digOutput3;
    #endif
    #ifdef EXIST_SWITCHES_SW1
            eos::DigInput *digInput1;
            DigInputEventCallback digInput1EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW2
            eos::DigInput *digInput2;
            DigInputEventCallback digInput2EventCallback;
    #endif
    #ifdef EXIST_SWITCHES_SW3
            eos::DigInput *digInput3;
            DigInputEventCallback digInput3EventCallback;
    #endif

        public:
            MyApplication();
    #ifdef EXIST_SWITCHES_SW1
            void digInput1_OnChange(const eos::DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW2
            void digInput2_OnChange(const eos::DigInput::EventArgs &args);
    #endif
    #ifdef EXIST_SWITCHES_SW3
            void digInput3_OnChange(const eos::DigInput::EventArgs &args);
    #endif

    #ifdef EXIST_LEDS_LED1
            eos::DigOutput *getLed1() const { return digOutput1; }
    #endif
    #ifdef EXIST_LEDS_LED2
            eos::DigOutput *getLed2() const { return digOutput2; }
    #endif
    #ifdef EXIST_LEDS_LED3
            eos::DigOutput *getLed3() const { return digOutput3; }
    #endif

        protected:
            void onInitialize();
    };

}


#endif // __appApplication__
