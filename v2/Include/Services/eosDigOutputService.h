#ifndef __eosDigOutput__
#define	__eosDigOutput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/Collections/eosArrayList.h"


namespace eos {

    class DigOutput;

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
        private:
            typedef ArrayList<DigOutput*> DigOutputList;
            typedef ArrayList<DigOutput*>::Iterator DigOutputListIterator;

            TMRTimer timer;
            DigOutputList outputs;

            static void timerInterrupt(TMRTimer timer, void* params);
            void timeOut();

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            DigOutputService(Application* application, TMRTimer timer);
            ~DigOutputService();

            void addOutput(DigOutput* output);
            void removeOutput(DigOutput* output);
            void removeOutputs();
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput final {
        private:
            enum class State {
                Idle,
                DelayedPulse,
                Pulse
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

            inline DigOutputService* getService() const { return service; }

            bool get() const;
            void set();
            void clear();
            void toggle();
            void pulse(unsigned width);
            void cicle(unsigned width1, unsigned width2);
            void delayedSet(unsigned delay);
            void delayedClear(unsigned delay);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned width);

        friend DigOutputService;
    };

}


#endif // __eosDigOutput__
