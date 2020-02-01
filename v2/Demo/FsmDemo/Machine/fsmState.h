#ifndef __FSMSTATE_H
#define __FSMSTATE_H


#include "eos.h"
#include "Services/Fsm/eosFsmStateBase.h"


namespace eos {

    class State: public FsmStateBase {

        protected:
            State();

        public:
            virtual void onSW1_ON(Context* context);
            virtual void onSW2_ON(Context* context);
            virtual void onSW3_ON(Context* context);
            virtual void onTMR1_TIMEOUT(Context* context);
    };

    class WaitingSW1: public State {

        protected:
            WaitingSW1();

        public:
            static WaitingSW1* getInstance();
            void onSW1_ON(Context* context) override;
    };

    class WaitingSW2: public State {

        protected:
            WaitingSW2();

        public:
            static WaitingSW2* getInstance();
            void onSW2_ON(Context* context) override;
    };

    class WaitingSW3: public State {

        protected:
            WaitingSW3();

        public:
            static WaitingSW3* getInstance();
            void onSW3_ON(Context* context) override;
    };

    class WaitingTMR1: public State {

        protected:
            WaitingTMR1();

        public:
            static WaitingTMR1* getInstance();
            void onTMR1_TIMEOUT(Context* context) override;
    };

}


#endif // __FSMSTATE_H
