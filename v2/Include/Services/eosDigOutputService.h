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

    class IDigOutput;

    using DigOutputList1 = IntrusiveForwardList<IDigOutput, 1>;
    using DigOutputListNode1 = IntrusiveForwardListNode<IDigOutput, 1>;

    using DigOutputList2 = IntrusiveForwardList<IDigOutput, 2>;
    using DigOutputListNode2 = IntrusiveForwardListNode<IDigOutput, 2>;

    /// \brief Clase que representa una sortida digital individual
    ///
    class IDigOutput: public DigOutputListNode1, public DigOutputListNode2  {
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
    					IDigOutput * const output;
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
                IDigOutput *output;
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
            void processClear(IDigOutput *output);
            void processSet(IDigOutput *output);
            void processToggle(IDigOutput *output);
            void processPulse(IDigOutput *output, unsigned width);
            void processDelayedSet(IDigOutput *output, unsigned delay);
            void processDelayedClear(IDigOutput *output, unsigned delay);
            void processDelayedToggle(IDigOutput *output, unsigned delay);
            void processDelayedPulse(IDigOutput *output, unsigned delay, unsigned width);
            void processTick();

            void setOutput(IDigOutput *output);
            void clearOutput(IDigOutput *output);
            void toggleOutput(IDigOutput *output);

            void notifyChanged(IDigOutput *output);

            void updateNextTimeLimit();
            bool hasExpired(unsigned timeLimit) const;

        protected:
            void onInitialize(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigOutputService();
            ~DigOutputService();

            IDigOutput* makeOutput(PinDriver *drv);

            void addOutput(IDigOutput *output);
            void removeOutput(IDigOutput *output);
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

            void set(IDigOutput *output);
            void clear(IDigOutput *output);
            void write(IDigOutput *output, bool pinState);
            void toggle(IDigOutput *output);
            void pulse(IDigOutput *output, unsigned width);
            void delayedSet(IDigOutput *output, unsigned delay);
            void delayedClear(IDigOutput *output, unsigned delay);
            void delayedToggle(IDigOutput *output, unsigned delay);
            void delayedPulse(IDigOutput *output, unsigned delay, unsigned pulseWidth);
            bool read(IDigOutput *ouput);

            void tick(unsigned blockTime);
            void tickISR();
    };

    // TODO: fer aquesta clase interna
    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final: public IDigOutput {
        private:
            enum class State {
                idle,
                pulse,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
            };

        public:
            PinDriver *_drv;
            State _state;
            unsigned _timeLimit;
            unsigned _timeLimit2;

        public:
            DigOutput(PinDriver *drv);

            inline PinDriver *getPinDriver() const {
            	return _drv;
            }

            friend DigOutputService;
    };

}


#endif // __eosDigOutputService__
