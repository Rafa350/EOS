#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"
#include "System/eosCallbacks.hpp"


#define EV_DigInput_onChange(cls, instance, method) \
    new eos::CallbackP1<cls, eos::DigInputHandle>(instance, method)


namespace eos {
    
    class DigInput;
    typedef DigInput *DigInputHandle;
    
    class DigInputService;
    typedef DigInputService *DigInputServiceHandle;

    typedef ICallbackP1<DigInputHandle> IDigInputEvent;
    
    class DigInputService: public IRunable {        
        private:
            typedef List<DigInputHandle> DigInputList;
            typedef ListIterator<DigInputHandle> DigInputListIterator;
            
        private:
            Task task;
            DigInputList inputs;
            
        public:
            DigInputService();
            void add(DigInputHandle input);
        private:
            void run();           
    };

    class DigInput {
        private:
            DigInputServiceHandle service;
            uint8_t pin;
            uint32_t pattern;
            bool inverted;
            bool state;
            IDigInputEvent *evChange;
        
        public:
            DigInput(DigInputServiceHandle service, uint8_t pin, bool inverted);
            inline bool get() const { return state; }
            inline void setChangeEvent(IDigInputEvent *event) { evChange = event; }
        private:
            void pinInitialize() const;
            bool pinGet() const;
        
        friend class DigInputService;
    };

}


#endif	

