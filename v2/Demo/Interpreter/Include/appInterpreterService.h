#ifndef __appInterpreterService__
#define __appInterpreterService__


#include "eos.h"
#include "Services/eosAppLoopService.h"


namespace app {
    
    class InterpreterService: public eos::AppLoopService {
        private:
            const uint8_t* ip;
            uint8_t stack[10];
            uint8_t* sp;
            
        protected:
            virtual void onSetup();
            virtual void onLoop();
            
            void add();
            void drop();
            void lit();

        public:
            InterpreterService(eos::Application* application);
    };
}


#endif

