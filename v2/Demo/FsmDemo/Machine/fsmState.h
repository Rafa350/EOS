#ifndef __FSMSTATE_H
#define __FSMSTATE_H


namespace app {

    class Machine;
    class Context;

    class State {
        protected:
            State();
        public:
            virtual State* onSW1_ON(Machine* machine);
            virtual State* onSW3_ON(Machine* machine);
            virtual State* onSW2_ON(Machine* machine);
            virtual State* onTMR1_TIMEOUT(Machine* machine);
    };

    class WaitingSW1: public State {
        private:
            static WaitingSW1* instance;
        private:
            WaitingSW1();
        public:
            static WaitingSW1* getInstance();
            State* onSW1_ON(Machine* machine) override;
    };

    class WaitingSW3: public State {
        private:
            static WaitingSW3* instance;
        private:
            WaitingSW3();
        public:
            static WaitingSW3* getInstance();
            State* onSW3_ON(Machine* machine) override;
    };

    class WaitingSW2: public State {
        private:
            static WaitingSW2* instance;
        private:
            WaitingSW2();
        public:
            static WaitingSW2* getInstance();
            State* onSW2_ON(Machine* machine) override;
    };

    class WaitingTMR1: public State {
        private:
            static WaitingTMR1* instance;
        private:
            WaitingTMR1();
        public:
            static WaitingTMR1* getInstance();
            State* onTMR1_TIMEOUT(Machine* machine) override;
    };

}


#endif // __FSMSTATE_H
