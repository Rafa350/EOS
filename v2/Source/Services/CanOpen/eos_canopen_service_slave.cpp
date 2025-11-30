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
	_sdoServer(params.dictionary) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les dades rebudes, tenint en compte l'estat del node
/// \param    cobid: El COB-ID
/// \param    data: Les dades a procesar
///
void CanOpenServiceSlave::process(
	uint16_t cobid,
	const uint8_t *data) {

	uint8_t nodeId = cobid & 0x007F;
	NodeState nodeState = getNodeState();

	switch (cobid & ~0x07F) {

		// Procesa un SDO nomes en estat preOperacional o operacional
		//
		case COBID::SDO:
			if (nodeId == getNodeId() &&
				((nodeState == NodeState::preOperational) || (nodeState == NodeState::operational)))
				processSDO(data);
			break;

		// Procesa un NMT
		//
		case COBID::NMT:
			if ((nodeId == getNodeId()) || (nodeId == 0))
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

	uint8_t response[8];

	if (_sdoServer.process(data, response).isSuccess()) {
		; //TODO: sendFrame(COBID::SDOr | nodeId, response, 8);
		uint16_t index = response[1] | (response[2] << 8);
		uint8_t subIndex = response[3];
		raiseValueChangedNotificationEvent(index, subIndex);
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
/*
	NodeState nodeState = getNodeState();

	if (nodeState == NodeState::operational) {

		// Comprova si hi han TPDO per enviar
		//
		for (unsigned tpdoId = 0; tpdoId < 4; tpdoId++) {

			// Comprova les entrades 0x1800 0x02
			//
			auto entryId = _dictionary->find(0x1800 | (tpdoId & 0x03), 0x02);
			if (entryId != (unsigned) -1) {

				// Existeix una entrada pel TPDO.
				//
				uint8_t value;
				if (_dictionary->readU8(entryId, value)) {

					// Comprova si es sincrona, alesores genera un TPDO
					//
					if ((value >= 1) && (value <= 240)) {

						uint8_t txData[8];

						buildTPDO(tpdoId, txData, sizeof(txData));
						sendFrame(tpdoId | _nodeId, txData, sizeof(txData));
					}
				}
			}
		}
	}
	*/
}


