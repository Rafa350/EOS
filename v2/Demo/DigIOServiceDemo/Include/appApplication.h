#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlTMR.h"
#include "Services/eosDigInputService.h"
#include "Services/eosDigOutputService.h"
#include "System/eosRTOSApplication.h"
#include "System/eosCallbacks.h"


namespace app {

    typedef struct {
        int id;
    } ButtonMessage;

    class MyApplication: public eos::RTOSApplication {
        private:
            using PinDevice = htl::gpio::PinDevice;

            static constexpr PinDevice *_pinSW1 = SW1_Pin::pInst;
            static constexpr PinDevice *_pinSW2 = SW2_Pin::pInst;
            static constexpr PinDevice *_pinSW3 = SW3_Pin::pInst;
            static constexpr PinDevice *_pinLED1 = LED1_Pin::pInst;
            static constexpr PinDevice *_pinLED2 = LED2_Pin::pInst;
            static constexpr PinDevice *_pinLED3 = LED3_Pin::pInst;

        private:
            using INPSRV_TMR = config::digInputService::TMR;
            using OUTSRV_TMR = config::digOutputService::TMR;

            using DigInputNotifyEvent = eos::DigInputService::NotifyEvent<MyApplication>;

        private:
            eos::DigOutputService *_digOutputService;
            eos::DigInputService *_digInputService;
            DigInputNotifyEvent _digInputNotifyEvent;

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
            #endif
            #ifdef EXIST_SW2
                eos::DigInput *_sw2;
            #endif
            #ifdef EXIST_SW3
                eos::DigInput *_sw3;
            #endif

        protected:
            void onExecute() override;
            void digInputNotifyEventHandler(eos::DigInputService::NotifyID id, eos::DigInputService::NotifyEventArgs * const args);
            
        public:
            MyApplication();
    };

}


#endif // __appApplication__
