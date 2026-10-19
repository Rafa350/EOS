export module Eos.Services.MsgDispatcher;


import Eos.Callbacks;
import Eos.Services.Service;
import Eos.System.Collections.IntrusiveForwardList;
import Eos.System.Core.Queue;
import Eos.System.Core.Ticks;
import Eos.Types;


export namespace eos {

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
		private:
    		UInt32 const _typeId;

		protected:
			virtual void dispatchImpl(Message *message) = 0;

		public:
			MsgListener(UInt32 typeId);
			MsgListener(const MsgListener&) = delete;
			MsgListener(const MsgListener&&) = delete;
			virtual ~MsgListener() = default;

			inline void dispatch(Message *message) {
				dispatchImpl(message);
			}

			inline UInt32 getTypeId() const {
				return _typeId;
			}
	};

	/// \brief Listener especific per un missatge en particular
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
			static constexpr UInt32 _commandQueueSize = 10;

		private:
			enum class CommandID {
				addListener,
				postMessage
			};
		    struct Command {
				CommandID id;
				union {
					struct {
						MsgListener *listener;
					} addListener;
					struct {
						UInt32 typeId;
						Message *message;
					} postMessage;
				};
			};
			using CommandQueue = Queue<Command>;

		private:
			MsgListenerList _listenerList;
			CommandQueue _commandQueue;
			IDispatchFinishedEvent *_dispatchFinishedEvent;

		private:
			void postImpl(UInt32 typeId, Message *message, Ticks blockTime);
			void addListenerImpl(MsgListener *lister, Ticks blockTime);

		protected:
			void onExecute() override;
			void onDispatchFinished(Message *message);

		public:
			MsgDispatcherService();

			template <typename Message_>
			void addListener(MsgListenerX<Message_> *listener, Ticks blockTime) {
				addListenerImpl(listener, blockTime);
			}

			template <typename Message_>
			void post(Message_ *message, Ticks blockTime) {
				postImpl(MessageID<Message_>::typeId, message, blockTime);
			}

			void setDispatchFinishedEvent(IDispatchFinishedEvent &event) {
				_dispatchFinishedEvent = &event;
			}

			void clearDispatchFinishedEvent() {
				_dispatchFinishedEvent = nullptr;
			}
	};
}
