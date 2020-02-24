#ifndef __appStateMachine__
#define __appStateMachine__


#include "eos.h"
#include "Services/eosFsmService.h"
#include "System/Core/eosQueue.h"


namespace app {
    
    class Context;
    
    class MyStateMachine: public eos::StateMachine {
        public:
            enum class Message {
                pressedSW1,
                pressedSW2,
                pressedSW3,
            };
            typedef eos::Queue<Message> MessageQueue;
        private:
            Context* context;
            MessageQueue messageQueue;
        public:
            MyStateMachine();
            bool acceptMessage(Message message, unsigned blockTime);
            void task() override;
            void doLED1On();
            void doLED2On();
            void doLED3On();
            void doLED1Off();
            void doLED2Off();
            void doLED3Off();
    };
    
}


#endif // __appStateMachine__
