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
    
    /// \brief Clase que implememta el servei de gestio d'entrades digitals
    //
    class DigInputService: private IRunable {        
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

    /// \brief Clase que impementa una entrada digital
    ///
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
            
            /// \brief Obte l'estat actual de la entrada.
            /// \return L'estat de la entrada.
            ///
            inline bool get() const { return state; }
            
            inline void setChangeEvent(IDigInputEvent *event) { evChange = event; }
            
        private:
            bool pinGet() const;
        
        friend class DigInputService;
    };

}


#endif	

