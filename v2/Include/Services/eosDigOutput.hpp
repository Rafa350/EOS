#ifndef __EOS_DIGOUTPUT_HPP
#define	__EOS_DIGOUTPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosVector.hpp"


namespace eos {
    
    class DigOutput;
    class DigOutputService;
    
    class DigOutputService: public IRunable {      
        
        private:
            typedef Vector<DigOutput*> Outputs;
        
        private:
            Task task;
            Outputs outputs;
        
        public:
            DigOutputService();
            void add(DigOutput *output);
        private:
            void run();
    };
    
    class DigOutput {
        
        private:
            uint8_t pin;
            bool inverted;
            unsigned timeout;
        
        public:
            DigOutput(uint8_t pin, bool inverted);
            DigOutput(DigOutputService *service, uint8_t pin, bool inverted);
            bool get();
            void set(bool state);
            void toggle();
            void pulse(unsigned time);
            void delayedSet(unsigned delay, bool state);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);
        private:
            void pinInitialize();
            bool pinGet();
            void pinSet(bool state);
            void pinToggle();
            
        friend class eos::DigOutputService;
    };
}


#endif	

