#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosApplication.h"


namespace eos {
    class I2CMasterService;
}


namespace app {
    
    class DisplayService;
    class LedService;

    class MyApplication: public eos::Application {

        protected:
            void onInitialize();

        public:
            MyApplication();
    };
}


#endif
