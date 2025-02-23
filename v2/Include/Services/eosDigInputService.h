#pragma once
#ifndef __eosDigInputService__
#define __eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/eosService.h"
#include "System/eosEvents.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

    class DigInputService;
    class DigInput;


    using DigInputList = IntrusiveForwardList<DigInput, 0>;
    using DigInputListNode = IntrusiveForwardListNode<DigInput, 0>;


    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
    	public:
			enum class NotifyID {
				beforeScan,
				changed,
				initialize
			};
			struct NotifyEventArgs {
				union {
					struct {
						DigInput * const input;
					} changed;
					struct {
						ServiceParams * const params;
					} initialize;
				};
			};
			using ER = NotifyEventRaiser<NotifyID, NotifyEventArgs>;
			using INotifyEvent = ER::IEvent;
			template <typename Instance_> using NotifyEvent = ER::Event<Instance_>;

        private:
    		DigInputList _inputs;
    		ER _erNotify;
            unsigned _scanPeriod;

        private:
            bool scanInputs();
            void notifyChanged(DigInput *input);
            void notifyBeforeScan();
            void notifyInitialize(ServiceParams *params);

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigInputService();
            ~DigInputService();

            void setScanPeriod(unsigned scanPeriod);

            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput *input) const;
            uint32_t getEdges(DigInput *input, bool clear = true) const;

            inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
            	_erNotify.set(event, enabled);
            }
            inline void enableNotifyEvent() {
            	_erNotify.enable();
            }
            inline void disableNotifyEvent() {
            	_erNotify.disable();
            }
            inline void enableNotifyID(NotifyID id) {
            	_erNotify.enable(id);
            }
            inline void disableNotifyID(NotifyID id) {
            	_erNotify.disable(id);
            }
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final: public DigInputListNode {
        public:
            enum class ScanMode {    // Modus d'exploracio de la entrada
                polling,             // -Polling
                interrupt            // -Interrupcio
            };

        private:
            DigInputService *_service;
            PinDriver *_drv;
            ScanMode _scanMode;
            unsigned _pattern;
            struct {
            	unsigned state : 1;
            	unsigned flag : 1;
            	unsigned edges : 30;
            } _pinStatus;

        public:
            DigInput(DigInputService *service, PinDriver *drv);
            ~DigInput();

            inline DigInputService* getService() const {
                return _service;
            }

            inline PinDriver *getPinDriver() const {
            	return _drv;
            }

            inline bool read() const {
                return _service->read(this);
            }

            inline unsigned getEdges(bool clear = false) {
                return _service->getEdges(this, clear);
            }

            inline void setScanMode(ScanMode scanMode) {
                _scanMode = scanMode;
            }

        friend DigInputService;
    };

}


#endif // __eosDigInputService__
