#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlUART.h"
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
    	    using GPIO_TX = board::arduino::GPIO_TX;
    	    using GPIO_RX = board::arduino::GPIO_RX;
    		using UART = board::arduino::UART;

    		using GPIO_LED = board::led1::GPIO_LED;
    		using GPIO_SW = board::sw1::GPIO_SW;

    		using TMR_INPSRV = config::digInputService::TMR;
    		using TMR_OUTSRV = config::digOutputService::TMR;

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
            void swEventHandler(const DigInput::EventArgs &args);
    };

}


#endif // __appApplication__
