#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            typedef DynamicArray<DigInput*> DigInputList;
            typedef DynamicArray<DigInput*>::Iterator DigInputListIterator;
        public:
            struct Settings {       // Informacio d'inicialitzacio del servei.
                TMRHandler hTimer;  // -Temporitzador. Si es HAL_TMR_TIMER_NONE utilitza el tick del sistema
            };

        private:
            Semaphore _changes;
            TMRHandler _hTimer;
            DigInputList _inputs;

        protected:
            void onInitialize() override;
            void onTerminate() override;
            void onTask(Task *task) override;
#if Eos_ApplicationTickEnabled
            void onTick();
#endif
        public:
            DigInputService(Application* application, const Settings &settings);
            ~DigInputService();
            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput* input) const;

            void tmrInterruptFunction(uint32_t event);
            static void tmrInterruptFunction(TMRHandler handler, void* params, uint32_t event);
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final {
        public:
            struct EventArgs {
                DigInput* input;
                void* param;
            };
        	typedef ICallbackP1<const EventArgs&> IEventCallback;
            struct Settings {    // Parametres de configuracio de l'entrada.
                GPIOPort port;   // -El port
                GPIOPin pin;     // -El pin
                IEventCallback *eventCallback;
                void* eventParam;
            };

        private:
            DigInputService *_service;
            GPIOPort _port;
            GPIOPin _pin;
            IEventCallback *_eventCallback;
            void *_eventParam;
            uint32_t _pattern;
            bool _value;
            bool _edge;

        public:
            DigInput(DigInputService *service, const Settings &settings);
            ~DigInput();

            inline DigInputService *getService() const {
                return _service;
            }

            inline bool read() const {
                return _service->read(this);
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

