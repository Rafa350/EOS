#ifndef __EOS_DIGINPUT_HPP
#define	__EOS_DIGINPUT_HPP


#include "eos.hpp"
#include "System/Core/eosCallbacks.hpp"
#include "System/Collections/eosList.hpp"
#include "Services/eosService.hpp"


namespace eos {
    
    
    class Application;
    class Task;
    class DigInput;
    

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService: Public Service {        
        private:
            typedef List<DigInput*> DigInputList;
            typedef ListIterator<DigInput*> DigInputListIterator;
            
        private:
            DigInputList inputs;
            
        public:
            DigInputService(Application *application);
            void add(DigInput *input);
            void remove(DigInput *input);
            
        private:
            void run(Task *task);           
    };

    /// \brief Clase que impementa una entrada digital
    ///
    class DigInput {
        private:
            typedef ICallbackP1<DigInput*> IDigInputEvent;
            
        private:
            DigInputService *service;
            uint8_t pin;
            uint32_t pattern;
            bool inverted;
            bool state;
            IDigInputEvent *evChange;
        
        public:
            DigInput(DigInputService *service, uint8_t pin, bool inverted);
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
            void setChangeEvent(cls *instance, void (cls::*method)(DigInput *input)) {                
                evChange = new CallbackP1<cls, DigInput*>(instance, method);
            }
            
        private:
            bool pinGet() const;
        
        friend void DigInputService::add(DigInput *input);
        friend void DigInputService::remove(DigInput *input);
    };

}


#endif	

