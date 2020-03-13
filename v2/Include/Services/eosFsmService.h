#ifndef __eosFsmService__
#define	__eosFsmService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosArrayList.h"


namespace eos {

    class Application;
    class FsmMachine;
    
    typedef unsigned Message;

    class FsmService final: public Service {
        public:
            enum class EventType {
                acceptMessage
            };
			struct EventArgs {
                EventType type;
                FsmService* service;  
                FsmMachine* machine;
			};                        

        private:
            typedef ArrayList<FsmMachine*> MachineList;
            typedef ArrayList<FsmMachine*>::Iterator MachineListIterator;
			typedef ICallbackP1<const EventArgs&> IEventCallback;

            MachineList machines;
            IEventCallback* eventCallback;

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            FsmService(Application* application);
            
            inline void setEventCallback(IEventCallback* callback) { 
                eventCallback = callback; 
            }
            
            void addMachine(FsmMachine* machine);
            void removeMachine(FsmMachine *machine);
    };
        
    class FsmMachine {
        private:
            FsmService* service;
            
        protected:
            FsmMachine();
            virtual void initialize() = 0;
            virtual void task() = 0;
        public:
            inline FsmService* getService() const { 
                return service; 
            }
            
        friend FsmService;
    };

}


#endif	// __eosFsmService__
