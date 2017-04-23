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
    class DigOutput;

    /// \brief Clase que implemenmta el servei de gestio de sortides digitals.
    ///
    class DigOutputService: public Service {
        private:
            enum class Action {
                set,
                clear,
                toggle,
                pulse,
            };
            struct Command {
                Action action;
                DigOutput *output;
                unsigned delay;
                unsigned time;
            };
            typedef Queue<Command> CommandQueue;
            typedef List<DigOutput*> DigOutputList;
            typedef ListIterator<DigOutput*> DigOutputListIterator;

        private:
            DigOutputList outputs;
            CommandQueue commandQueue;

        public:
            DigOutputService(Application *application);
            void add(DigOutput *output);
            void remove(DigOutput *output);
            void set(DigOutput *output);
            void clear(DigOutput *output);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned time);
            void cicle(DigOutput *output, unsigned time1, unsigned time2);

        private:
            void run(Task *task);
            void onTimeout(Timer *timer);
            void doClearAction(DigOutput *output);
            void doSetAction(DigOutput *output);
            void doToggleAction(DigOutput *output);
            void doPulseAction(DigOutput *output, unsigned time);
    };

    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput {
        private:
            DigOutputService *service;
            Timer *timer;
            GPIOPort port;
            GPIOPin pin;

        public:
            DigOutput(DigOutputService *service, GPIOPort port, GPIOPin pin);
            ~DigOutput();
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
            /// \param time: Duracio del puls en ticks.
            ///
            inline void pulse(unsigned time) { service->pulse(this, time); }
            
            /// \brief Genera cicle continu (Inverteix l'estat ciclicament) en la sortida.
            /// \param time1: Duracio del primer semicicle en ticks.
            /// \param time2: Duracio del segon semicicle en ticks.
            ///
            inline void cicle(unsigned time1, unsigned time2) { service->cicle(this, time1, time2); }
            
            void delayedSet(unsigned delay);
            void delayedClear(unsigned delay);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);

        friend DigOutputService;
    };
}


#endif

