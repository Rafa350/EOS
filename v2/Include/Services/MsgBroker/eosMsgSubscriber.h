#pragma once
#ifndef __eosMsgSubscriber__
#define __eosMsgSubscriber__


#include "eos.h"
#include "Services/MsgBroker/eosMsgBrokerService.h"


namespace eos {

	struct MsgSubscriberEventArgs {
		MsgTopic topic;
		void *payload;
	};
	using IMsgSubscriberEvent = eos::ICallbackP2<MsgSubscriber*, MsgSubscriberEventArgs*>;
	template <typename Instance_> using MsgSubscriberEvent = eos::CallbackP2<Instance_, MsgSubscriber*, MsgSubscriberEventArgs*>;

	class MsgSubscriber: public MsgSubscriberListNode {
		private:
			MsgBrokerService *_service;
			MsgTopic const _topic;
			IMsgSubscriberEvent * const _event;

		public:
			MsgSubscriber(MsgTopic topic, IMsgSubscriberEvent &event);

			void dispatch(MsgPayload payload);

			inline bool canAccept(MsgTopic topic) const {
				return _topic == topic;
			}

			inline MsgBrokerService *getService() const {
				return _service;
			}

		friend void __link(MsgBrokerService *service, MsgSubscriber *subscriber);
	};
}


#endif // __eosMsgSubscriber__
