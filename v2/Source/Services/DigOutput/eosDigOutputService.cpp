module;


#include "eos.h"
#include "eosEvents.h"


// Numero maxim d'elements en la cua d'accions
#ifndef DigOutputService_ActionQueueSize
    #define DigOutputService_ActionQueueSize 4
#endif

// Retard minim/maxim en ms
#ifndef DigOutputService_MinDelay
    #define DigOutputService_MinDelay 50
#endif
#ifndef DigOutputService_MaxDelay
    #define DigOutputService_MaxDelay 1000000
#endif

// Amplada minima/maxima en ms
#ifndef DigOutputService_MinPulseWidth
#   define DigOutputService_MinPulseWidth 50
#endif
#ifndef DigOutputService_MinPulseWidth
#   define DigOutputService_MaxPulseWidth 1000000
#endif

// Modus segur (Verificacio complerta de parametres critics, es mes lent i ocupa mes flash)
#define DigOutputService_SafeMode 0


export module Eos.Services.DigOutput;


export import Eos.Services.Service;


import Eos.Math;
import Eos.Ticks;
import Eos.Controllers.Pin;
import Eos.System.Collections.IntrusiveForwardList;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.Queue;
import Eos.System.Core.Task;


namespace eos {

    // Declaracions forward
    //
    export class DigOutput;


    /// \brief Declaracio de les llistes
    ///
    using DigOutputList = IntrusiveForwardList<DigOutput, 0>;
    using DigOutputListNode = IntrusiveForwardListNode<DigOutput, 0>;


    /// \brief Clase que representa una sortida digital individual.
    ///
    export class DigOutput: public DigOutputListNode {
    	private:
    		uint32_t _tag;

    	protected:
    		DigOutput(uint32_t tag);

    	public:
    	    DigOutput(const DigOutput&) = delete;
    	    DigOutput(const DigOutput&&) = delete;

    	    DigOutput& operator=(const DigOutput&) = delete;
    	    DigOutput& operator=(const DigOutput&&) = delete;

    	    uint32_t getTag() const;
    };


	class DigOutputImpl final: public DigOutput {
		public:
			enum class State {
				idle,
				pulse,
				delayedSet,
				delayedClear,
				delayedToggle,
				delayedPulse,
			};

		private:
			PinDriver * const _drv;
			bool _value;
			State _state;
			Ticks _delayEndTime;
			Ticks _pulseEndTime;

		public:
			DigOutputImpl(PinDriver *drv, uint32_t tag);

			bool getValue() const;
			void set();
			void clear();
			void toggle();
			void pulse(Ticks now, Ticks pulse);
			void delayedSet(Ticks now, Ticks delay);
			void delayedClear(Ticks now, Ticks delay);
			void delayedToggle(Ticks now, Ticks delay);
			void delayedPulse(Ticks now, Ticks delay, Ticks pulse);
			void write(bool value);
			void tick();
	};


    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    export class DigOutputService final: public Service {
		public:
			struct OutputChangedEventArgs {
     			DigOutput *output;
				bool value;
			};
			using OutputChangedEventRaiser = EventRaiser<DigOutputService, OutputChangedEventArgs>;
			using IOutputChangedEvent = OutputChangedEventRaiser::IEvent;
			template <typename Instance_> using OutputChangedEvent = OutputChangedEventRaiser::Event<Instance_>;

        private:
            static constexpr const char *_serviceName = "DigOutputs";
            static constexpr Task::Priority _servicePriority = Task::Priority::normal;
            static constexpr uint32_t _serviceStackDepth = 164;
            static constexpr unsigned _actionQueueSize = DigOutputService_ActionQueueSize;

        public:
            static constexpr Ticks minPulseWidth = Ticks::fromMiliseconds(DigOutputService_MinPulseWidth);
            static constexpr Ticks minDelay = Ticks::fromMiliseconds(DigOutputService_MinDelay);

		private:
            enum class ActionID {
                set,
                clear,
                toggle,
                pulse,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                tick
            };
            struct Timing {
                Ticks now;
                Ticks delay;
                Ticks pulse;
            };
            struct Action {
                ActionID id;
                DigOutputImpl *output;
                Timing timing;
            };

            using ActionQueue = Queue<Action>;

    	private:
            DigOutputList _outputs;

            OutputChangedEventRaiser _outputChangedEventRaiser;
            ActionQueue _actionQueue;

        private:
            void processAction(const Action &action);
            void processClear(DigOutputImpl *output);
            void processSet(DigOutputImpl *output);
            void processToggle(DigOutputImpl *output);
            void processPulse(DigOutputImpl *output, const Timing &timing);
            void processDelayedSet(DigOutputImpl *output, const Timing &timing);
            void processDelayedClear(DigOutputImpl *output, const Timing &timing);
            void processDelayedToggle(DigOutputImpl *output, const Timing &timing);
            void processDelayedPulse(DigOutputImpl *output, const Timing &timing);
            void processTick();

            void onOutputChanged(DigOutputImpl *output);

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigOutputService();
            DigOutputService(const DigOutputService&) = delete;
            DigOutputService(const DigOutputService&&) = delete;

            DigOutputService& operator=(const DigOutputService&) = delete;
    	    DigOutputService& operator=(const DigOutputService&&) = delete;

            DigOutput* addOutput(PinDriver *drv, uint32_t tag);
            bool containsOutput(DigOutput *output) const;
            DigOutput *getOutput(uint32_t tag) const;

            inline void enableOutputChangedEvent(IOutputChangedEvent &event) {
            	_outputChangedEventRaiser.enable(event);
            }
            inline void disableOutputChangedEvent() {
            	_outputChangedEventRaiser.disable();
            }

            void set(DigOutput *output, Ticks blockTime);
            void clear(DigOutput *output, Ticks blockTime);
            void write(DigOutput *output, bool pinState, Ticks blockTime);
            void toggle(DigOutput *output, Ticks blockTime);
            void pulse(DigOutput *output, Ticks pulse, Ticks blockTime);
            void delayedSet(DigOutput *output, Ticks delay, Ticks blockTime);
            void delayedClear(DigOutput *output, Ticks delay, Ticks blockTime);
            void delayedToggle(DigOutput *output, Ticks delay, Ticks blockTime);
            void delayedPulse(DigOutput *output, Ticks delay, Ticks pulse, Ticks blockTime);
            bool read(DigOutput *ouput);

            void tick(Ticks blockTime);
            void tickISR();
    };

}
