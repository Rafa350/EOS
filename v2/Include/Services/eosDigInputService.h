#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"
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

        private:
            Semaphore _changes;
            DigInputList _inputs;

        protected:
            void onInitialize() override;
            void onTask(Task *task) override;
#if Eos_ApplicationTickEnabled
            void onTick();
#endif
        public:
            DigInputService(Application *application);
            ~DigInputService();
            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput *input) const;

            void tmrInterruptFunction();
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

        private:
            DigInputService *_service;
            const htl::GPIOAdapter &_gpio;
            ScanMode _scanMode;
            IEventCallback *_eventCallback;
            void *_eventParam;
            uint32_t _pattern;
            bool _value;
            bool _edge;

        public:
            DigInput(DigInputService *service, const htl::GPIOAdapter &gpio);
            ~DigInput();

            inline DigInputService* getService() const {
                return _service;
            }

            inline bool read() const {
                return _service->read(this);
            }

            inline void setScanMode(ScanMode scanMode) {
                _scanMode = scanMode;
            }

            inline void setCallback(IEventCallback &callback, void *param) {
                _eventCallback = &callback;
                _eventParam = param;
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

