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

    /// \brief Clase que implementa una entrada digitals
    //
    class DigInput: public DigInputListNode {
    	protected:
    		DigInput() = default;
    };

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

            DigInput* makeInput(PinDriver* pinDrv);

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
}


#endif // __eosDigInputService__
