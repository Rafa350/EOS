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
    #define DigOutputService_CommandQueueSize 10
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


    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
		public:
    		enum class NotifyId {
    			changed
    		};
			struct NotifyEventArgs {
    			DigOutputService * const service;
    			NotifyId id;
    			union {
    				struct {
    					DigOutput * const output;
    					bool pinState;
    				} changed;
    			};
			};
			using NotifyEventRaiser = EventRaiser<NotifyId, NotifyEventArgs>;
			using INotifyEvent = NotifyEventRaiser::IEvent;
			template <typename Instance_> using NotifyEvent = NotifyEventRaiser::Event<Instance_>;

		private:
            enum class CommandId {
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
                CommandId id;
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

            NotifyEventRaiser _evRaiser;
            volatile unsigned _timeCounter;
            unsigned _nextTimeLimit;
            CommandQueue _commandQueue;

        private:
            DigOutputService(const DigOutputService&) = delete;

            void processCommand(const Command &command);
            void processClear(DigOutput *output);
            void processSet(DigOutput *output);
            void processToggle(DigOutput *output);
            void processPulse(DigOutput *output, unsigned pulseWidth);
            void processDelayedSet(DigOutput *output, unsigned delay);
            void processDelayedClear(DigOutput *output, unsigned delay);
            void processDelayedToggle(DigOutput *output, unsigned delay);
            void processDelayedPulse(DigOutput *output, unsigned delay, unsigned pulseWidth);
            void processTick();

            void setOutput(DigOutput *output);
            void clearOutput(DigOutput *output);
            void toggleOutput(DigOutput *output);

            void notifyChanged(DigOutput *output);

            void updateNextTimeLimit();
            bool hasExpired(unsigned timeLimit) const;

        protected:
            void initService(ServiceParams &params) override;
            void onExecute() override;

        public:
            DigOutputService();
            ~DigOutputService();

            void addOutput(DigOutput *output);
            void removeOutput(DigOutput *output);
            void removeOutputs();

            inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
            	_evRaiser.set(event, enabled);
            }
            inline void enableNotifyEvent() {
            	_evRaiser.enable();
            }
            inline void disableNotifyEvent() {
            	_evRaiser.disable();
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

            void tmrInterruptFunction();
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final: public DigOutputListNode1, public DigOutputListNode2 {
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
            DigOutputService *_service;  // El servei al que pertany
            PinDriver *_drv;
            State _state;
            unsigned _timeLimit;
            unsigned _timeLimit2;

        public:
            DigOutput(DigOutputService *service, PinDriver *drv);
            ~DigOutput();

            inline DigOutputService* getService() const {
                return _service;
            }

            inline PinDriver *getPinDriver() const {
            	return _drv;
            }

            inline void set() {
                _service->set(this);
            }

            inline void clear() {
                _service->clear(this);
            }

            inline void write(bool pinState) {
                _service->write(this, pinState);
            }

            inline void toggle() {
                _service->toggle(this);
            }

            inline void pulse(unsigned width) {
                _service->pulse(this, width);
            }

            inline void delayedSet(unsigned delay) {
                _service->delayedSet(this, delay);
            }

            inline void delayedClear(unsigned delay) {
                _service->delayedClear(this, delay);
            }

            inline void delayedToggle(unsigned delay) {
                _service->delayedToggle(this, delay);
            }

            inline void delayedPulse(unsigned delay, unsigned width) {
                _service->delayedPulse(this, delay, width);
            }

            inline bool read() {
            	return _service->read(this);
            }

            friend DigOutputService;
    };

}


#endif // __eosDigOutputService__
