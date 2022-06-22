#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosVector.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

    class DigInputService;
    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            typedef Vector<DigInput*> DigInputList;
            typedef DigInputList::Iterator DigInputIterator;
        public:
            struct Settings {       // Informacio d'inicialitzacio del servei.
                halTMRHandler hTimer;  // -Temporitzador. Si es HAL_TMR_TIMER_NONE utilitza el tick del sistema
            };

        private:
            Semaphore _changes;
            halTMRHandler _hTimer;
            DigInputList _inputs;

        protected:
            void onInitialize() override;
            void onTerminate() override;
            void onTask(Task *task) override;
#if Eos_ApplicationTickEnabled
            void onTick();
#endif
        public:
            DigInputService(Application *application, const Settings &settings);
            ~DigInputService();
            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput *input) const;

            void tmrInterruptFunction(uint32_t event);
            static void tmrInterruptFunction(halTMRHandler handler, void *params, uint32_t event);
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final {
        public:
            struct EventArgs {
                DigInput *input;
                void *param;
            };
        	typedef ICallbackP1<const EventArgs&> IEventCallback;
            enum class ScanMode {    // Modus d'exploracio de la entrada
                polling,             // -Polling
                interrupt            // -Interrupcio
            };
            struct Settings {        // Parametres de configuracio de l'entrada.
                halGPIOPort port;               // -El port
                halGPIOPin pin;                 // -El pin
                ScanMode scanMode;              // Modus d'escaneig de la entrada
                IEventCallback *eventCallback;  // Funcio callback
                void *eventParam;               // Parametres
            };

        private:
            DigInputService *_service;
            halGPIOPort _port;
            halGPIOPin _pin;
            ScanMode _scanMode;
            IEventCallback *_eventCallback;
            void *_eventParam;
            uint32_t _pattern;
            bool _value;
            bool _edge;

        public:
            DigInput(DigInputService *service, const Settings &settings);
            ~DigInput();

            inline DigInputService* getService() const {
                return _service;
            }

            inline bool read() const {
                return _service->read(this);
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

