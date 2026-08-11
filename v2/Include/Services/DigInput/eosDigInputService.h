#pragma once
#ifndef __eosDigInputService__
#define __eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "eosEvents.h"
#include "eosTime.h"
#include "Services/eosService.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

	// Declaracions forward
	//
    class DigInputService;
    class DigInput;
    class PinDriver;

    // Definicio de handlers
    //
    using DigInputHandler = DigInput*;
    using DigInputServiceHandler = DigInputService*;

    // Declaracions per les llistes
    //
    using DigInputList = IntrusiveForwardList<DigInput, 0>;
    using DigInputListNode = IntrusiveForwardListNode<DigInput, 0>;

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput: public DigInputListNode {
    	private:
    		uint32_t const _tag;

    	protected:
    		inline DigInput(uint32_t tag): _tag {tag} { }

    	public:
    	    DigInput(const DigInput&) = delete;
    	    DigInput(const DigInput&&) = delete;

    	    DigInput& operator=(const DigInput&) = delete;
    	    DigInput& operator=(const DigInput&&) = delete;

    	    inline uint32_t getTag() const { return _tag; }
    };

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
    	public:
    		using BeforeScanEventRaiser = EventRaiser<DigInputService, NullEventArgs*>;
			using IBeforeScanEvent = BeforeScanEventRaiser::IEvent;
			template <typename Instance_> using BeforeScanEvent = BeforeScanEventRaiser::Event<Instance_>;

			struct InputChangedEventArgs {
				uint32_t tag;
				bool value;
			};
			using InputChangedEventRaiser = EventRaiser<DigInputService, InputChangedEventArgs>;
			using IInputChangedEvent = InputChangedEventRaiser::IEvent;
			template <typename Instance_> using InputChangedEvent = InputChangedEventRaiser::Event<Instance_>;

        private:
            static constexpr const char *_serviceName = "DigInputs";
            static constexpr rtos::Task::Priority _servicePriority = rtos::Task::Priority::normal;
            static constexpr uint32_t _serviceStackDepth = 160;
            static constexpr Time _minScanPeriod = Time::fromMiliseconds(5);

        private:
    		DigInputList _inputs;
    		InputChangedEventRaiser _inputChangedEventRaiser;
    		BeforeScanEventRaiser _beforeScanEventRaiser;
            Time _scanPeriod;

        private:
            void onInputChanged(DigInput *input);
            void beforeScan();

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigInputService();
            DigInputService(const DigInputService&) = delete;
            DigInputService(const DigInputService&&) = delete;

            DigInputService& operator=(const DigInputService&) = delete;
    	    DigInputService& operator=(const DigInputService&&) = delete;

            void setScanPeriod(Time scanPeriod);

            DigInput * addInput(PinDriver *drv, uint32_t tag);
            DigInput * getInput(uint32_t tag) const;

            bool read(const DigInput *input) const;
            uint32_t getEdges(DigInput *input, bool clear = true) const;

            inline void enableInputChangedEvent(IInputChangedEvent &event) {
            	_inputChangedEventRaiser.enable(event);
            }
            inline void disableInputChangedEvent() {
            	_inputChangedEventRaiser.disable();
            }

            inline void enableBeforeScanEvent(IBeforeScanEvent &event) {
            	_beforeScanEventRaiser.enable(event);
            }
            inline void disableBeforeScanEvent() {
            	_beforeScanEventRaiser.disable();
            }
    };

}


#endif // __eosDigInputService__
