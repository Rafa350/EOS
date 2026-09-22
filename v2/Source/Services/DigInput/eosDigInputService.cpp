module;


#include "eos.h"
#include "eosEvents.h"


export module Eos.Services.DigInput;


export import Eos.Services.Service;


import Eos.Math;
import Eos.Controllers.Pin;
import Eos.System.Core.Queue;
import Eos.System.Core.Task;
import Eos.System.Collections.IntrusiveForwardList;
import Eos.System.Core.Ticks;


namespace eos {

    // Declaracions forward
    //
    export class DigInput;


    // Declaracions per les llistes
    //
    using DigInputList = IntrusiveForwardList<DigInput, 0>;
    using DigInputListNode = IntrusiveForwardListNode<DigInput, 0>;


    /// \brief Clase que implementa una entrada digital
    ///
    export class DigInput: public DigInputListNode {
    	private:
    		uint32_t const _tag;

    	protected:
    		DigInput(uint32_t tag);

    	public:
    		static constexpr uint32_t nullTag = Math::maxU32;

    	public:
    	    DigInput(const DigInput&) = delete;
    	    DigInput(const DigInput&&) = delete;

    	    DigInput& operator=(const DigInput&) = delete;
    	    DigInput& operator=(const DigInput&&) = delete;

    	    uint32_t getTag() const;
    };


    /// \brief Clase que gestiona una entrada digital
    //
	class DigInputImpl final: public DigInput {
		private:
			static constexpr uint32_t _patternMask    = 0x000000FF;
			static constexpr uint32_t _patternPosEdge = 0x0000007F;
			static constexpr uint32_t _patternNegEdge = 0x00000080;
			static constexpr uint32_t _patternActive  = 0x000000FF;
			static constexpr uint32_t _patternIdle    = 0x00000000;

        private:
			PinDriver * const _drv;
        	uint32_t _pattern;
			bool _value;
			uint32_t _count;

        public:
        	DigInputImpl(PinDriver *drv, uint32_t tag);

        	bool scan();
        	bool getValue() const;
        	uint32_t getCount(bool clear);
    };


    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    export class DigInputService final: public Service {
    	public:
    		using BeforeScanEventRaiser = EventRaiser<DigInputService, NullEventArgs*>;
			using IBeforeScanEvent = BeforeScanEventRaiser::IEvent;
			template <typename Instance_> using BeforeScanEvent = BeforeScanEventRaiser::Event<Instance_>;

			struct InputChangedEventArgs {
				DigInput *input;
				bool value;
			};
			using InputChangedEventRaiser = EventRaiser<DigInputService, InputChangedEventArgs>;
			using IInputChangedEvent = InputChangedEventRaiser::IEvent;
			template <typename Instance_> using InputChangedEvent = InputChangedEventRaiser::Event<Instance_>;

        private:
            static constexpr const char *_serviceName = "DigInputs";
            static constexpr Task::Priority _servicePriority = Task::Priority::normal;
            static constexpr uint32_t _serviceStackDepth = 160;
            static constexpr Ticks _minScanPeriod = Ticks::fromMiliseconds(5);

        private:
    		DigInputList _inputs;
    		InputChangedEventRaiser _inputChangedEventRaiser;
    		BeforeScanEventRaiser _beforeScanEventRaiser;
            Ticks _scanPeriod;

        private:
            void onInputChanged(DigInputImpl *input);
            void beforeScan();

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

            void setScanPeriod(Ticks scanPeriod);

            DigInput * addInput(PinDriver *drv, uint32_t tag);
            DigInput * getInput(uint32_t tag) const;

            bool read(const DigInput *input) const;
            uint32_t getEdges(DigInput *input, bool clear = true) const;

            void enableInputChangedEvent(IInputChangedEvent &event);
            void disableInputChangedEvent();
            void enableBeforeScanEvent(IBeforeScanEvent &event);
            void disableBeforeScanEvent();
    };

}
