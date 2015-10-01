#ifndef __EOS_DIGOUTPUT_HPP
#define	__EOS_DIGOUTPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosDigPin.h"
#include "System/eosVector.hpp"


namespace eos {
    
    class DigOutput;
    
    class DigOutputService {
        
        class ServiceTask: public Task {
            public:
                ServiceTask(DigOutputService *service);
                void run();
            private:
                DigOutputService *service;
        };
        
        typedef Vector<DigOutput*> OutputVector;
        
        public:
            DigOutputService();
            void add(DigOutput *output);
        private:
            ServiceTask task;
            OutputVector outputs;
    };
    
    class DigOutput {
        public:
            DigOutput(unsigned pin, bool inverted);
            DigOutput(DigOutputService *service, unsigned pin, bool inverted);
            bool get();
            void set(bool state);
            void toggle();
            void pulse(unsigned time);
            void delayerSet(unsigned delay, bool state);
            void delayerToggle(unsigned delay);
            void delayerPulse(unsigned delay, unsigned time);
        private:
            unsigned pin;
            unsigned timeout;
            bool inverted;
            void pinInitialize();
            bool pinGet();
            void pinSet(bool state);
            void pinToggle();
    };
}


#endif	

