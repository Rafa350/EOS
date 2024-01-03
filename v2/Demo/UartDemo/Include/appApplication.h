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
    };
}


#endif // __appApplication__
