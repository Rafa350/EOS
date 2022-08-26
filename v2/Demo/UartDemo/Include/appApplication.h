#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosApplication.h"


namespace app {

    class MyAppLoopService;

    class MyApplication: public eos::Application {
        private:
            MyAppLoopService *_loopService;

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
