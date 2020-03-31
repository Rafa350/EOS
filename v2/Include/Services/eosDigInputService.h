#ifndef __eosDigInput__
#define	__eosDigInput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosArrayList.h"


namespace eos {

    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            typedef ArrayList<DigInput*> DigInputList;
            typedef ArrayList<DigInput*>::Iterator DigInputListIterator;

        private:
            unsigned weakTime;
            DigInputList inputs;

        protected:
            void onInitialize();
            void onTask();
        public:
            DigInputService(Application* application);
            ~DigInputService();
            void addInput(DigInput* input);
            void removeInput(DigInput* input);
            void removeInputs();
    };

    /// \brief Clase que impementa una entrada digital
    ///
    class DigInput final {
        public:
            struct EventArgs {
                DigInput* input;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IEventCallback;

        private:
            DigInputService* service;
            GPIOPort port;
            GPIOPin pin;
            GPIOOptions options;
            uint8_t pattern;
            bool state;
            IEventCallback* eventCallback;
            
        public:
            DigInput(DigInputService* service, GPIOPort port, GPIOPin pin, GPIOOptions options = 0);
            ~DigInput();

            inline DigInputService* getService() const { 
                return service; 
            }

            /// \brief Obte l'estat actual de la entrada.
            /// \return L'estat de la entrada.
            ///
            inline bool get() const { 
                return state; 
            }

            /// \brief Asigna el event onChange
            /// \param callback: El callback del event
            ///
            inline void setEventCallback(IEventCallback* callback) { 
                eventCallback = callback; 
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInput__

