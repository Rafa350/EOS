#ifndef __EOS_UART_HPP
#define __EOS_UART_HPP


#include "eos.h"
#include "Services/eosService.hpp"


namespace eos {
    
    
    class Application;
    class Task;

    
    class UARTService: public Service {
        public:
            UARTService(Application *application, uint_8 moduleId);
            
        private:
            static void interruptCallback(uint8_t moduleId, void *param);
            void run(Task *task);
    }
}


#endif
