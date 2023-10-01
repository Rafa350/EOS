#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/eosService.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosQueue.h"


// Numero maxim d'elements en la cua de comandes
#ifndef DigOutputService_CommandQueueSize
    #define DigOutputService_CommandQueueSize 10
#endif

// Retard minim en ms
#ifndef DigOutputService_MinDelay
    #define DigOutputService_MinDelay 50
#endif

// Amplada minima en ms
#ifndef DigOutputService_MinWidth
#define DigOutputService_MinWidth 50
#endif


namespace eos {

    class DigOutput;

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
        private:
            enum class OpCode {
                set,
                clear,
                toggle,
                pulse,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                repeatPulse,
                timeOut
            };
            struct Command {
                OpCode opCode;
                DigOutput *output;
                unsigned time1;
                unsigned time2;
            };

            using CommandQueue = Queue<Command>;
            using DigOutputList = List<DigOutput*>;
            using DigOutputIterator = DigOutputList::Iterator;

    	public:
    		static constexpr uint32_t minStackSize = 128;

    	private:
            static constexpr unsigned _commandQueueSize = DigOutputService_CommandQueueSize;
            static constexpr unsigned _minDelay = DigOutputService_MinDelay;
            static constexpr unsigned _minWidth = DigOutputService_MinWidth;
            unsigned _timeCounter;
            CommandQueue _commandQueue;
            DigOutputList _outputs;

        private:
            void cmdClear(DigOutput *output);
            void cmdSet(DigOutput *output);
            void cmdToggle(DigOutput *output);
            void cmdPulse(DigOutput *output, unsigned width);
            void cmdDelayedSet(DigOutput *output, unsigned delay);
            void cmdDelayedClear(DigOutput *output, unsigned delay);
            void cmdDelayedToggle(DigOutput *output, unsigned delay);
            void cmdDelayedPulse(DigOutput *output, unsigned delay, unsigned width);
            void cmdRepeatPulse(DigOutput *output, unsigned width, unsigned space);
            void cmdTimeOut(unsigned time);

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            DigOutputService();
            ~DigOutputService();

            void addOutput(DigOutput *output);
            void removeOutput(DigOutput *output);
            void removeOutputs();

            void set(DigOutput *output, bool fromISR = false);
            void clear(DigOutput *output, bool fromISR = false);
            void write(DigOutput *output, bool pinState, bool fromISR = false);
            void toggle(DigOutput *output, bool fromISR = false);
            void pulse(DigOutput *output, unsigned width, bool fromISR = false);
            void delayedSet(DigOutput *output, unsigned delay, bool fromISR = false);
            void delayedClear(DigOutput *output, unsigned delay, bool fromISR = false);
            void delayedToggle(DigOutput *output, unsigned delay, bool fromISR = false);
            void delayedPulse(DigOutput *output, unsigned delay, unsigned width, bool fromISR = false);
            void repeatPulse(DigOutput *output, unsigned width, unsigned space, bool fromISR = false);
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

            inline void set(bool fromISR = false) {
                _service->set(this, fromISR);
            }

            inline void clear(bool fromISR = false) {
                _service->clear(this, fromISR);
            }

            inline void write(bool pinState, bool fromISR = false) {
                _service->write(this, pinState, fromISR);
            }

            inline bool read() {
            	return _service->read(this);
            }

            inline void toggle(bool fromISR = false) {
                _service->toggle(this, fromISR);
            }

            inline void pulse(unsigned width, bool fromISR = false) {
                _service->pulse(this, width, fromISR);
            }

            inline void delayedSet(unsigned delay, bool fromISR = false) {
                _service->delayedSet(this, delay, fromISR);
            }

            inline void delayedClear(unsigned delay, bool fromISR = false) {
                _service->delayedClear(this, delay, fromISR);
            }

            inline void delayedToggle(unsigned delay, bool fromISR = false) {
                _service->delayedToggle(this, delay, fromISR);
            }

            inline void delayedPulse(unsigned delay, unsigned width, bool fromISR = false) {
                _service->delayedPulse(this, delay, width, fromISR);
            }
            
            inline void repeatPulse(unsigned width, unsigned space, bool fromISR = false) {
                _service->repeatPulse(this, width, space, fromISR);
            }

            friend DigOutputService;
    };
    
}


#endif // __eosDigOutput__
