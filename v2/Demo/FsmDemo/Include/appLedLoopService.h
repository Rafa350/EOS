#ifndef __appLedLoopService__
#define __appLedLoopService__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "System/eosApplication.h"


namespace app {

    using namespace eos;

    class LedLoopService: public AppLoopService {
        protected:
            void onLoop();

        public:
            LedLoopService(Application* application);
    };

}


#endif // __appLedLoopService__
