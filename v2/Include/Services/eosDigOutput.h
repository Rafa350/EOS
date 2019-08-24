#ifndef __eosDigOutput__
#define	__eosDigOutput__


#include "eos.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"
#include "hal/halTMR.h"


namespace eos {

    class Application;
    class DigOutput;

    struct  DigOutputServiceConfiguration {
    	TMRTimer timer;
    };

    struct DigOutputConfiguration {
        GPIOPort port;
        GPIOPin pin;
        bool initState;
        bool openDrain;
    };

    /// \brief Clase que implementa el servei de gestio de sortides digitals.
    ///
    class DigOutputService final: public Service {
        private:
            typedef List<DigOutput*> DigOutputList;
            typedef ListIterator<DigOutput*> DigOutputListIterator;
            
        private:
            DigOutputList outputs;
            TMRTimer timer;
            
        private:
            static void timerInterrupt(TMRTimer timer, void *pParams);
            void timeOut();
            
        protected:
            void onInitialize();
            void onTask();

        public:
            DigOutputService(Application *pApplication);
            DigOutputService(Application *pApplication, const DigOutputServiceConfiguration &configuration);
            ~DigOutputService();

            void addOutput(DigOutput *pOutput);
            void removeOutput(DigOutput *pOutput);
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

        private:
            DigOutputService *pService;
            GPIOPort port;
            GPIOPin pin;
            GPIOOptions options;
            State state;
            unsigned delayCnt;
            unsigned widthCnt;
            
        private:
            void initialize();
            void timeOut();

        public:
            DigOutput(DigOutputService *pService, const DigOutputConfiguration &configuration);
            ~DigOutput();

            DigOutputService *getService() const { return pService; }

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
