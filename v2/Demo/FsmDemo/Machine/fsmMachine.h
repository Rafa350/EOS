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
            Machine(Context* context);
            inline State* getState() const { return state; }
            inline Context* getContext() const { return context; }
            void start();
            void terminate();
            void onSW1_ON();
            void onSW2_ON();
            void onSW3_ON();
            void onTMR1_TIMEOUT();
            void doLED1_ON();
            void doLED1_OFF();
            void doLED2_ON();
            void doLED2_OFF();
            void doLED3_ON();
            void doTMR1_START();
            void doLED3_OFF();

        friend State;
    };
}


#endif // __FSMMACHINE_H
