#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosVector.hpp"
#include "System/eosCallbacks.hpp"


#define EV_DigInput_onPosEdge(cls, instance, method) \
    new eos::CallbackP1<cls, eos::DigInput*>(instance, method)

#define EV_DigInput_onNegEdge(cls, instance, method) \
    new eos::CallbackP1<cls, eos::DigInput*>(instance, method)

#define EV_DigInput_onChange(cls, instance, method) \
    new eos::CallbackP1<cls, eos::DigInput*>(instance, method)


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
        public:
            typedef ICallbackP1<DigInput*> IDigInputEvent;

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
            IDigInputEvent *onPosEdge;
            IDigInputEvent *onNegEdge;
            IDigInputEvent *onChange;
        
        public:
            DigInput(uint8_t pin, bool inverted);
            DigInput(DigInputService *service, uint8_t pin, bool inverted);
            inline bool get() const { return state; }
            bool isPosEdge();
            bool isNegEdge();
            inline void setOnPosEdge(IDigInputEvent *event) { onPosEdge = event; }
            inline void setOnNegEdge(IDigInputEvent *event) { onNegEdge = event; }
            inline void setOnChange(IDigInputEvent *event) { onChange = event; }
        private:
            void pinInitialize() const;
            bool pinGet() const;
        
        friend class eos::DigInputService;
    };

}


#endif	

