#pragma once
#ifndef __eosDigOutputService__
#define __eosDigOutputService__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/eosService.h"
#include "System/eosEvents.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


// Numero maxim d'elements en la cua de comandes
#ifndef DigOutputService_CommandQueueSize
    #define DigOutputService_CommandQueueSize 4
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


namespace eos {

    class DigOutput;

    using DigOutputList1 = IntrusiveForwardList<DigOutput, 1>;
    using DigOutputListNode1 = IntrusiveForwardListNode<DigOutput, 1>;

    using DigOutputList2 = IntrusiveForwardList<DigOutput, 2>;
    using DigOutputListNode2 = IntrusiveForwardListNode<DigOutput, 2>;

    /// \brief Clase que representa una sortida digital individual
    ///
    class DigOutput: public DigOutputListNode1, public DigOutputListNode2  {
    	protected:
    		DigOutput() = default;
    };

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
		public:
    		enum class NotifyID {
    			changed
    		};
			struct NotifyEventArgs {
    			union {
    				struct {
    					DigOutput * const output;
    				} changed;
    			};
			};
			using ER = NotifyEventRaiser<NotifyID, NotifyEventArgs>;
			using INotifyEvent = ER::IEvent;
			template <typename Instance_> using NotifyEvent = ER::Event<Instance_>;

		private:
            enum class CommandID {
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
            struct Command {
                CommandID id;
                DigOutput *output;
                unsigned time1;
                unsigned time2;
            };

            using CommandQueue = Queue<Command>;

		private:
            static constexpr unsigned _commandQueueSize = DigOutputService_CommandQueueSize;

    	private:
            DigOutputList1 _outputs;
            DigOutputList2 _pending;

            ER _erNotify;
            volatile unsigned _timeCounter;
            unsigned _nextTimeLimit;
            CommandQueue _commandQueue;

        private:
            DigOutputService(const DigOutputService&) = delete;

            void commandDispatcher(const Command &command);
            void processClear(DigOutput *output);
            void processSet(DigOutput *output);
            void processToggle(DigOutput *output);
            void processPulse(DigOutput *output, unsigned width);
            void processDelayedSet(DigOutput *output, unsigned delay);
            void processDelayedClear(DigOutput *output, unsigned delay);
            void processDelayedToggle(DigOutput *output, unsigned delay);
            void processDelayedPulse(DigOutput *output, unsigned delay, unsigned width);
            void processTick();

            void setOutput(DigOutput *output);
            void clearOutput(DigOutput *output);
            void toggleOutput(DigOutput *output);

            void notifyChanged(DigOutput *output);

            void updateNextTimeLimit();
            bool hasExpired(unsigned timeLimit) const;

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigOutputService();
            ~DigOutputService();

            DigOutput* makeOutput(PinDriver *pinDrv);

            void addOutput(DigOutput *output);
            void removeOutput(DigOutput *output);
            void removeOutputs();

            inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
            	_erNotify.set(event, enabled);
            }
            inline void enableNotifyEvent() {
            	_erNotify.enable();
            }
            inline void disableNotifyEvent() {
            	_erNotify.disable();
            }

            void set(DigOutput *output);
            void clear(DigOutput *output);
            void write(DigOutput *output, bool pinState);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned width);
            void delayedSet(DigOutput *output, unsigned delay);
            void delayedClear(DigOutput *output, unsigned delay);
            void delayedToggle(DigOutput *output, unsigned delay);
            void delayedPulse(DigOutput *output, unsigned delay, unsigned pulseWidth);
            bool read(DigOutput *ouput);

            void tick(unsigned blockTime);
            void tickISR();
    };
}


#endif // __eosDigOutputService__
