#ifndef __eosFsmService__
#define	__eosFsmService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"


namespace eos {

    class FsmMachine;

    class FsmService final: public Service {
        public:
            enum class EventType {
                acceptMessage
            };
			struct EventArgs {
                EventType type;
                FsmMachine* machine;
			};

        private:
            using MachineList = List<FsmMachine*>;
            using MachineIterator = MachineList::Iterator;
			using IEvent = ICallbackP2<const FsmService*, const EventArgs&>;
			using Event = CallbackP2<FsmService, const FsmService*, const EventArgs&>;

            MachineList _machines;
            IEvent* _event;
            bool _eventEnabled;

        protected:
            void onInitialize() override;
            void onTask() override;

        public:
            FsmService();

            void setEvent(IEvent &event, bool enabled = true);
            inline void enableEvent() {
                _eventEnabled = _event != nullptr;
            }
            void disableEvent() {
                _eventEnabled = false;
            }

            void addMachine(FsmMachine *machine);
            void removeMachine(FsmMachine *machine);
    };

    class FsmMachine {
        private:
            FsmService *_service;

        protected:
            FsmMachine();
            virtual void initialize() = 0;
            virtual void task() = 0;
        public:
            inline FsmService* getService() const {
                return _service;
            }

        friend FsmService;
    };

}


#endif	// __eosFsmService__
