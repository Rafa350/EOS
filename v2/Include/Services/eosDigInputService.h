#pragma once
#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

    class DigInputService;
    class DigInput;

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

            htl::gpio::PinState read(const DigInput *input) const;

            void tmrInterruptFunction();
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final {
        public:
            struct ChangedEventArgs {
                DigInput *input;
                htl::gpio::PinState pinState;
            };
        	using IChangedEvent = ICallbackP1<const ChangedEventArgs&>;
        	template <typename instance_> using ChangedEvent = CallbackP1<instance_, const ChangedEventArgs&>;

            enum class ScanMode {    // Modus d'exploracio de la entrada
                polling,             // -Polling
                interrupt            // -Interrupcio
            };

        private:
            DigInputService *_service;
            const htl::gpio::PinHandler _pin;
            ScanMode _scanMode;
            IChangedEvent *_changedEvent;
            bool _changedEventEnabled;
            uint32_t _pattern;
            htl::gpio::PinState _pinState;
            bool _edge;

        public:
            DigInput(DigInputService *service, htl::gpio::PinHandler pin);
            ~DigInput();

            inline DigInputService* getService() const {
                return _service;
            }

            inline htl::gpio::PinState read() const {
                return _service->read(this);
            }

            inline void setScanMode(ScanMode scanMode) {
                _scanMode = scanMode;
            }

            inline void setChangedEvent(IChangedEvent &event, bool enabled = true) {
                _changedEvent = &event;
                _changedEventEnabled = enabled;
            }

            inline bool isChangedEventEnabled() const {
            	return (_changedEvent != nullptr) && _changedEventEnabled;
            }

            inline void enableChangeEvent() {
                _changedEventEnabled = true;
            }

            inline void disableChangeEvent() {
                _changedEventEnabled = false;
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

