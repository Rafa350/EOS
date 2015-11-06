#ifndef __EOS_DIGOUTPUT_HPP
#define	__EOS_DIGOUTPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"


namespace eos {
    
    class DigOutput;
    typedef DigOutput *DigOutputHandle;
    
    class DigOutputService;
    typedef DigOutputService *DigOutputServiceHandle;
    
    class DigOutputService: public IRunable {      
        private:
            typedef List<DigOutputHandle> DigOutputList;
            typedef ListIterator<DigOutputHandle> DigOutputListIterator;
            
        private:
            Task task;
            DigOutputList outputs;        
            
        public:
            DigOutputService();
            void add(DigOutputHandle output);
        private:
            void run();
    };
    
    class DigOutput {        
        private:
            DigOutputServiceHandle service;
            uint8_t pin;
            bool inverted;
            unsigned timeout;
        
        public:
            DigOutput(DigOutputServiceHandle service, uint8_t pin, bool inverted);
            bool get() const;
            void set(bool state);
            void toggle();
            void pulse(unsigned time);
            void delayedSet(unsigned delay, bool state);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);
        private:
            void pinInitialize() const;
            bool pinGet() const;
            void pinSet(bool state) const;
            void pinToggle() const;
            
        friend class DigOutputService;
    };
}


#endif	

