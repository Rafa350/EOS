#ifndef __eosDigOutput__
#define	__eosDigOutput__


#include "eos.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"
#include "hal/halTMR.h"

#include <stdint.h>


namespace eos {

    class Application;
    class Task;
    class DigOuputService;
    class DigOutput;

    typedef struct {
    	TMRTimer timer;
    } DigOutputServiceInitializeInfo;

    typedef struct {
        GPIOPort port;
        GPIOPin pin;
        bool initState;
        bool openDrain;
    } DigOutputInitializeInfo ;

    /// \brief Clase que implemenmta el servei de gestio de sortides digitals.
    ///
    class DigOutputService: public Service {
        private:
    	    class Implementation;

        private:
            Implementation *pImpl;

        public:
            DigOutputService(Application *application, const DigOutputServiceInitializeInfo *pInfo);
            ~DigOutputService();

            void add(DigOutput *output);
            void remove(DigOutput *output);
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput {
    	private:
    		class Implementation;

        private:
            DigOutputService *service;
            Implementation *pImpl;

        public:
            DigOutput(DigOutputService *service, const DigOutputInitializeInfo *pInfo);
            ~DigOutput();

            DigOutputService *getService() const { return service; }
            Implementation *getImpl() const { return pImpl; }

            bool get() const;
            void set();
            void clear();
            void toggle();
            void pulse(unsigned width);
            void cicle(unsigned width1, unsigned width2);
            void delayedSet(unsigned delay);
            void delayedClear(unsigned delay);
            void delayedToggle(unsigned delay);
            inline void delayedPulse(unsigned delay, unsigned width);
    };
}


#endif // __eosDigOutput__
