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
        virtual void transition(unsigned eventId);
};

class WaitSW1State: public State {
    public:
        WaitSW1State(Machine* machine);
        void enter() override;
        void transition(unsigned eventId) override;
};

class WaitSW2State: public State {
    public:
        WaitSW2State(Machine* machine);
        void enter() override;
        void exit() override;
        void transition(unsigned eventId) override;
};

class WaitSW3State: public State {
    public:
        WaitSW3State(Machine* machine);
        void transition(unsigned eventId) override;
};

class WaitTimer1State: public State {
    public:
        WaitTimer1State(Machine* machine);
        void transition(unsigned eventId) override;
};


#endif
