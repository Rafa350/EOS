#ifndef __EOS_DIGOUTPUT_HPP
#define	__EOS_DIGOUTPUT_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosTimer.hpp"
#include "System/eosList.hpp"
#include "System/eosQueue.hpp"


namespace eos {
    
    class DigOutput;
    typedef DigOutput *DigOutputHandle;
    
    class DigOutputService;
    typedef DigOutputService *DigOutputServiceHandle;
    
    /// \brief Clase que implemenmta el servei de gestio de sortides digitals.
    ///
    class DigOutputService: private IRunable {
        private:
            enum class Action {
                set,
                clear,
                toggle,
                pulse,
            };
            struct Command {
                Action action;
                DigOutputHandle output;
                unsigned delay;
                unsigned time;
            };
            typedef Queue<Command> CommandQueue;
            typedef List<DigOutputHandle> DigOutputList;
            typedef ListIterator<DigOutputHandle> DigOutputListIterator;
            
        private:
            Task task;
            DigOutputList outputs;     
            CommandQueue commandQueue;
            
        public:
            DigOutputService();
            void add(DigOutputHandle output);
            void remove(DigOutHandle output);
            void set(DigOutputHandle output, bool state);
            void toggle(DigOutputHandle output);
            void pulse(DigOutputHandle output, unsigned time);
        private:
            void run();
            void onTimeout(TimerHandle timer);
            void doClearAction(DigOutputHandle output);
            void doSetAction(DigOutputHandle output);
            void doToggleAction(DigOutputHandle output);
            void doPulseAction(DigOutputHandle output, unsigned time);
    };
    
    /// \brief Clase que implementa una sortida digital.
    ///
    class DigOutput {        
        private:
            DigOutputServiceHandle service;
            TimerHandle timer;
            uint8_t pin;
            bool inverted;
        
        public:
            DigOutput(DigOutputServiceHandle service, uint8_t pin, bool inverted);
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
            /// param time: Durecio del puls en ticks.
            ///
            inline void pulse(unsigned time) { service->pulse(this, time); }
            void delayedSet(unsigned delay, bool state);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);
            
        friend class DigOutputService;
    };
}


#endif	

