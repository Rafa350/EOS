#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/Collections/eosVector.h"
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

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
        private:
            enum class OpCode: uint8_t {
                set,
                clear,
                toggle,
                pulse,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                timeOut
            };
            struct Command {
                OpCode opCode;
                DigOutput *output;
                unsigned param1;
                unsigned param2;
            };
            typedef Queue<Command> CommandQueue;
            typedef Vector<DigOutput*> DigOutputList;
            typedef DigOutputList::Iterator DigOutputIterator;

        public:
            struct Settings {       // Informacio d'inicialitzacio del servei
                halTMRHandler hTimer;  // -Temporitzador. Si es NULL utilitza el tick del sistema
            };

        private:
            const unsigned _commandQueueSize = DigOutputService_CommandQueueSize;
            const unsigned _minDelay = DigOutputService_MinDelay;
            const unsigned _minWidth = DigOutputService_MinWidth;
            halTMRHandler _hTimer;
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
            void cmdTimeOut(unsigned time);
        protected:
            void onInitialize() override;
            void onTerminate() override;
            void onTask(Task *task) override;
#if Eos_ApplicationTickEnabled
            void onTick() override;
#endif
        public:
            DigOutputService(Application *application, const Settings &settings);
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

            void tmrInterruptFunction(uint32_t event);
            static void tmrInterruptFunction(halTMRHandler handler, void *params, uint32_t event);
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
                pulse
            };
        public:
            struct Settings {
                halGPIOPort port;
                halGPIOPin pin;
            };

            DigOutputService *_service;
            halGPIOPort _port;
            halGPIOPin _pin;
            State _state;
            unsigned _delayCnt;
            unsigned _widthCnt;

        public:
            DigOutput(DigOutputService *service, const Settings &settings);
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

            friend DigOutputService;
    };
}


#endif // __eosDigOutput__
