#ifndef __appApplication__
#define __appApplication__


#include "eos.h"
#include "System/eosRTOSApplication.h"


namespace eos {

	class MessengerService;
}


namespace app {

    class MyAppLoopService;

    class MyApplication: public eos::RTOSApplication {
        private:
            MyAppLoopService *_loopService;
            eos::MessengerService *_messengerService;

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
