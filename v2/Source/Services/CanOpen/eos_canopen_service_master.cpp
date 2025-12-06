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

	CanOpenService(params) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les dades rebudes, tenint en compte l'estat del node
/// \param    cobid: El COB-ID
/// \param    data: Les dades a procesar
///
void CanOpenMasterService::process(
	uint16_t cobid, const
	uint8_t *data) {

	switch (cobid & ~0x007F) {
		case COBID::HeartBeat:
			break;
	}

}


/// ----------------------------------------------------------------------
/// \brief    SDO expedited download. Transfereix dades a un
//            node determinat
/// \param    nodeId: El node destinatari.
/// \param    index: Index.
/// \param    subIndex: Subindex.
/// \param    value: El valor.
///
void CanOpenMasterService::sdoDownload(
	unsigned nodeId,
	uint16_t index,
	uint8_t subIndex,
	uint32_t value) {

	uint8_t txData[8];
	txData[0] = SDO0::CCS_DN | SDO0::E_EXP | SDO0::S_SIZE | SDO0::SIZE_4;
	txData[1] = index & 0xFF;
	txData[2] = index >> 8;
	txData[3] = subIndex;
	txData[4] = value & 0xFF;
	txData[5] = (value >> 8) & 0xFF;
	txData[6] = (value >> 16) & 0xFF;
	txData[7] = (value >> 24) & 0xFF;

	sendFrame(COBID::SDO, txData, sizeof(txData));
}
