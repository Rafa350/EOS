#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlUART.h"
#include "HTL/htlTMR.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosUARTService.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    using namespace eos;
    using namespace htl;

    class MyAppLoopService;

    class MyApplication: public Application {
        private:
    	    using PinTX = config::uartService::GPIO_TX;
    	    using PinRX = config::uartService::GPIO_RX;
    		using Uart = config::uartService::UART;

    		using PinLED = board::led1::GPIO_LED;
    		using PinSW = board::sw1::GPIO_SW;

    		using Tmr1 = config::digInputService::TMR;
    		using Tmr2 = config::digOutputService::TMR;

            typedef CallbackP1<MyApplication, const DigInput::EventArgs&> DigInputEventCallback;

        private:
            DigOutputService *_digOutputService;
            DigInputService *_digInputService;
            UARTService *_uartService;
            MyAppLoopService *_loopService;

            DigOutput *_led;
            DigInput *_sw;
            DigInputEventCallback _swEventCallback;

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
