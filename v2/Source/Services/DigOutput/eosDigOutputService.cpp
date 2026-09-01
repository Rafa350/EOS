module;


#include "eosEvents.h"
#include "eosTime.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosTask.h"
#include "Services/eosService.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


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


import Eos.Math;


export namespace eos {

    class DigOutput;

    using DigOutputList = IntrusiveForwardList<DigOutput, 0>;
    using DigOutputListNode = IntrusiveForwardListNode<DigOutput, 0>;

    /// \brief Clase que representa una sortida digital individual.
    ///
    class DigOutput: public DigOutputListNode {
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

    class DigOutputImpl;

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
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
            static constexpr rtos::Task::Priority _servicePriority = rtos::Task::Priority::normal;
            static constexpr uint32_t _serviceStackDepth = 164;
            static constexpr unsigned _actionQueueSize = DigOutputService_ActionQueueSize;

        public:
            static constexpr Time minPulseWidth = Time::fromMiliseconds(DigOutputService_MinPulseWidth);
            static constexpr Time minDelay =Time::fromMiliseconds(DigOutputService_MinDelay);

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
            struct Action {
                ActionID id;
                DigOutputImpl *output;
                Time time1;
                Time time2;
            };

            using ActionQueue = Queue<Action>;

    	private:
            DigOutputList _outputs;

            OutputChangedEventRaiser _outputChangedEventRaiser;
            Time _timeCounter;
            ActionQueue _actionQueue;

        private:
            void processAction(const Action &action);
            void processClear(DigOutputImpl *output);
            void processSet(DigOutputImpl *output);
            void processToggle(DigOutputImpl *output);
            void processPulse(DigOutputImpl *output, Time width);
            void processDelayedSet(DigOutputImpl *output, Time delay);
            void processDelayedClear(DigOutputImpl *output, Time delay);
            void processDelayedToggle(DigOutputImpl *output, Time delay);
            void processDelayedPulse(DigOutputImpl *output, Time delay, Time width);
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

            void set(DigOutput *output, Time blockTime);
            void clear(DigOutput *output, Time blockTime);
            void write(DigOutput *output, bool pinState, Time blockTime);
            void toggle(DigOutput *output, Time blockTime);
            void pulse(DigOutput *output, Time width, Time blockTime);
            void delayedSet(DigOutput *output, Time delay, Time blockTime);
            void delayedClear(DigOutput *output, Time delay, Time blockTime);
            void delayedToggle(DigOutput *output, Time delay, Time blockTime);
            void delayedPulse(DigOutput *output, Time delay, Time pulseWidth, Time blockTime);
            bool read(DigOutput *ouput);

            void tick(Time blockTime);
            void tickISR();
    };
}


namespace eos {

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
			Time _delayEndTime;
			Time _pulseEndTime;

		private:
			static bool hasExpired(Time time, Time endTime);

		public:
			DigOutputImpl(PinDriver *drv, uint32_t tag);

			bool getValue() const;
			void set();
			void clear();
			void toggle();
			void pulse(Time time, Time pulse);
			void delayedSet(Time time, Time delay);
			void delayedClear(Time time, Time delay);
			void delayedToggle(Time time, Time delay);
			void delayedPulse(Time time, Time delay, Time pulse);
			void write(bool value);
			void tick(Time time);
	};

}
