#ifndef __appStateMachine__
#define __appStateMachine__


#include "eos.h"
#include "Services/eosFsmService.h"
#include "System/Core/eosQueue.h"


namespace app {
    
    class Context;
    
    class MyStateMachine: public eos::FsmMachine {
        public:
            enum class Message {
                pressedSW1,
                pressedSW2,
                pressedSW3,
            };
            enum class Action {
                led1ON,
                led2ON,
                led3ON,
                led1OFF,
                led2OFF,
                led3OFF
            };
            typedef eos::Queue<Message> MessageQueue;
        private:
            Context* context;
            MessageQueue messageQueue;
        protected:
            void initialize() override;
            void task() override;
        public:
            MyStateMachine();
            bool acceptMessage(Message message, unsigned blockTime);
            void doLED1On();
            void doLED2On();
            void doLED3On();
            void doLED1Off();
            void doLED2Off();
            void doLED3Off();
    };
    
}


#endif // __appStateMachine__
