#ifndef __appDisplayService__
#define __appDisplayService__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "Services/eosI2CMasterService.h"


namespace app {
    
    class DisplayService: public eos::AppLoopService {
        private:
            eos::I2CMasterService *i2cMasterService;
            eos::I2CMasterTransactionConfiguration transactionConfig;
            uint8_t txBuffer[100];
            uint8_t rxBuffer[20];
            
        protected:
            void onLoop() override;
            void onSetup() override;
            
        public:
            DisplayService(eos::Application *application, eos::I2CMasterService *i2cMasterService);
    };
}


#endif // __appDisplayService__