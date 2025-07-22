#pragma once
#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosRTOSApplication.h"


#define USB_MAX_EP0_SIZE              64


namespace app {

    class MyApplication: public eos::RTOSApplication {
        protected:
            void onExecute() override;
            void initApplication(ApplicationParams &params) override;

        private:
            void initializeGPIO();
            void configureInterrupts();

        public:
            MyApplication();
    };
}


#endif // __appApplication__
