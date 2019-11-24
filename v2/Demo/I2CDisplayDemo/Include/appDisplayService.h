#ifndef __appDisplayService__
#define __appDisplayService__


#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "Services/eosAppLoopService.h"


namespace app {
    
    class DisplayService: public eos::AppLoopService {
        private:
            eos::GfxDisplay *display;
            int x;
            int y;
            
        protected:
            void onLoop() override;
            void onSetup() override;
                       
        public:
            DisplayService(eos::Application *application, eos::GfxDisplay *display);
    };
}


#endif // __appDisplayService__