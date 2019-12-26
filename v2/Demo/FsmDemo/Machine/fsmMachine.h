#ifndef __FSMMACHINE_H
#define __FSMMACHINE_H


namespace app {

    class State;
    class Context;

    class Machine {
        private:
            State* state;
            Context* context;
        public:
            State* stateWaitingSW1;
            State* stateWaitingSW2;
            State* stateWaitingSW3;
            State* stateWaitingTMR1;
        private:
            void setState(State* state);
            void pushState(State* state);
            void popState();
        public:
            Machine(Context* context);
            inline State* getState() const { return state; }
            inline Context* getContext() const { return context; }
            void start();
            void pressedSW1();
            void pressedSW2();
            void pressedSW3();
            void timeoutTMR1();

        friend State;
    };
}


#endif // __FSMMACHINE_H
