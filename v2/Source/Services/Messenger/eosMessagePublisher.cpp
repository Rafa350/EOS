#include "eos.h"
#include "Services/Messenger/eosMessagePublisher.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    topicId: Idenfificador del topic.
///
eos::MessagePublisher::MessagePublisher(
	TopicID topicId):

	_service {nullptr},
	_topicId {topicId} {
}


/// ----------------------------------------------------------------------
/// \brief    Publica un element.
/// \param    payload: L'element a publicar.
/// \param    blockTime: Temps maxim de bloqueig.
///
void eos::MessagePublisher::publish(
	void *payload,
	uint32_t blockTime) {

	if (_service != nullptr)
		_service->publish(this, payload, blockTime);
}
