#ifndef __eosDigInput__
#define	__eosDigInput__


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"


namespace eos {

    class DigInput;

    struct DigInputServiceConfiguration {
        ServiceConfiguration serviceConfiguration;
    };

    struct DigInputConfiguration {
        GPIOPort port;
        GPIOPin pin;
    };

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            typedef List<DigInput*> DigInputList;
            typedef ListIterator<DigInput*> DigInputListIterator;

        private:
            unsigned weakTime;
            DigInputList inputs;

        protected:
            void onInitialize();
            void onTask();

        public:
            DigInputService(Application *pApplication);
            DigInputService(Application *pApplication, const DigInputServiceConfiguration &configuration);
            void addInput(DigInput *pInput);
            void removeInput(DigInput *pInput);
            void removeInputs();
    };

    /// \brief Clase que impementa una entrada digital
    ///
    class DigInput final {
        private:
            typedef ICallbackP1<DigInput*> IDigInputEvent;

        private:
            DigInputService *pService;
            GPIOPort port;
            GPIOPin pin;
            uint32_t pattern;
            bool state;
            IDigInputEvent *evChange;
            
        private:
            void initialize();

        public:
            DigInput(DigInputService *pService, const DigInputConfiguration &configuration);
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


#endif	// __eosDigInput__
