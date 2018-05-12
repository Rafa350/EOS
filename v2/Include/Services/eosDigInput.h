#ifndef __eosDigInput__
#define	__eosDigInput__


#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"


namespace eos {


    class Application;
    class Task;
    class DigInput;

    typedef struct {

    } DigInputServiceInitializeInfo;

    typedef struct {
        uint8_t port;
        uint8_t pin;
    } DigInputInitializeInfo;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService: public Service {
        private:
            typedef List<DigInput*> DigInputList;
            typedef ListIterator<DigInput*> DigInputListIterator;

        private:
            DigInputList inputs;

        public:
            DigInputService(Application *application, const DigInputServiceInitializeInfo *info);
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
            uint8_t port;
            uint8_t pin;
            uint32_t pattern;
            bool state;
            IDigInputEvent *evChange;

        public:
            DigInput(DigInputService *service, const DigInputInitializeInfo *info);
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

