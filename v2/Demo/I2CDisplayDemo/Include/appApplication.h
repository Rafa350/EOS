#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosApplication.h"


namespace eos {
    class I2CMasterService;
}


namespace app {
    
    class DisplayService;

    class MyApplication: public eos::Application {
        private:
            eos::I2CMasterService *i2cMasterService;
            DisplayService *displayService;

        protected:
            void onInitialize();

        public:
            MyApplication();
    };
}


#endif
