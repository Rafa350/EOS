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
    public:
        State(Machine* machine);
        virtual void enter();
        virtual void exit();
        virtual void sw1_pressed();
        virtual void sw2_pressed();
        virtual void sw3_pressed();
        virtual void timer1_timeout();
};

class WaitingSW1: public State {
    public:
        WaitingSW1(Machine* machine);
        void enter() override;
        void sw1_pressed() override;
};

class WaitingSW2: public State {
    public:
        WaitingSW2(Machine* machine);
        void enter() override;
        void exit() override;
        void sw2_pressed() override;
};

class WaitingSW3: public State {
    public:
        WaitingSW3(Machine* machine);
        void sw3_pressed() override;
};

class WaitingTimer1: public State {
    public:
        WaitingTimer1(Machine* machine);
        void timer1_timeout() override;
};


#endif
