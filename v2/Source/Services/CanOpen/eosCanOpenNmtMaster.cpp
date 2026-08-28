module;

#include "eos.h"
#include "eosTime.h"
#include "Services/CanOPen/eosCanOpenService.h"


export module Eos.Services.CanOpen.NmtMaster;


export namespace eos {

	class CanOpenNmtMaster {
		public:
			enum class Command: uint8_t {
				start = 1,
				stop = 2,
				enterPreoperational = 128,
				resetNode = 129,
				resetComunication = 130
			};

		private:
			CanOpenService * const _service;

		public:
			CanOpenNmtMaster(CanOpenService *service);

			Result sendCommand(NodeID nodeId, Command command, Time blockTime);
	};

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei CanOpen.
///
eos::CanOpenNmtMaster::CanOpenNmtMaster(
	CanOpenService *service):

	_service {service} {

}


/// ----------------------------------------------------------------------
/// \brief    Emet una comanda NMT a un node especificat.
/// \parent   nodeId: Identificador del node.
/// \param    command: La comanda.
/// \param    blockTime: Temps maxim de bloqueig.
///
eos::Result eos::CanOpenNmtMaster::sendCommand(
	NodeID nodeId,
	Command command,
	Time blockTime) {

	uint8_t data[2];
	data[0] = (uint8_t) command;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return _service->emitFrame(cobId, data, sizeof(data), blockTime);
}
