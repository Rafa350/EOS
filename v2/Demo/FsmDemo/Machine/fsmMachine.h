#ifndef __FSMMACHINE_H
#define __FSMMACHINE_H


class State;
class IContext;


class Machine {
    private:
        State* state;
        IContext* context;
    public:
        Machine(IContext* context);
        inline State* getState() const { return state; }
        inline IContext* getContext() const { return context; }
};


#endif
