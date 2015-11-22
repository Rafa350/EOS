#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class DigInput;
    typedef DigInput *DigInputHandle;
    
    class DigInputService;
    typedef DigInputService *DigInputServiceHandle;

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
            typedef ICallbackP1<DigInputHandle> IDigInputEvent;
            
        private:
            DigInputServiceHandle service;
            uint8_t pin;
            uint32_t pattern;
            bool inverted;
            bool state;
            IDigInputEvent *evChange;
        
        public:
            DigInput(DigInputServiceHandle service, uint8_t pin, bool inverted);
            ~DigInput();
            
            /// \brief Obte l'estat actual de la entrada.
            /// \return L'estat de la entrada.
            ///
            inline bool get() const { return state; }
            
            /// \brief Asigna el event onChange
            /// \param instance: La instancia
            /// \param method: El metode
            ///
            template <class cls> 
            void setChangeEvent(cls *instance, void (cls::*method)(DigInputHandle input)) {
                
                evChange = new CallbackP1<cls, DigInputHandle>(instance, method);
            }
            
        private:
            bool pinGet() const;
        
        friend class DigInputService;
    };

}


#endif	

