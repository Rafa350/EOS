#ifndef __eosMessengerService__
#define __eosMessengerService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosQueue.h"
#include "System/Collections/eosVector.h"


namespace eos {

	class IMessageBus {
        protected:
            virtual ~IMessageBus() = default;
		public:
			virtual void processLoop() = 0;
	};

	template <typename message_>
	class MessageBus final: public IMessageBus {
		private:
			using IMessageBusCallback = ICallbackP1<const message_&>;
			using CallbackList = Vector<const IMessageBusCallback*>;
			using MessageQueue = Queue<message_>;

		private:
			CallbackList _callbacks;
			MessageQueue _messages;

		protected:
			void processLoop() override {
                while (true) {
                    message_ message;
                    if (_messages.pop(message, (unsigned)-1))
                        for (auto callback: _callbacks)
                            callback->execute(message);
                }
			}

		public:
			MessageBus(int capacity) :
				_messages(capacity) {

			}

			bool send(const message_ &message, unsigned blockTime) {
				return _messages.push(message, blockTime);
			}

            void subscribe(const IMessageBusCallback &callback) {
                _callbacks.pushBack(&callback);
            }
	};

    class MessengerService final: public Service {
    	private:
			using MessageBusList = Vector<IMessageBus*>;
            using BusTaskEventCallback = CallbackP1<MessengerService, const Task::EventArgs&>;

    	private:
			MessageBusList _busses;
            BusTaskEventCallback _busTaskEventCallback;

    	protected:
            void onInitialize() override;
            void busTaskEventHandler(const Task::EventArgs&);
        public:
            MessengerService(Application *application);
            void addMessageBus(IMessageBus *bus);
    };
}


#endif // __eosMessangerService__
