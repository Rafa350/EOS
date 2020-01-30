#ifndef __FSMCONTEXT_H
#define __FSMCONTEXT_H


#include "eos.h"
#include "Services/Fsm/eosFsmContextBase.h"


namespace eos {

    class Context: public FsmContextBase {

        public:
            Context();
            void start();
            void end();
            void onSW1_ON();
            void onSW2_ON();
            void onSW3_ON();
            void onTMR1_TIMEOUT();
            void doLED1_ON();
            void doLED1_OFF();
            void doLED2_ON();
            void doLED3_ON();
            void doLED2_OFF();
            void doTMR1_START();
            void doLED3_OFF();
    };

}


#endif // __FSMCONTEXT_H
