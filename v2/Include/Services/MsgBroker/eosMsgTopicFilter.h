#pragma once
#ifndef __eosMsgTopicFilter__
#define __eosMsgTopicFilter__


#include "eos.h"
#include "Services/MsgBroker/eosMsgBrokerService.h"


namespace eos {

	/// \brief Base pels filtres de topics
	//
	class MsgTopicFilter {
		public:
			virtual ~MsgTopicFilter() = default;
			virtual bool canAccept(MsgTopic topic) = 0;
	};

	/// \brief Filtre de coincidencia
	///
	class MsgEqualTopicFilter: public MsgTopicFilter {
		private:
			MsgTopic _topic;
		public:
			MsgEqualTopicFilter(MsgTopic topic) : _topic {topic} {}
			bool canAccept(MsgTopic topic) override { return _topic == topic; }
	};
}


#endif // __eosMsgTopicFilter__

