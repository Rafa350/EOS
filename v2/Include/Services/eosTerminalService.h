#ifndef __eosTerminalService__
#define __eosTerminalService__


#include "eos.h"
#include "HAL/halUART.h"
#include "Services/eosService.h"


namespace eos {
    
    class Application;
    class Task;
    
    class TerminalService: public Service {
        public:
            struct Configuration {
                UARTModule module;
                int baudRate;
            };
            
            TerminalService(Application *application, const Configuration &cfg);
            ~TerminalService();
            
        protected:
            void onInitialize() override;
            void onTask() override;
            
        private:
            UARTModule module;
            
            void initializeHardware(const Configuration &cfg);
            void deinitializeHardware();
            static void interruptCallback(UARTModule module, void *param);
    };
}


#endif // __eosUartService__
