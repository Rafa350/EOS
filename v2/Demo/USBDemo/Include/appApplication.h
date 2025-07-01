#pragma once
#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace app {

    class MyApplication: public eos::RTOSApplication {
        protected:
            void onExecute() override;

        private:
            void initializeGPIO();
            void configureInterrupts();

        public:
            MyApplication();
    };
}


#endif // __appApplication__
