#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"
#include "System/eosCallbacks.hpp"


#define EV_DigInput_onChange(cls, instance, method) \
    new eos::CallbackP1<cls, eos::DigInput*>(instance, method)


namespace eos {
    
    class DigInput;

    typedef List<DigInput*> DigInputList;
    typedef ListIterator<DigInput*> DigInputListIterator;
    typedef ICallbackP1<DigInput*> IDigInputEvent;
    
    class DigInputService: public IRunable {        
        private:
            Task task;
            DigInputList inputs;
            
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
            IDigInputEvent *onChange;
        
        public:
            DigInput(DigInputService *service, uint8_t pin, bool inverted);
            inline bool get() const { return state; }
            inline void setOnChange(IDigInputEvent *event) { onChange = event; }
        private:
            void pinInitialize() const;
            bool pinGet() const;
        
        friend class DigInputService;
    };

}


#endif	

