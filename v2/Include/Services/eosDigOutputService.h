#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/Collections/eosArrayList.h"
#include "System/Core/eosQueue.h"


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
                timeOut
            };
            struct Command {
                OpCode opCode;
                DigOutput* output;
                unsigned param1;
                unsigned param2;
            };
            typedef Queue<Command> CommandQueue;
            typedef ArrayList<DigOutput*> DigOutputList;
            typedef ArrayList<DigOutput*>::Iterator DigOutputListIterator;

        private:
            const unsigned commandQueueSize = 5;
            const unsigned minDelay = 50;
            const unsigned minWidth = 50;
            CommandQueue commandQueue;
            TMRTimer timer;
            DigOutputList outputs;

    private:
            static void timerInterrupt(TMRTimer timer, void* params);
            void cmdClear(DigOutput* output);
            void cmdSet(DigOutput* output);
            void cmdToggle(DigOutput* output);
            void cmdPulse(DigOutput* output, unsigned width);
            void cmdDelayedSet(DigOutput* output, unsigned delay);
            void cmdDelayedClear(DigOutput* output, unsigned delay);
            void cmdDelayedToggle(DigOutput* output, unsigned delay);
            void cmdDelayedPulse(DigOutput* output, unsigned delay, unsigned width);
            void cmdTimeOut(unsigned time);

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            DigOutputService(Application* application, TMRTimer timer);
            ~DigOutputService();

            void addOutput(DigOutput* output);
            void removeOutput(DigOutput* output);
            void removeOutputs();
            
            void set(DigOutput* output);
            void clear(DigOutput* output);
            void toggle(DigOutput* output);
            void pulse(DigOutput* output, unsigned width);
            void delayedSet(DigOutput* output, unsigned delay);
            void delayedClear(DigOutput* output, unsigned delay);
            void delayedToggle(DigOutput* output, unsigned delay);
            void delayedPulse(DigOutput* output, unsigned delay, unsigned width);
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
                pulse
            };

            DigOutputService* service;
            GPIOPort port;
            GPIOPin pin;
            GPIOOptions options;
            State state;
            unsigned delayCnt;
            unsigned widthCnt;

        public:
            DigOutput(DigOutputService* service, GPIOPort port, GPIOPin pin, GPIOOptions options = 0);
            ~DigOutput();

            inline DigOutputService* getService() const { 
                return service; 
            }

            inline void set() {
                service->set(this);
            }
            
            inline void clear() {
                service->clear(this);
            }
            
            inline void toggle() {
                service->toggle(this);
            }
            
            inline void pulse(unsigned width) {
                service->pulse(this, width);
            }
            
            inline void delayedSet(unsigned delay) {
                service->delayedSet(this, delay);
            }

            inline void delayedClear(unsigned delay) {
                service->delayedClear(this, delay);
            }

            inline void delayedToggle(unsigned delay) {
                service->delayedToggle(this, delay);
            }

            inline void delayedPulse(unsigned delay, unsigned width) {
                service->delayedPulse(this, delay, width);
            }

            friend DigOutputService;
    };
}


#endif // __eosDigOutput__
