#pragma once
#ifndef __eosMsgSubscriber__
#define __eosMsgSubscriber__


#include "eos.h"
#include "Services/MsgBroker/eosMsgBrokerService.h"


namespace eos {

	/// \brief Representa un subscriptor
	///
	class MsgSubscriber: public MsgSubscriberListNode {
		public:
			struct SubscriptionEventArgs {
				MsgTopic topic;
				MsgPayload *payload;
			};
			using ISubscriptionEvent = eos::ICallbackP2<MsgSubscriber*, SubscriptionEventArgs*>;
			template <typename Instance_> using SubscriptionEvent = eos::CallbackP2<Instance_, MsgSubscriber*, SubscriptionEventArgs*>;

		private:
			MsgBrokerService *_service;
			MsgTopic const _topic;
			ISubscriptionEvent * const _subscriptionEvent;

		protected:
			virtual void onSubscription(MsgPayload *payload);

		public:
			MsgSubscriber(MsgTopic topic, ISubscriptionEvent &event);
			MsgSubscriber(const MsgSubscriber&) = delete;
			MsgSubscriber(const MsgSubscriber&&) = delete;
			virtual ~MsgSubscriber() = default;

			void dispatch(MsgPayload *payload);

			inline bool canAccept(MsgTopic topic) const {
				return (_topic == 0) || (_topic == topic);
			}

			inline MsgBrokerService *getService() const {
				return _service;
			}

		friend void __link(MsgBrokerService *service, MsgSubscriber *subscriber);
	};
}


#endif // __eosMsgSubscriber__
