#ifndef __eosDigInput__
#define	__eosDigInput__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosArrayList.h"
#include "System/Core/eosQueue.h"


namespace eos {

    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            enum class OpCode {
                null,
                posEdge,
                negEdge
            };
            struct Command {
                OpCode opCode;
                DigInput* input;
            };
            typedef Queue<Command> CommandQueue;
            typedef ArrayList<DigInput*> DigInputList;
            typedef ArrayList<DigInput*>::Iterator DigInputListIterator;
        public:
            struct InitParams {  // Parametres d'inicialitzaci0.
                TMRTimer timer;  // -Temporitzador
                unsigned period; // -Periode en ms
            };

        private:
            const unsigned commandQueueSize = 10;
            TMRTimer timer;
            unsigned period;
            DigInputList inputs;
            CommandQueue commandQueue;

        private:
            static void isrTimerFunction(TMRTimer timer, void* params);
        protected:
            void onInitialize();
            void onTask();
            void onTick();
        public:
            DigInputService(Application* application, const InitParams& initParams);
            ~DigInputService();
            void addInput(DigInput* input);
            void removeInput(DigInput* input);
            void removeInputs();
    };

    /// \brief Clase que impementa una entrada digital
    ///
    class DigInput final {
        public:
            struct EventArgs {
                DigInput* input;
                void* param;
            };
            typedef ICallbackP1<const EventArgs&> IEventCallback;
            struct InitParams {
                GPIOPort port;
                GPIOPin pin;
                IEventCallback* eventCallback;
                void* eventParam;
            };

        private:
            DigInputService* service;
            GPIOPort port;
            GPIOPin pin;
            IEventCallback* eventCallback;
            void* eventParam;
            uint32_t pattern;
            bool state;
            
        public:
            DigInput(DigInputService* service, const InitParams& initParams);
            ~DigInput();

            inline DigInputService* getService() const { 
                return service; 
            }
            
            bool get() const;

        friend DigInputService;
    };

}


#endif	// __eosDigInput__

