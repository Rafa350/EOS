#include "eos.h"
#include "Services/MsgBroker/eosMsgPublisher.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    topic: Idenfificador de la publicacio.
///
eos::MsgPublisher::MsgPublisher() :
	_service {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Publica una publicacio.
/// \param    topic: El topic de la publicacio.
/// \param    payload: El contingut de la publicacio.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool eos::MsgPublisher::publish(
	MsgTopic topic,
	MsgPayload payload,
	uint32_t blockTime) {

	return _service->publish(this, topic, payload, blockTime);
}
