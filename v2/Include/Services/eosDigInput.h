#ifndef __EOS_DIGINPUT_H
#define	__EOS_DIGINPUT_H


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"


namespace eos {
    
    
    class Application;
    class Task;
    class DigInput;
    

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService: public Service {        
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
            GPIOPort port;
            GPIOPin pin;
            uint32_t pattern;
            bool state;
            IDigInputEvent *evChange;
        
        public:
            DigInput(DigInputService *service, GPIOPort port, GPIOPin pin);
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
        
        friend DigInputService;
    };

}


#endif	

