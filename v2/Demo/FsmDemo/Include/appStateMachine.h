#ifndef __appStateMachine__
#define __appStateMachine__


#include "eos.h"
#include "Services/eosFsmService.h"
#include "fsmMachine.h"


namespace app {
       
    class MyStateMachine: public eos::StateMachine {
        private:
            Machine machine;
        public:
            MyStateMachine();
    };
    
}


#endif // __appStateMachine__
