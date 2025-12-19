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


namespace eos {

    class DigOutput;

    using DigOutputList1 = IntrusiveForwardList<DigOutput, 1>;
    using DigOutputListNode1 = IntrusiveForwardListNode<DigOutput, 1>;

    using DigOutputList2 = IntrusiveForwardList<DigOutput, 2>;
    using DigOutputListNode2 = IntrusiveForwardListNode<DigOutput, 2>;

    /// \brief Clase que representa una sortida digital individual.
    ///
    class DigOutput: public DigOutputListNode1, public DigOutputListNode2  {
    	protected:
    		DigOutput() = default;
    };

    class Output;

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
		public:
    		enum class NotificationID {
    			changed
    		};
			struct NotificationEventArgs {
    			NotificationID const id;
    			union {
    				struct {
    					DigOutput * const output;
    					bool value;
    				} changed;
    			};
			};
			using NotificationEventRaiser = EventRaiser<DigOutputService, NotificationEventArgs>;
			using INotificationEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

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
                unsigned time1;
                unsigned time2;
            };

            using ActionQueue = Queue<Action>;

		private:
            static constexpr unsigned _actionQueueSize = DigOutputService_ActionQueueSize;

    	private:
            DigOutputList1 _outputs;

            NotificationEventRaiser _erNotification;
            volatile unsigned _timeCounter;
            ActionQueue _actionQueue;

        private:
            DigOutputService(const DigOutputService&) = delete;

            void actionDispatcher(const Action &action);
            void processClear(Output *output);
            void processSet(Output *output);
            void processToggle(Output *output);
            void processPulse(Output *output, unsigned width);
            void processDelayedSet(Output *output, unsigned delay);
            void processDelayedClear(Output *output, unsigned delay);
            void processDelayedToggle(Output *output, unsigned delay);
            void processDelayedPulse(Output *output, unsigned delay, unsigned width);
            void processTick();

            void raiseChangedNotificationEvent(Output *output);

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigOutputService();
            ~DigOutputService();

            DigOutput* makeOutput(PinDriver *drv);

            void addOutput(DigOutput *output);
            void removeOutput(DigOutput *output);
            void removeOutputs();

            inline void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
            	_erNotification.set(event, enabled);
            }
            inline void enableNotificationEvent() {
            	_erNotification.enable();
            }
            inline void disableNotificationEvent() {
            	_erNotification.disable();
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
