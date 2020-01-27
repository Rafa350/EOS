#ifndef __FSMMACHINE_H
#define __FSMMACHINE_H


namespace app {

    class State;
    class Context;

    class Machine {
        private:
            State* state;
            Context* context;
        protected:
            void setState(State* state);
            void pushState(State* state);
            void popState();
        public:
            Machine(Context* context);
            inline State* getState() const { return state; }
            inline Context* getContext() const { return context; }
            void start();
            void onSW1_ON();
            void onSW3_ON();
            void onSW2_ON();
            void onTMR1_TIMEOUT();
            void doLED1_ON();
            void doLED2_ON();
            void doLED3_ON();
            void doWaitingSW1_EnterAction();
            void doWaitingSW1_ExitAction();
            void doLED2_OFF();
            void doTMR1_START();
            void doWaitingSW3_EnterAction();
            void doLED1_OFF();

        friend State;
    };
}


#endif // __FSMMACHINE_H
