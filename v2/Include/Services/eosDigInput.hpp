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
            typedef Vector<DigInput*> Inputs;

        private:
            Task task;
            Inputs inputs;
            
        public:
            DigInputService();
            void add(DigInput *input);
        private:
            void run();
    };

    class DigInput {
        private:
            uint8_t pin;
            uint32_t pattern;
            bool inverted;
            bool state;
            bool posEdge;
            bool negEdge;
            bool onPosEdgeFired;
            bool onNegEdgeFired;
            bool onChangeFired;
        
        public:
            DigInput(uint8_t pin, bool inverted);
            DigInput(DigInputService *service, uint8_t pin, bool inverted);
            bool get();
            bool isPosEdge();
            bool isNegEdge();
        private:
            void pinInitialize();
            bool pinGet();
        
        friend class eos::DigInputService;
    };

}


#endif	
