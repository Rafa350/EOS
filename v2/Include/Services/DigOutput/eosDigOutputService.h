#pragma once
#ifndef __eosDigOutputService__
#define __eosDigOutputService__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
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


namespace eos {

    class DigOutput;

    using DigOutputList = IntrusiveForwardList<DigOutput, 0>;
    using DigOutputListNode = IntrusiveForwardListNode<DigOutput, 0>;

    /// \brief Clase que representa una sortida digital individual.
    ///
    class DigOutput: public DigOutputListNode {
    	private:
    		uint32_t _tag;

    	protected:
    		DigOutput(uint32_t tag): _tag {tag} {}

    	public:
    	    DigOutput(const DigOutput&) = delete;
    	    DigOutput(const DigOutput&&) = delete;

    	    DigOutput& operator=(const DigOutput&) = delete;
    	    DigOutput& operator=(const DigOutput&&) = delete;

    	    inline uint32_t getTag() const { return _tag; }
    };

    class Output;

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
		public:
			struct OutputChangedEventArgs {
     			uint32_t tag;
				bool value;
			};
			using IOutputChangedEvent = ICallbackP2<DigOutputService*, OutputChangedEventArgs*>;
			template <typename Instance_> using OutputChangedEvent = CallbackP2<Instance_, DigOutputService*, OutputChangedEventArgs*>;

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
                Output *output;
                uint32_t time1;
                uint32_t time2;
            };

            using ActionQueue = Queue<Action>;

		private:
            static constexpr unsigned _actionQueueSize = DigOutputService_ActionQueueSize;

    	private:
            DigOutputList _outputs;

            IOutputChangedEvent * _outputChangedEvent;
            volatile uint32_t _timeCounter;
            ActionQueue _actionQueue;

        private:
            void processAction(const Action &action);
            void processClear(Output *output);
            void processSet(Output *output);
            void processToggle(Output *output);
            void processPulse(Output *output, uint32_t width);
            void processDelayedSet(Output *output, uint32_t delay);
            void processDelayedClear(Output *output, uint32_t delay);
            void processDelayedToggle(Output *output, uint32_t delay);
            void processDelayedPulse(Output *output, uint32_t delay, uint32_t width);
            void processTick();

            void onOutputChanged(Output *output);

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

            inline void setOutputChangedEvent(IOutputChangedEvent &event) {
            	_outputChangedEvent = &event;
            }
            inline void clearOutputChangedEvent() {
            	_outputChangedEvent = nullptr;
            }

            void set(DigOutput *output);
            void clear(DigOutput *output);
            void write(DigOutput *output, bool pinState);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, uint32_t width);
            void delayedSet(DigOutput *output, uint32_t delay);
            void delayedClear(DigOutput *output, uint32_t delay);
            void delayedToggle(DigOutput *output, uint32_t delay);
            void delayedPulse(DigOutput *output, uint32_t delay, uint32_t pulseWidth);
            bool read(DigOutput *ouput);

            void tick(uint32_t blockTime);
            void tickISR();
    };
}


#endif // __eosDigOutputService__
