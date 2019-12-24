#ifndef __FSMSTATE_H
#define __FSMSTATE_H


class Machine;
class IContext;


class State {
    private:
        Machine* machine;
    protected:
        inline Machine* getMachine() const { return machine; }
        IContext* getContext() const;
        inline void setState(State* state) const { machine->setState(state); }
    public:
        State(Machine* machine);
        virtual void enter();
        virtual void exit();
        virtual void pressedSW1();
        virtual void pressedSW2();
        virtual void pressedSW3();
        virtual void timeoutTMR1();
};

class WaitingSW1: public State {
    public:
        WaitingSW1(Machine* machine);
        void pressedSW1() override;
};

class WaitingSW2: public State {
    public:
        WaitingSW2(Machine* machine);
        void pressedSW2() override;
};

class WaitingSW3: public State {
    public:
        WaitingSW3(Machine* machine);
        void pressedSW3() override;
};

class WaitingTMR1: public State {
    public:
        WaitingTMR1(Machine* machine);
        void timeoutTMR1() override;
};


#endif
