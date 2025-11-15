#include "eos.h"
#include "Services/CanOpen/eosCanOpenService.h"


using namespace eos;
using namespace htl;


constexpr const char *serviceName = "CanOpen";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 256;

struct COBID {
	static constexpr uint16_t MNT       = 0x000;
	static constexpr uint16_t SDO       = 0x600;
	static constexpr uint16_t SDOr      = 0x580;
	static constexpr uint16_t Heartbeat = 0x700;
	static constexpr uint16_t TPDO1     = 0x180;
	static constexpr uint16_t TPDO2     = 0x280;
	static constexpr uint16_t TPDO3     = 0x380;
	static constexpr uint16_t TPDO4     = 0x480;
};

struct NMT0 {
	static constexpr uint8_t CS_Pos    = 0;
	static constexpr uint8_t CS_Msk    = 0xFF << CS_Pos;
	static constexpr uint8_t CS_START  = 0x01 << CS_Pos;
	static constexpr uint8_t CS_STOP   = 0x02 << CS_Pos;
	static constexpr uint8_t CS_PREOP  = 0x80 << CS_Pos;
	static constexpr uint8_t CS_RST    = 0x81 << CS_Pos;
	static constexpr uint8_t CS_RSTCOM = 0x82 << CS_Pos;
};

struct SDO0 {
	static constexpr uint8_t CCS_Pos      = 5;
	static constexpr uint8_t CCS_Msk      = 0b111 << CCS_Pos;
	static constexpr uint8_t CCS_UP       = 0 << CCS_Pos;
	static constexpr uint8_t CCS_DN       = 1 << CCS_Pos;
	static constexpr uint8_t CCS_RSP      = 3 << CCS_Pos;
	static constexpr uint8_t CCS_ABORT    = 4 << CCS_Pos;

	static constexpr uint8_t E_Pos        = 1;
	static constexpr uint8_t E_Msk        = 0b1 << E_Pos;
	static constexpr uint8_t E_SEG        = 0 << E_Pos;
	static constexpr uint8_t E_EXP        = 1 << E_Pos;

	static constexpr uint8_t S_Pos        = 0;
	static constexpr uint8_t S_Msk        = 0b1;
	static constexpr uint8_t S_NO         = 0 << S_Pos;
	static constexpr uint8_t S_SIZE       = 1 << S_Pos;

	static constexpr uint8_t SIZE_Pos     = 2;
	static constexpr uint8_t SIZE_Msk     = 0b11 << SIZE_Pos;
	static constexpr uint8_t SIZE_1       = 3 << SIZE_Pos;
	static constexpr uint8_t SIZE_2       = 2 << SIZE_Pos;
	static constexpr uint8_t SIZE_3       = 1 << SIZE_Pos;
	static constexpr uint8_t SIZE_4       = 0 << SIZE_Pos;
};


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
CanOpenService::CanOpenService(
	InitParams const &params) :

    _devCAN {params.devCAN},
	_canDeviceNotificationEvent {*this, &CanOpenService::canDeviceNotificationEventHandler},
	_dictionary {params.dictionary},
	_nodeId {params.nodeId},
	_nodeType {params.nodeType},
	_nodeState {NodeState::initializing},
	_queue {10} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
/// \param    params: Parametres d'inicialitzacio.
///
void CanOpenService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackSize = serviceStackSize;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief    Executa els procesos del servei.
///
void CanOpenService::onExecute() {

	// Permet els missatges SDO dirigits especificament al node
	//
    can::Filter filter = {
       	.id1 = _nodeId & 0x7Fu,
       	.id2 = 0x7Fu,
		.idType = can::IdentifierType::standard,
		.type = can::FilterType::mask,
		.config = can::FilterConfig::rxFifo0
    };
    _devCAN->setFilter(&filter, 0);

	// Accepta notificacions del dispositiu.
	//
	_devCAN->setNotificationEvent(_canDeviceNotificationEvent);

	// Inicia el dicpositiu FCAN en modus interrupcio.
	//
	_devCAN->start_IRQ();

	// Canvia l'estat
	//
	changeNodeState(NodeState::operational);

	while (!stopSignal()) {

		Message msg;
		while(_queue.pop(msg, 1000)) {
			switch (msg) {
				case Message::rxFifo0: {

					htl::can::RxHeader rxHeader;
					uint8_t rxData[8];

					_devCAN->getRxMessage(htl::can::RxFifoSelection::fifo0, &rxHeader, rxData, sizeof(rxData));

					uint8_t nodeId = rxHeader.id & 0x007F;
					uint16_t cobid = rxHeader.id & ~0x007F;

					// Comprova si es el node receptor. En teoria no cal
					// perque ja ve filtrat
					//
					if (nodeId == _nodeId) {

						switch (cobid){
							case COBID::SDO:
								processSDO(rxData);
								break;

							case COBID::MNT:
								processMNT(rxData);
								break;
						}
					}
					break;
				}

				case Message::heartbeat:
					break;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Realitza el canvi d'estat i notifica els canvis
/// \param    newNodeState: El nou estat
///
void CanOpenService::changeNodeState(
	NodeState newNodeState) {

	if (_nodeState != newNodeState) {

		switch (_nodeState) {
			case NodeState::initializing:
				break;

			case NodeState::preOperational:
				break;

			case NodeState::operational:
				break;

			case NodeState::stoped:
				break;
		}

		_nodeState = newNodeState;

		switch (_nodeState) {
			case NodeState::initializing:
				break;

			case NodeState::preOperational:
				break;

			case NodeState::operational:
				break;

			case NodeState::stoped:
				break;
		}
	}
}



/// ----------------------------------------------------------------------
/// \brief    Procesa SDO
/// \param    rxData: Les dades del bloc SDO
///
void CanOpenService::processSDO(
	const uint8_t *rxData) {

	if ((_nodeState == NodeState::operational) ||
		(_nodeState == NodeState::preOperational)) {

		switch (rxData[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) {
			case SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP :
				processSDO_ExpeditedDownload(rxData);
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa SDO expedited download
/// \param    rxData: Les dades del bloc SDO
///
void CanOpenService::processSDO_ExpeditedDownload(
	const uint8_t *rxData) {

	uint32_t errorCode = 0;

	uint16_t index = rxData[1] | (rxData[2] << 8);
	uint8_t subIndex = rxData[3];

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1) {

		uint8_t size = 4 - ((rxData[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
		uint32_t value = rxData[4];
		if (size > 1)
			value |= rxData[5] << 8;
		if (size > 2)
			value |= rxData[6] << 16;
		if (size > 3)
			value |= rxData[7] << 24;

		if (!_dictionary->write(entryId, value))
			errorCode = 0x6010000; // Access no permes
	}
	else
		errorCode = 0x06020000; // L'entrada del diccionari no existeix

	uint8_t txData[8];
	txData[1] = rxData[1];
	txData[2] = rxData[2];
	txData[3] = rxData[3];
	if (errorCode == 0) {
		txData[0] = SDO0::CCS_RSP;
		txData[4] = 0;
		txData[5] = 0;
		txData[6] = 0;
		txData[7] = 0;
	}
	else {
		txData[0] = SDO0::CCS_ABORT;
		txData[4] = errorCode & 0xFF;
		txData[5] = (errorCode >> 8) & 0xFF;
		txData[6] = (errorCode >> 16) & 0xFF;
		txData[7] = (errorCode >> 24) & 0xFF;
	}
	//sendFrame(COBID::SDOr, rdata, 8);
}


// -----------------------------------------------------------------------
/// \brief    Procesa MNT
/// \param    rxData: Les dades del bloc MNT
///
void CanOpenService::processMNT(
	const uint8_t *rxData) {

	switch (rxData[0] & NMT0::CS_Msk) {
		case NMT0::CS_START:
			if ((_nodeState == NodeState::preOperational) ||
				(_nodeState == NodeState::stoped))
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
	}
}


/// ----------------------------------------------------------------------
/// \brief    SDO expedited download
/// \param    nodeId: El node destinatari.
/// \param    index: Index.
/// \param    subIndex: Subindex.
/// \param    value: El valor.
///
void CanOpenService::sdoDownload(
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


/// ----------------------------------------------------------------------
/// \brief    Envia un heartbeat al bus.
///
void CanOpenService::heartbeat() {

	uint8_t txData;
	switch (_nodeState) {
		case NodeState::initializing:
			txData = 0;
			break;

		case NodeState::stoped:
			txData = 4;
			break;

		case NodeState::preOperational:
			txData = 0x7F;
			break;

		case NodeState::operational:
			txData = 5;
			break;

		case NodeState::error:
			txData = 0x80;
			break;
	}

	sendFrame(COBID::Heartbeat, &txData, sizeof(txData));
}


/// ----------------------------------------------------------------------
/// \brief    Transmet un TPDO
/// \param    tpdoId: Indentificador del TPDO
///
void CanOpenService::tpdoTransmit(
	uint8_t tpdoId) {

	if (_nodeState == NodeState::operational) {
		auto entryId = _dictionary->find(0x1A00 | (tpdoId & 0x03),  0x00);
		if (entryId != (unsigned) -1) {
			uint8_t mapCount;
			if (_dictionary->readU8(entryId, mapCount)) {
				for (unsigned i = 0; i < mapCount; i++) {
					uint32_t mapInfo;
					_dictionary->readU32(entryId, mapInfo);

					uint16_t mapIndex = (mapInfo >> 16) & 0xFFFF;
					uint8_t mapSubIndex = (mapInfo >> 8) & 0xFF;
					unsigned mapLength = (mapInfo & 0xFF) / 8;
				}
			}
		}
	}
	//sendFrame(COBID::TPDO1, txData, sizeof(txData));
}


/// ----------------------------------------------------------------------
/// \brief    Transmet una trama.
/// \param    cobid: El identificador.
/// \param    data: Les dades.
///
void CanOpenService::sendFrame(
	uint16_t cobid,
	const uint8_t *data,
	unsigned length) {

	htl::can::DataLength len = length == 1 ?
			htl::can::DataLength::len1 : htl::can::DataLength::len8;

	htl::can::TxHeader header = {
		.id = cobid | (_nodeId & 0x7F),
		.idType = htl::can::IdentifierType::standard,
		.dataLength = len,
		.frameType = htl::can::FrameType::dataFrame,
		.errorStateFlag = htl::can::ErrorStateFlag::active,
		.bitrateSwitching = htl::can::BitrateSwitching::off,
		.fdFormat = htl::can::FDFormat::can,
		.txEventFifoControl = htl::can::TxEventFifoControl::noStore,
		.messageMarker = 0x00
	};

	_devCAN->addTxMessage(&header, data);
}


void CanOpenService::canDeviceNotificationEventHandler(
	htl::can::CANDevice * const sender,
	htl::can::CANDevice::NotificationEventArgs * const args) {

	switch (args->id) {
		case htl::can::CANDevice::NotificationID::rxFifoNotEmpty:
			Message msg;
			if (args->rxFifoNotEmpty.fifo == htl::can::RxFifoSelection::fifo0)
				msg = Message::rxFifo0;
			else
				msg = Message::rxFifo1;
			_queue.pushISR(msg);
			break;
	}
}
