#ifndef __appDisplayService__
#define __appDisplayService__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "Services/eosI2CMasterService.h"


namespace app {
    
    class DisplayService: public eos::AppLoopService {
        private:
            eos::I2CMasterService *i2cMasterService;
            
        protected:
            void onLoop() override;
            void onSetup() override;
                       
        public:
            DisplayService(eos::Application *application, eos::I2CMasterService *i2cMasterService);
    };
}


#endif // __appDisplayService__