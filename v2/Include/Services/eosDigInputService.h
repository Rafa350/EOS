#ifndef __eosDigInput__
#define	__eosDigInput__


#include "eos.h"
#include "HAL/halGPIO.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"


// Nom del servei
#ifndef eosDigInputService_ServiceName 
#define eosDigInputService_ServiceName "DigInputService"
#endif

// Prioritat d'execucio del servei
#ifndef eosDigInputService_TaskPriority
#define eosDigInputService_taskPriority taskPriority::normal
#endif

// Tamany del stack del servei
#ifndef eosDigInputService_StackSize
#define eosDigInputService_StackSize 512
#endif


namespace eos {

    class DigInput;

    /// \brief Clase que implementa el servei de gestio d'entrades digitals
    //
    class DigInputService final: public Service {
        public:
            struct Configuration {
                const ServiceConfiguration *serviceConfiguration;
            };

        private:
            typedef List<DigInput*, 10> DigInputList;

        private:
            int weakTime;
            DigInputList inputs;

        protected:
            void onInitialize();
            void onTask();

        public:
            DigInputService(Application *application);
            DigInputService(Application *application, const DigInputService::Configuration *configuration);
            ~DigInputService();
            
            void addInput(DigInput *input);
            void removeInput(DigInput *input);
            void removeInputs();
    };

    /// \brief Clase que impementa una entrada digital
    ///
    class DigInput final {
        public:            
            struct Configuration {
                GPIOPort port;
                GPIOPin pin;
                GPIOOptions options;
            };
            struct EventArgs {
                DigInput* input;
            };

        private:
            typedef ICallbackP1<const EventArgs&> IDigInputEventCallback;

        private:
            DigInputService *service;
            GPIOPort port;
            GPIOPin pin;
            GPIOOptions options;
            uint32_t pattern;
            bool state;
            IDigInputEventCallback *changeEventCallback;
            
        private:
            void initialize();

        public:
            DigInput(DigInputService *service, const Configuration *configuration);
            DigInput(DigInputService *service, GPIOPort port, GPIOPin pin, GPIOOptions options);
            ~DigInput();

            /// \brief Obte l'estat actual de la entrada.
            /// \return L'estat de la entrada.
            ///
            inline bool get() const { return state; }

            /// \brief Asigna el event onChange
            /// \param callback: El callback del event
            ///
            inline void setChangeEventCallback(IDigInputEventCallback *callback) {
                changeEventCallback = callback;
            }

        friend DigInputService;
    };
}


#endif	// __eosDigInput__

