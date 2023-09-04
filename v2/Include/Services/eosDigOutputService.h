#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HTL/htlGPIO.h"
#include "Services/eosService.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosQueue.h"


// Numero maxim d'elements en la cua de comandes
#ifndef DigOutputService_CommandQueueSize
    #define DigOutputService_CommandQueueSize 5
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
    class DigOutputPinDriver;

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
                unsigned param1;
                unsigned param2;
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

            void set(DigOutput *output);
            void clear(DigOutput *output);
            void write(DigOutput *output, bool value);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned width);
            void delayedSet(DigOutput *output, unsigned delay);
            void delayedClear(DigOutput *output, unsigned delay);
            void delayedToggle(DigOutput *output, unsigned delay);
            void delayedPulse(DigOutput *output, unsigned delay, unsigned width);
            void repeatPulse(DigOutput *output, unsigned width, unsigned space);

            void tmrInterruptFunction();
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final {
        private:
            enum class State: uint8_t {
                idle,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                pulse,
                repeatPulse,
                repeatSpace
            };
        public:
            DigOutputService *_service;
            const htl::gpio::PinHandler _pin;
            State _state;
            unsigned _delayCnt;
            unsigned _widthCnt;

        public:
            DigOutput(DigOutputService *service, const htl::gpio::PinHandler pin);
            DigOutput(DigOutputService *service, const DigOutputPinDriver *pinDriver);
            ~DigOutput();

            inline DigOutputService* getService() const {
                return _service;
            }

            inline void set() {
                _service->set(this);
            }

            inline void clear() {
                _service->clear(this);
            }

            inline void write(bool value) {
                _service->write(this, value);
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

            friend DigOutputService;
    };
    
    /// \brief Clase abstracta que implementa del driver del pin
    ///
    class DigOutputPinDriver {
        public:
            virtual ~DigOutputPinDriver() = default;
            virtual void set() = 0;
            virtual void clear() = 0;
            virtual void toggle() = 0;
    };
    
    /// \brief Clase que implementa del driver del pin amb acces directe a GPIO
    ///
    class DigOutputPinDriver_GPIO final: public DigOutputPinDriver {
        private:
            const htl::gpio::PinHandler _pin;
            
        public:
            DigOutputPinDriver_GPIO(const htl::gpio::PinHandler pin);
            void set() override;
            void clear() override;
            void toggle() override;
    };
}


#endif // __eosDigOutput__
