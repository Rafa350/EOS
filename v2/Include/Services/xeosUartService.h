#ifndef __eosUartService__
#define __eosUartService__


#include "eos.h"
#include "Services/eosService.h"


namespace eos {
    
    
    class Application;
    class Task;

    
    class UARTService: public Service {
        public:
            UARTService(Application *application, UARTModule module);
            
        protected:
            void onInitialize() override;
            void onTask() override;
            
        private:
            static void interruptCallback(uint8_t moduleId, void *param);
    }
}


#endif // __eosUartService__
