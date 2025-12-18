#include "eos.h"
#include "services/canopen/eos_canopen_dictionary.h"
#include "services/canopen/eos_canopen_service_master.h"
#include "services/canopen/eos_canopen_protocols.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
CanOpenMasterService::CanOpenMasterService(
	InitParams const &params) :

	CanOpenService {params} {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les dades rebudes, tenint en compte l'estat del node
/// \param    cobid: El COB-ID
/// \param    data: Les dades a procesar
/// \param    dataLen: La longitut de les dades
///
void CanOpenMasterService::processFrame(
	uint16_t cobid,
	const uint8_t *data,
	unsigned dataLen) {

	switch (cobid & 0xFF80) {
		case COBID::Heartbeat:
			processHeartbeat(cobid & 0x007F, data[0]);
			break;

		case COBID::TPDO1:
		case COBID::TPDO2:
		case COBID::TPDO3:
		case COBID::TPDO4:
			processTPDOFrame(cobid, data, dataLen);
			break;

		default:
			CanOpenService::processFrame(cobid, data, dataLen);
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una trama TPDO.
/// \param    nodeId: El node origen del missatge.
/// \param    state: L'estat del node.
///
void CanOpenMasterService::processTPDOFrame(
	uint16_t cobid,
	const uint8_t *data,
	unsigned dataLen) {

	raiseTPDOReceivedEvent(cobid, data, dataLen);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges Heartbeat.
/// \param    nodeId: El node origen del missatge.
/// \param    state: L'estat del node.
///
void CanOpenMasterService::processHeartbeat(
	uint8_t nodeId,
	uint8_t state) {

	// Comprova si es un boot-up
	//
	if (state == 0x7F) {

		// El posa en modus operacional
		//
		nmtStartNode(nodeId, 200);
	}
}


/// ----------------------------------------------------------------------
/// \brief    SDO expedited download. Transfereix dades a un servidor SDO
/// \param    nodeId: El node destinatari.
/// \param    index: Index.
/// \param    subIndex: Subindex.
/// \param    value: El valor.
/// \param    timeout: Temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::sdoDownload(
	unsigned nodeId,
	uint16_t index,
	uint8_t subIndex,
	uint32_t value,
	unsigned timeout) {

	uint8_t data[8];
	data[0] = SDO0::CCS_DN | SDO0::E_EXP | SDO0::S_SIZE | SDO0::SIZE_4;
	data[1] = index & 0xFF;
	data[2] = index >> 8;
	data[3] = subIndex;
	data[4] = value & 0xFF;
	data[5] = (value >> 8) & 0xFF;
	data[6] = (value >> 16) & 0xFF;
	data[7] = (value >> 24) & 0xFF;

	return sendFrame(COBID::SDO, data, sizeof(data), timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Solicita dades a un servidor SDO
/// \param    nodeId: El node destinatari.
/// \param    index: Index.
/// \param    subIndex: Subindex.
/// \param    timeout: Tamps maxim d'espera
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::sdoUpload(
	unsigned nodeId,
	uint16_t index,
	uint8_t subIndex,
	unsigned timeout) {

	uint8_t data[8];
	data[0] = SDO0::CCS_UP;
	data[1] = index & 0xFF;
	data[2] = index >> 8;
	data[3] = subIndex;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;

	return sendFrame(COBID::SDO, data, sizeof(data), timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Posa un node en estat 'operational'.
/// \param    nodeId: Node destinatari.
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::nmtStartNode(
	uint8_t nodeId,
	unsigned timeout) {

	uint8_t data[2] = {
		0x01,
		nodeId & 0x7F
	};

	return sendFrame(COBID::NMT, data, sizeof(data), timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Posa un node en estat 'stoped'
/// \param    nodeId: Node destinatati
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::nmtStopNode(
	uint8_t nodeId) {

	uint8_t data[2] = {
		0x02,
		nodeId & 0x7F
	};

	return sendFrame(COBID::NMT, data, sizeof(data), 15);
}


/// ----------------------------------------------------------------------
/// \brief    Posa un node en estat 'pre-operational'.
/// \param    nodeId: Node destinatati
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::nmtEnterPreOperational(
	uint8_t nodeId) {

	uint8_t data[2] = {
		0x80,
		nodeId & 0x7F
	};

	return sendFrame(COBID::NMT, data, sizeof(data), 15);
}


/// ----------------------------------------------------------------------
/// \brief    Reinicia el node.
/// \param    nodeId: Node destinatati
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::nmtResetNode(
	uint8_t nodeId) {

	uint8_t data[2] = {
		0x81,
		nodeId & 0x7F
	};

	return sendFrame(COBID::NMT, data, sizeof(data), 15);
}


/// ----------------------------------------------------------------------
/// \brief    Reinicia nomes les comunicacions del node.
/// \param    nodeId: Node destinatati
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::nmtResetCommunication(
	uint8_t nodeId) {

	uint8_t data[2] = {
		0x82,
		nodeId & 0x7F
	};

	return sendFrame(COBID::NMT, data, sizeof(data), 15);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge SYNC
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
Result CanOpenMasterService::sync(
	unsigned timeout) {

	uint32_t options;
	if (readU32(0x1005, 0x00, options) && htl::bits::isSet(options, (uint32_t)(1 << 30)))
		return sendFrame(COBID::SYNC, nullptr, 0, (unsigned) -1);
	else
		return Result::ErrorCodes::error;
}


/// ---------------------------------------------------------------------
/// \brief    Asigna el event TPDOReceived.
/// \param    event: L'event.
/// \param    enabled: True per deixar-lo habilitat.
///
void CanOpenMasterService::setTPDOReceivedEvent(
	ITPDOReceivedEvent &event,
	bool enabled) {

	_erTPDOReceived.set(event, enabled);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event TPDOReceived.
/// \param    cobid: El COBID del TPDO
/// \param    data: Les dades.
/// \param    dataLen: La longitut de les dades.
///
void CanOpenMasterService::raiseTPDOReceivedEvent(
	uint16_t cobid,
	const uint8_t *data,
	unsigned dataLen) {

	if (_erTPDOReceived.isEnabled()) {

		TPDOReceivedEventArgs args = {
			.cobid {cobid},
			.dataLen {dataLen},
			.data {data}
		};

		_erTPDOReceived(this, &args);
	}
}

