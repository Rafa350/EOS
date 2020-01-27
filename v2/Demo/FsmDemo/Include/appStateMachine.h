#ifndef __appStateMachine__
#define __appStateMachine__


#include "eos.h"
#include "Services/eosFsmService.h"
#include "fsmMachine.h"
#include "fsmState.h"


namespace app {
       
    class MyStateMachine: public eos::StateMachine {
        public:
            enum class Event {
                prossedSW1,
                pressedSW2,
                pressedSW3,
            };
        private:
            Machine* machine;
        public:
            MyStateMachine();
            void accept(Event event);
    };
    
}


#endif // __appStateMachine__
