#include "eos.h"
#include "services/canopen/eos_canopen_dictionary.h"
#include "services/canopen/eos_canopen_service_slave.h"
#include "services/canopen/eos_canopen_protocols.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
CanOpenServiceSlave::CanOpenServiceSlave(
	InitParams const &params) :

	CanOpenService(params),
	_sdoServer(params.dictionary),
	_tpdoTransmitter(params.dictionary) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les dades rebudes, tenint en compte l'estat del node
/// \param    cobid: El COB-ID
/// \param    data: Les dades a procesar
///
void CanOpenServiceSlave::process(
	uint16_t cobid,
	const uint8_t *data) {

	switch (cobid & ~0x007F) {

		// Procesa un SDO nomes en estat preOperacional o operacional
		//
		case COBID::SDO:
			processSDO(data);
			break;

		// Procesa un NMT
		//
		case COBID::NMT:
			processNMT(data);
			break;

		// Procesa un SYNC
		//
		case COBID::SYNC:
			processSYNC();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un SDO
/// \param    data: Les dades a procesar
///
void CanOpenServiceSlave::processSDO(
	const uint8_t *data) {

	auto nodeState = getNodeState();
	if ((nodeState == NodeState::preOperational) || (nodeState == NodeState::operational)) {

		uint8_t response[8];
		if (_sdoServer.process(data, response).isSuccess()) {
			; //TODO: sendFrame(COBID::SDOr | nodeId, response, 8);
			uint16_t index = response[1] | (response[2] << 8);
			uint8_t subIndex = response[3];
			raiseValueChangedNotificationEvent(index, subIndex);
		}
	}
}


// -----------------------------------------------------------------------
/// \brief    Procesa un MNT
/// \param    data: Les dades a procesar
///
void CanOpenServiceSlave::processNMT(
	const uint8_t *data) {

	NodeState nodeState = getNodeState();

	switch (data[0] & NMT0::CS_Msk) {
		case NMT0::CS_START:
			if ((nodeState == NodeState::preOperational) ||
				(nodeState == NodeState::stoped))
				changeNodeState(NodeState::operational);
			break;

		case NMT0::CS_STOP:
			changeNodeState(NodeState::stoped);
			break;

		case NMT0::CS_PREOP:
			changeNodeState(NodeState::preOperational);
			break;

		case NMT0::CS_RST:
			changeNodeState(NodeState::initializing);
			break;

		case NMT0::CS_RSTCOM:
			changeNodeState(NodeState::initializing);
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un SYNC
///
void CanOpenServiceSlave::processSYNC() {
}


void CanOpenServiceSlave::sendTPDO(
	unsigned tpdoId) {

	if (getNodeState() == NodeState::operational) {

		uint8_t response[8];
		if (_tpdoTransmitter.process(tpdoId, response).isSuccess()) {
			; //TODO: sendFrame(COBID::TPDO | nodeId, response, 8);
		}
	}
}
