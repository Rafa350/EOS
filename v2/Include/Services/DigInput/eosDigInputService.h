#pragma once
#ifndef __eosDigInputService__
#define __eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosEvents.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

    class DigInputService;
    class DigInput;
    class PinDriver;

    using DigInputList = IntrusiveForwardList<DigInput, 0>;
    using DigInputListNode = IntrusiveForwardListNode<DigInput, 0>;

    /// \brief Clase que implementa una entrada digitals
    //
    class DigInput: public DigInputListNode {
    	private:
    		unsigned const _tag;

    	protected:
    		DigInput(unsigned tag) : _tag {tag} {}

    	public:
    	    DigInput(const DigInput&) = delete;
    	    DigInput(const DigInput&&) = delete;

    	    DigInput& operator=(const DigInput&) = delete;
    	    DigInput& operator=(const DigInput&&) = delete;

    	    inline unsigned getTag() const { return _tag; }
    };

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
    	public:
			enum class NotificationID {
				beforeScan,
				changed,
				initialize
			};
			struct NotificationEventArgs {
				NotificationID const id;
				union {
					struct {
						DigInput * const input;
						bool value;
					} changed;
					struct {
						ServiceParams * const params;
					} initialize;
				};
			};
			using NotificationEventRaiser = EventRaiser<DigInputService, NotificationEventArgs>;
			using INotificationEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

        private:
    		DigInputList _inputs;
    		NotificationEventRaiser _erNotification;
            unsigned _scanPeriod;

        private:
            void raiseChangedNotificationEvent(DigInput *input);
            void raiseBeforeScanNotificationEvent();
            void raiseInitializeNotificationEvent(ServiceParams *params);

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigInputService();
            DigInputService(const DigInputService&) = delete;
            DigInputService(const DigInputService&&) = delete;
            ~DigInputService();

            DigInputService& operator=(const DigInputService&) = delete;
    	    DigInputService& operator=(const DigInputService&&) = delete;

            void setScanPeriod(unsigned scanPeriod);

            DigInput* addInput(PinDriver *drv, unsigned tag = 0);
            void removeInput(DigInput *input);
            void removeInputs();

            bool read(const DigInput *input) const;
            unsigned getEdges(DigInput *input, bool clear = true) const;

            void setNotificationEvent(INotificationEvent &event, bool enabled = true);
            void enableNotifyEvent();
            void disableNotifyEvent();
    };
}


#endif // __eosDigInputService__
