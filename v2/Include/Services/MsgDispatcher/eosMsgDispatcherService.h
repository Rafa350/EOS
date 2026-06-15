#pragma once
#ifndef __eosMsgDispatcherService__
#define __eosMsgDispatcherService__


#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class Time;

	/// \brief Base de tots els missatges
	//
	class Message {
		public:
			virtual ~Message() = default;
	};
	template <typename Message_>
	struct MessageID;

	struct MsgListener;
    using MsgListenerList = IntrusiveForwardList<MsgListener, 0>;
    using MsgListenerListNode = IntrusiveForwardListNode<MsgListener, 0>;

	/// \brief Base dels listeners dels missatges
    //
	class MsgListener: public MsgListenerListNode {
		public:
    		uint32_t const typeId;

		protected:
			virtual void dispatchImpl(Message *message) = 0;

		public:
			MsgListener(uint32_t typeId);
			MsgListener(const MsgListener&) = delete;
			MsgListener(const MsgListener&&) = delete;
			virtual ~MsgListener() = default;

			inline void dispatch(Message *message) {
				dispatchImpl(message);
			}
	};

	/// \brief Listener espeficic per un missatge en particular
	///
	template <typename Message_>
	class MsgListenerX: public MsgListener {
		public:
			using IEvent = ICallbackP1<Message_*>;
			template <typename Instance_> using Event = CallbackP1<Instance_, Message_*>;

		private:
			IEvent * _event;

		protected:
			inline void dispatchImpl(Message *message) override {
				_event->execute(static_cast<Message_*>(message));
			}

		public:
			MsgListenerX(IEvent &event):
				MsgListener(MessageID<Message_>::typeId) {
				_event = &event;
			}
	};

	/// \brief Servei de gestio del bus de missatges
	///
	class MsgDispatcherService: public Service {
		public:
			struct DispatchFinishedEventArgs {
				Message *message;
			};
			using IDispatchFinishedEvent = ICallbackP2<MsgDispatcherService*, DispatchFinishedEventArgs*>;
			template <typename Instance_> using DispatchFinishedEvent = CallbackP2<Instance_, MsgDispatcherService*, DispatchFinishedEventArgs*>;

		private:
			enum class ActionID {
				addListener,
				postMessage
			};
		    struct Action {
				ActionID id;
				union {
					struct {
						MsgListener *listener;
					} addListener;
					struct {
						uint32_t typeId;
						Message *message;
					} postMessage;
				};
			};
			using ActionQueue = Queue<Action>;

		private:
			MsgListenerList _listenerList;
			ActionQueue _actionQueue;
			IDispatchFinishedEvent *_dispatchFinishedEvent;

		private:
			void postImpl(uint32_t typeId, Message *message, Time blockTime);
			void addListenerImpl(MsgListener *lister, Time blockTime);

		protected:
			void onExecute() override;
			void onDispatchFinished(Message *message);

		public:
			MsgDispatcherService();

			template <typename Message_>
			void addListener(MsgListenerX<Message_> *listener, Time blockTime) {
				addListenerImpl(listener, blockTime);
			}

			template <typename Message_>
			void post(Message_ *message, Time blockTime) {
				postImpl(MessageID<Message_>::typeId, message, blockTime);
			}

			inline void setDispatchFinishedEvent(IDispatchFinishedEvent &event) {
				_dispatchFinishedEvent = &event;
			}
			inline void clearDispatchFinishedEvent() {
				_dispatchFinishedEvent = nullptr;
			}
	};
}


#endif // __eosMsgDispatcherService__
