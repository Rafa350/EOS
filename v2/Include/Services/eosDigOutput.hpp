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
    
    ///
    /// \brief Clase que implemenmta el servei de gestio de sortides digitals.
    ///
    class DigOutputService: public IRunable {
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
            void outputSet(DigOutputHandle output, bool state);
            void outputToggle(DigOutputHandle output);
            void outputPulse(DigOutputHandle output, unsigned time);
        private:
            void run();
            void onTimeout(TimerHandle timer);
            void doClearAction(DigOutputHandle output);
            void doSetAction(DigOutputHandle output);
            void doToggleAction(DigOutputHandle output);
            void doPulseAction(DigOutputHandle output, unsigned time);
    };
    
    ///
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
            inline void set(bool state) { service->outputSet(this, state); }
            inline void toggle() { service->outputToggle(this); }
            inline void pulse(unsigned time) { service->outputPulse(this, time); }
            void delayedSet(unsigned delay, bool state);
            void delayedToggle(unsigned delay);
            void delayedPulse(unsigned delay, unsigned time);
            
        friend class DigOutputService;
    };
}


#endif	

