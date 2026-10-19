export module Eos.Services.DigInput;

import Eos.Events;
import Eos.Math;
import Eos.Controllers.Pin;
import Eos.System.Core.Queue;
import Eos.System.Core.Task;
import Eos.System.Collections.IntrusiveForwardList;
import Eos.Services.Service;
import Eos.System.Core.Ticks;
import Eos.Types;


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
    		UInt32 const _tag;

    	protected:
    		DigInput(UInt32 tag);

    	public:
    		static constexpr UInt32 nullTag = Math::maxU32;

    	public:
    	    DigInput(const DigInput&) = delete;
    	    DigInput(const DigInput&&) = delete;

    	    DigInput& operator=(const DigInput&) = delete;
    	    DigInput& operator=(const DigInput&&) = delete;

    	    UInt32 getTag() const;
    };


    /// \brief Clase que gestiona una entrada digital
    //
	class DigInputImpl final: public DigInput {
		private:
			static constexpr UInt32 _patternMask    = 0x000000FF;
			static constexpr UInt32 _patternPosEdge = 0x0000007F;
			static constexpr UInt32 _patternNegEdge = 0x00000080;
			static constexpr UInt32 _patternActive  = 0x000000FF;
			static constexpr UInt32 _patternIdle    = 0x00000000;

        private:
			PinDriver * const _drv;
        	UInt32 _pattern;
			bool _value;
			UInt32 _count;

        public:
        	DigInputImpl(PinDriver *drv, UInt32 tag);

        	bool scan();
        	bool getValue() const;
        	UInt32 getCount(bool clear);
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
            static constexpr UInt32 _serviceStackDepth = 160;
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

            DigInput * addInput(PinDriver *drv, UInt32 tag);
            DigInput * getInput(UInt32 tag) const;

            bool read(const DigInput *input) const;
            UInt32 getEdges(DigInput *input, bool clear = true) const;

            void enableInputChangedEvent(IInputChangedEvent &event);
            void disableInputChangedEvent();
            void enableBeforeScanEvent(IBeforeScanEvent &event);
            void disableBeforeScanEvent();
    };

}
