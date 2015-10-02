#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosVector.hpp"


namespace eos {
    
    class DigInputService;
    class DigInput;
    
    class DigInputService: public IRunable {
        
        private:
            typedef eosVector<DirInput> Inputs;

        private:
            Task task;
            Inputs inputs;
            
        public:
            DigInputService():
            void add(DigInput *input);
        private:
            void run();
    };

    class DigInput {
        private:
            uint8_t pin;
            bool inverted;
        
        public:
            DigInput(uint8_t pin, bool inverted);
            bool get();
            bool posEdge();
            bool negEdge();
    };

}


#endif	

