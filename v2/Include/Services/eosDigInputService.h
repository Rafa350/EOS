#ifndef __eosDigInputService__
#define	__eosDigInputService__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Core/eosSemaphore.h"


namespace eos {

    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        private:
            typedef DynamicArray<DigInput*> DigInputList;
            typedef DynamicArray<DigInput*>::Iterator DigInputListIterator;
        public:
            struct InitParams {     // Parametres d'inicialitzacio del servei.
                TMRHandler hTimer;  // -Temporitzador. Si es HAL_TMR_TIMER_NONE utilitza el tick del sistema
            };

        private:
            Semaphore semaphore;
            TMRHandler hTimer;
            DigInputList inputs;

        protected:
            void onInitialize() override;
            void onTerminate() override;
            void onTask();
#if Eos_ApplicationTickEnabled            
            void onTick();
#endif            
        public:
            DigInputService(Application* application, const InitParams& initParams);
            ~DigInputService();
            void addInput(DigInput* input);
            void removeInput(DigInput* input);
            void removeInputs();
            
            bool read(const DigInput* input) const;
            
            void tmrInterruptFunction();
            static void tmrInterruptFunction(TMRHandler handler, void* params);
    };

    /// \brief Clase que implementa una entrada digital
    ///
    class DigInput final {
        public:
            struct EventArgs {
                DigInput* input;
                void* param;
            };
            typedef ICallbackP1<const EventArgs&> IEventCallback;
            struct InitParams {  // Parametres d'inicialitzacio de l'entrada.
                GPIOPort port;   // -El port
                GPIOPin pin;     // -El pin
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
            bool value;
            bool edge;
            
        public:
            DigInput(DigInputService* service, const InitParams& initParams);
            ~DigInput();

            inline DigInputService* getService() const { 
                return service; 
            }
            
            inline bool read() const { 
                return service->read(this); 
            }

        friend DigInputService;
    };

}


#endif	// __eosDigInputService__

