#ifndef __EOS_EXTINTERRUPT_H
#define	__EOS_EXTINTERRUPT_H


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"


namespace eos {
    
    
    class Application;
    class Task;
    class ExtInterrupt;
    
    
    class ExtInterruptService: public Service {
        private:
            typedef List<ExtInterrupt*> ExtInterruptList;
            typedef ListIterator<ExtInterrupt*> ExtInterruptListIterator;
            
        private:
            ExtInterruptList extInterrupts;
        
        public:
            ExtInterruptService(Application *application);
            void add(ExtInterrupt *extInterrupt);
            void remove(ExtInterrupt *extInterrupt);
            
        private:
            void run(Task *task);           
    };
    
    class ExtInterrupt {
        private:
            ExtInterruptService *service;
            CNPin pin;
            
        public:
            ExtInterrupt(ExtInterruptService *service, CNPin pin);
            ~ExtInterrupt();

        private:
            static void interruptCallback(CNPin pin, void *param);
            
        friend ExtInterruptService;
    };
    
}


#endif	/* __EOS_EXTINTERRUPT_H */

