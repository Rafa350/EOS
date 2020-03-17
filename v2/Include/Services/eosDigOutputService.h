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
                delayedPulse
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
            void timeOut();
            void cmdClear(DigOutput* output);
            void cmdSet(DigOutput* output);
            void cmdToggle(DigOutput* output);
            void cmdPulse(DigOutput* output, unsigned width);
            void cmdDelayedPulse(DigOutput* output, unsigned delay, unsigned width);

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
            void delayedPulse(DigOutput* output, unsigned delay, unsigned width);
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final {
        private:
            enum class State {
                idle,
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

            void initialize();
            void timeOut();

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

            inline void delayedPulse(unsigned delay, unsigned width) {
                service->delayedPulse(this, delay, width);
            }

            friend DigOutputService;
    };
}


#endif // __eosDigOutput__
