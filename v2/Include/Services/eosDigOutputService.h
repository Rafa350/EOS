#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/Collections/eosDynamicArray.h"
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
                DigOutput* output;
                unsigned param1;
                unsigned param2;
            };
            typedef Queue<Command> CommandQueue;
            typedef DynamicArray<DigOutput*> DigOutputList;
            typedef DynamicArray<DigOutput*>::Iterator DigOutputListIterator;
        public:
            struct InitParams {
                TMRTimer timer;
                unsigned period;
            };

        private:
            const unsigned commandQueueSize = DigOutputService_CommandQueueSize;
            const unsigned minDelay = DigOutputService_MinDelay;
            const unsigned minWidth = DigOutputService_MinWidth;
            TMRTimer timer;
            unsigned period;
            CommandQueue commandQueue;
            DigOutputList outputs;

    private:
            static void isrTimerFunction(TMRTimer timer, void* params);
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
            void onTerminate() override;
            void onTask() override;
            void onTick() override;
            
        public:
            DigOutputService(Application* application, const InitParams& initParams);
            ~DigOutputService();

            void addOutput(DigOutput* output);
            void removeOutput(DigOutput* output);
            void removeOutputs();
            
            void set(DigOutput* output);
            void clear(DigOutput* output);
            void write(DigOutput* output, bool value);
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
            enum class State: uint8_t {
                idle,
                delayedSet,
                delayedClear,
                delayedToggle,
                delayedPulse,
                pulse
            };
        public:
            struct InitParams {
                GPIOPort port;
                GPIOPin pin;
            };

            DigOutputService* service;
            GPIOPort port;
            GPIOPin pin;
            State state;
            unsigned delayCnt;
            unsigned widthCnt;

        public:
            DigOutput(DigOutputService* service, const InitParams& initParams);
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
            
            inline void write(bool value) {
                service->write(this, value);
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
