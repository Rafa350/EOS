#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"
#include "HTL/htlUART.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    class LedLoopService;

    class MyApplication: public eos::Application {
        private:
            using GPIO_LED1 = board::led1::GPIO_LED;
            using GPIO_SW1 = board::sw1::GPIO_SW;
            using DigInputEventCallback = eos::CallbackP1<MyApplication, const eos::DigInput::EventArgs&>;

        private:
            eos::DigOutput *led1;
            eos::DigInput *sw1;
            eos::DigOutputService *_digOutputService;
            eos::DigInputService *_digInputService;
            DigInputEventCallback sw1EventCallback;

        protected:
            void onInitialize();
            void sw1EventHandler(const eos::DigInput::EventArgs &args);

        public:
            MyApplication();
    };

}


#endif // __appApplication__
