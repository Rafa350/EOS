#ifndef __appStateMachine__
#define __appStateMachine__


#include "eos.h"
#include "Services/eosFsmService.h"
#include "System/Core/eosQueue.h"
#include "fsmContext.h"
#include "fsmState.h"


namespace app {
       
    class MyStateMachine: public eos::StateMachine {
        public:
            enum class Message {
                pressedSW1,
                pressedSW2,
                pressedSW3,
            };
            typedef eos::Queue<Message> MessageQueue;
        private:
            eos::Context* context;
            MessageQueue messageQueue;
        public:
            MyStateMachine();
            bool acceptMessage(Message message, unsigned blockTime);
            void task() override;
    };
    
}


#endif // __appStateMachine__
