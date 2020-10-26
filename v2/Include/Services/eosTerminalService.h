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
            struct Settings {
                UARTHandler hUART;
                int baudRate;
            };

            TerminalService(Application *application, const Settings &settings);
            ~TerminalService();

        protected:
            void onInitialize() override;
            void onTask(Task *task) override;

        private:
            UARTHandler hUART;

            void deinitializeHardware();
            static void interruptFunction(UARTHandler handler, void *params);
    };
}


#endif // __eosUartService__
