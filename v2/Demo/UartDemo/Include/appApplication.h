#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlUART.h"
#include "HTL/htlTMR.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    using namespace eos;
    using namespace htl;

    class MyAppLoopService;

    class MyApplication: public Application {
        private:
#if 1
    	    using PinTX = config::uartService::GPIO_TX;
    	    using PinRX = config::uartService::GPIO_RX;
    		using Uart = config::uartService::UART;
#else
    		using PinTX = GPIO_A9;
    	    using PinRX = GPIO_B7;
    		using Uart = UART_1;
#endif
    		using PinLED = board::led1::GPIO_LED;
    		using PinSW = board::sw1::GPIO_SW;

    		using Tmr1 = config::digInputService::TMR;
    		using Tmr2 = config::digOutputService::TMR;

            using DigInputEventCallback = CallbackP1<MyApplication, const DigInput::EventArgs&>;

        private:
            DigOutputService *_digOutputService;
            DigInputService *_digInputService;
            MyAppLoopService *_loopService;

            DigOutput *_led;
            DigInput *_sw;
            DigInputEventCallback _swCallback;

        public:
            MyApplication();

        protected:
            void onInitialize();

        private:
            void initializeHardware();
            void initializeServices();

            static void isrTmr1(TMREvent, TMRInterruptParam);
            static void isrTmr2(TMREvent, TMRInterruptParam);

            void swEventHandler(const DigInput::EventArgs &args);
    };

}


#endif // __appApplication__
