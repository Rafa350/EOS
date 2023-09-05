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
                uint16_t time1;
                uint16_t time2;
            };
            using CommandQueue = Queue<Command>;
            using DigOutputList = List<DigOutput*>;
            using DigOutputIterator = DigOutputList::Iterator;

    	public:
    		static constexpr uint32_t minStackSize = 128;

    	private:
            static constexpr unsigned _commandQueueSize = DigOutputService_CommandQueueSize;
            static constexpr uint16_t _minDelay = DigOutputService_MinDelay;
            static constexpr uint16_t _minWidth = DigOutputService_MinWidth;
            CommandQueue _commandQueue;
            DigOutputList _outputs;

        private:
            void cmdClear(DigOutput *output);
            void cmdSet(DigOutput *output);
            void cmdToggle(DigOutput *output);
            void cmdPulse(DigOutput *output, uint16_t width);
            void cmdDelayedSet(DigOutput *output, uint16_t delay);
            void cmdDelayedClear(DigOutput *output, uint16_t delay);
            void cmdDelayedToggle(DigOutput *output, uint16_t delay);
            void cmdDelayedPulse(DigOutput *output, uint16_t delay, uint16_t width);
            void cmdRepeatPulse(DigOutput *output, uint16_t width, uint16_t space);
            void cmdTimeOut(uint16_t time);

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
            void pulse(DigOutput *output, uint16_t width);
            void delayedSet(DigOutput *output, uint16_t delay);
            void delayedClear(DigOutput *output, uint16_t delay);
            void delayedToggle(DigOutput *output, uint16_t delay);
            void delayedPulse(DigOutput *output, uint16_t delay, uint16_t width);
            void repeatPulse(DigOutput *output, uint16_t width, uint16_t space);

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
            DigOutputPinDriver *_drv;
            State _state;
            uint16_t _timeCnt;
            uint16_t _time1;
            uint16_t _time2;

        public:
            DigOutput(DigOutputService *service, const htl::gpio::PinHandler pin);
            DigOutput(DigOutputService *service, DigOutputPinDriver *drv);
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

            inline void delayedSet(uint16_t delay) {
                _service->delayedSet(this, delay);
            }

            inline void delayedClear(uint16_t delay) {
                _service->delayedClear(this, delay);
            }

            inline void delayedToggle(uint16_t delay) {
                _service->delayedToggle(this, delay);
            }

            inline void delayedPulse(uint16_t delay, uint16_t width) {
                _service->delayedPulse(this, delay, width);
            }
            
            inline void repeatPulse(uint16_t width, uint16_t space) {
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
