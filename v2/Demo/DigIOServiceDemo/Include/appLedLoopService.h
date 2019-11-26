#ifndef __appLedLoopService__
#define __appLedLoopService__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "System/eosApplication.h"


namespace app {

    class LedLoopService: public eos::AppLoopService {
        protected:
            void onLoop();

        public:
            LedLoopService(eos::Application *application);
    };

}


#endif // __appLedLoopService__
