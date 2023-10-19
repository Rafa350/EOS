#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"
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

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
		public:
			struct ChangedEventArgs {
				DigOutput *output;
				bool pinState;
			};
			using IChangedEvent = ICallbackP2<DigOutputService*, ChangedEventArgs&>;
			template <typename instance_> using ChangedEvent = CallbackP2<instance_, DigOutputService*, ChangedEventArgs&>;

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
                repeatPulse,
                tick
            };
            struct Command {
                CommandID id;
                DigOutput *output;
                unsigned time1;
                unsigned time2;
            };

            using CommandQueue = Queue<Command>;
            using OutputList = List<DigOutput*>;
            using OutputIterator = OutputList::Iterator;

		private:
            static constexpr unsigned _commandQueueSize = DigOutputService_CommandQueueSize;
    	public:
    		static constexpr unsigned minStackSize = 128;
            static constexpr unsigned minDelay = DigOutputService_MinDelay;
            static constexpr unsigned minPulseWidth = DigOutputService_MinPulseWidth;

    	private:
            IChangedEvent *_changedEvent;
            bool _changedEventEnabled;
            unsigned _timeCounter;
            unsigned _timeMinLimit;
            CommandQueue _commandQueue;
            OutputList _outputs;

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
            void processRepeatPulse(DigOutput *output, unsigned pulseWidth, unsigned spaceWidth);
            void processTick(unsigned time);

            void setOutput(DigOutput *output);
            void clearOutput(DigOutput *output);
            void toggleOutput(DigOutput *output);

            void notifyChanged(DigOutput *output);
            
            bool hasExpired(unsigned timeLimit) const;

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            DigOutputService();
            ~DigOutputService();

            void addOutput(DigOutput *output);
            void removeOutput(DigOutput *output);
            void removeOutputs();

            void setChangedEvent(IChangedEvent &event, bool enabled = true);
            void enableChangedEvent();
            void disableChangedEvent();

            void set(DigOutput *output);
            void clear(DigOutput *output);
            void write(DigOutput *output, bool pinState);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned width);
            void delayedSet(DigOutput *output, unsigned delay);
            void delayedClear(DigOutput *output, unsigned delay);
            void delayedToggle(DigOutput *output, unsigned delay);
            void delayedPulse(DigOutput *output, unsigned delay, unsigned pulseWidth);
            void repeatPulse(DigOutput *output, unsigned pulseWidth, unsigned spaceWidth);
            bool read(DigOutput *ouput);

            void tmrInterruptFunction();
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final {
        private:
            enum class State {
                idle,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                singlePulse,
                repeatPulse,
                repeatInterval
            };

        public:
            DigOutputService *_service;
            PinDriver *_drv;
            State _state;
            unsigned _timeCnt;
            unsigned _time1;
            unsigned _time2;

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

            inline void repeatPulse(unsigned width, unsigned space) {
                _service->repeatPulse(this, width, space);
            }

            inline bool read() {
            	return _service->read(this);
            }

            friend DigOutputService;
    };
    
}


#endif // __eosDigOutput__
