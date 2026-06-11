#pragma once
#ifndef __eosMsgPublisher__
#define __eosMsgPublisher__


#include "eos.h"
#include "Services/MsgBroker/eosMsgBrokerService.h"


namespace eos {

	class MsgPublisher: public MsgPublisherListNode {
		private:
			MsgBrokerService *_service;

		public:
			MsgPublisher();
			virtual ~MsgPublisher() = default;

			bool publish(MsgTopic topic, MsgPayload *payload, uint32_t blockTime);

			inline MsgBrokerService *getService() const {
				return _service;
			}

			virtual void done(MsgPayload *payload) = 0;

        friend void __link(MsgBrokerService *service, MsgPublisher *publisher);
	};

}


#endif // __eosMsgPublisher__
