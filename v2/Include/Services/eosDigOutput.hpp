#ifndef __EOS_DIGOUTPUT_HPP
#define	__EOS_DIGOUTPUT_HPP


#include "eos.hpp"
#include "System/Core/eosQueue.hpp"
#include "System/Collections/eosList.hpp"
#include "Services/eosService.hpp"
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
            void set(DigOutput *output, bool state);
            void toggle(DigOutput *output);
            void pulse(DigOutput *output, unsigned time);

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
            bool inverted;

        public:
            DigOutput(DigOutputService *service, GPIOPort port, GPIOPin pin, bool inverted);
            ~DigOutput();
            bool get() const;

            /// \brief Asigna l'estat de la sortida.
            /// \param state: El nou estat
            ///
            inline void set(bool state) { service->set(this, state); }

            /// \brief Inverteix l'estat de la sortida
            ///
            inline void toggle() { service->toggle(this); }

            /// \brief Genera un puls (Inverteix l'estat momentaneament) en la sortida.
            /// param time: Direcio del puls en ticks.
            ///
            inline void pulse(unsigned time) { service->pulse(this, time); }
            void delayedSet(unsigned delay, bool state);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);

        friend DigOutputService;
    };
}


#endif

