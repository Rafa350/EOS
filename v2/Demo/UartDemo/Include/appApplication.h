#pragma once
#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace app {

    class MyApplication: public eos::RTOSApplication {
        public:
            MyApplication();

        protected:
            void onInitialize();

        private:
            void initializeHardware();
            void initializeServices();
    };
}


#endif // __appApplication__
