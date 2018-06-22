#ifndef __EOS_DIGOUTPUT_H
#define	__EOS_DIGOUTPUT_H


#include "eos.h"
#include "System/Core/eosQueue.h"
#include "System/Collections/eosList.h"
#include "Services/eosService.h"
#include "HAL/halGPIO.h"

#include <stdint.h>


namespace eos {

    class Application;
    class Task;
    class Timer;
    class DigOuputService;
    class DigOutput;

    typedef struct {

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
            enum class Action {
                set,
                clear,
                toggle,
                pulse,
				delayedSet,
				delayedClear,
				delayedToggle,
				delayedPulse
            };
            struct Command {
                Action action;
                DigOutput *output;
                unsigned delay;
                unsigned width;
            };
            typedef Queue<Command> CommandQueue;
            typedef List<DigOutput*> DigOutputList;
            typedef ListIterator<DigOutput*> DigOutputListIterator;

        private:
            DigOutputList outputs;
            CommandQueue commandQueue;

        public:
            DigOutputService(Application *application, const DigOutputServiceInitializeInfo *info);
            void add(DigOutput *output);
            void remove(DigOutput *output);
            void set(DigOutput *output);
            void clear(DigOutput *output);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned width);
            void delayedPulse(DigOutput *output, unsigned delay, unsigned width);
            void cicle(DigOutput *output, unsigned width1, unsigned width2);
            
        protected:
            void onLoop();

        private:
            void onTimeout(Timer *timer);
            void startTimer(DigOutput *output, unsigned time);
            void stopTimer(DigOutput *output);
            void doClearCommand(Command *command);
            void doSetCommand(Command *command);
            void doToggleCommand(Command *command);
            void doPulseCommand(Command *command);
            void doDelayedPulseCommand(Command *command);
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput {
    	public:
    		enum class State {
    			Done,
				Delay,
				Pulse
    		};

        private:
            DigOutputService *service;
            Timer *timer;
            unsigned time;
            State state;
            uint8_t port;
            uint8_t pin;

        public:
            DigOutput(DigOutputService *service, const DigOutputInitializeInfo *info);
            ~DigOutput();

            /// \brief Obte l'estat del port.
            bool get() const;

            /// \brief Asigna l'estat actiu a la sortida.
            ///
            inline void set() { service->set(this); }

            /// \brief Asigna l'estat inactiu a la sortida.
            ///
            inline void clear() { service->clear(this); }

            /// \brief Inverteix l'estat de la sortida
            ///
            inline void toggle() { service->toggle(this); }

            /// \brief Genera un puls (Inverteix l'estat momentaneament) en la sortida.
            /// \param width: Duracio del puls en ticks.
            ///
            inline void pulse(unsigned width) { service->pulse(this, width); }

            /// \brief Genera cicle continu (Inverteix l'estat ciclicament) en la sortida.
            /// \param width1: Amplada del primer semicicle en ticks.
            /// \param width2: Amplada del segon semicicle en ticks.
            ///
            inline void cicle(unsigned width1, unsigned width2) { service->cicle(this, width1, width2); }

            void delayedSet(unsigned delay);
            void delayedClear(unsigned delay);
            void delayedToggle(unsigned delay);

            /// \brief Genera un puls retardat (Inverteix l'estat momentaneament) en la sortida.
            /// \param delay: Retart en ticks
            /// \param width: Amplada en ticks.
            ///
            inline void delayedPulse(unsigned delay, unsigned width) { service->delayedPulse(this, delay, width); }

            State getState() const;

        friend DigOutputService;
    };
}


#endif

