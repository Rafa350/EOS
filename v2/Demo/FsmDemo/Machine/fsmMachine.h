#ifndef __FSMMACHINE_H
#define __FSMMACHINE_H


class State;
class IContext;


class Machine {
    private:
        State* state;
        State* stateWaitingSW1;
        State* stateWaitingSW2;
        State* stateWaitingSW3;
        State* stateWaitingTimer1;
        IContext* context;
    private:
        void setState(State* state);
        void pushState(State* state);
        void popState();
    public:
        Machine(IContext* context);
        inline State* getState() const { return state; }
        inline IContext* getContext() const { return context; }
        void start();
        void sw1_pressed();
        void sw2_pressed();
        void sw3_pressed();
        void timer1_timeout();

    friend State;
};


#endif
