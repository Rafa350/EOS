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
/// \param    message: El missatge a publicar.
/// \param    blockTime: Temps maxim de bloqueig.
///
void eos::MessagePublisher::publish(
	Message *message,
	uint32_t blockTime) {

	if (_service != nullptr)
		_service->publish(this, message, blockTime);
}
