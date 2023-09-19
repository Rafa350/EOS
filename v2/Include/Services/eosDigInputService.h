#pragma once
#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

    class DigInputService;
    class DigInput;
    class DigInputDriver;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
    	public:
    		static constexpr uint32_t minStackSize = 100;

        private:
            typedef List<DigInput*> DigInputList;
            typedef DigInputList::Iterator DigInputIterator;

        private:
            Semaphore _changes;
            DigInputList _inputs;

        private:
            bool scanInputs();

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            DigInputService();
            ~DigInputService();

            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput *input) const;
            uint32_t readPulses(const DigInput *input, bool clear = true) const;

            void tmrInterruptFunction();
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final {
        public:
            struct ChangedEventArgs {
                bool state;
                uint32_t pulses;
            };
        	using IChangedEvent = ICallbackP2<DigInput*, ChangedEventArgs&>;
        	template <typename instance_> using ChangedEvent = CallbackP2<instance_, DigInput*, ChangedEventArgs&>;

            enum class ScanMode {    // Modus d'exploracio de la entrada
                polling,             // -Polling
                interrupt            // -Interrupcio
            };

        private:
            DigInputService *_service;
            PinDriver *_drv;
            ScanMode _scanMode;
            IChangedEvent *_changedEvent;
            bool _changedEventEnabled;
            uint32_t _pattern;
            bool _pinState;
            uint32_t _pinPulses;
            bool _edge;

        public:
            DigInput(DigInputService *service, PinDriver *drv);
            ~DigInput();

            inline DigInputService* getService() const {
                return _service;
            }

            inline bool read() const {
                return _service->read(this);
            }

            inline uint32_t readPulses(bool clear = false) const {
                return _service->readPulses(this, clear);
            }

            inline void setScanMode(ScanMode scanMode) {
                _scanMode = scanMode;
            }

            inline void setChangedEvent(IChangedEvent &event, bool enabled = true) {
                _changedEvent = &event;
                _changedEventEnabled = enabled;
            }

            inline void enableChangeEvent() {
                _changedEventEnabled = _changedEvent != nullptr;
            }

            inline void disableChangeEvent() {
                _changedEventEnabled = false;
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

