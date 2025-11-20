#include "eos.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"
#include "Services/CanOpen/eosCanOpenService.h"
#include "Services/CanOpen/eosCanOpenProtocols.h"


using namespace eos;
using namespace htl;


constexpr const char *serviceName = "CanOpen";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 256;


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
	_queue {5},
	_sdoServer(params.dictionary) {

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
    can::Filter filter0 = {
       	.id1 = COBID::SDO | (_nodeId & 0x7Fu),
       	.id2 = 0x7FFu,
		.idType = can::IdentifierType::standard,
		.type = can::FilterType::mask,
		.config = can::FilterConfig::rxFifo0
    };
    _devCAN->setFilter(&filter0, 0);

    // Permet els missatges NMT dirigits especificament al node
	//
    can::Filter filter1 = {
       	.id1 = COBID::NMT | (_nodeId & 0x7Fu),
       	.id2 = 0x7FFu,
		.idType = can::IdentifierType::standard,
		.type = can::FilterType::mask,
		.config = can::FilterConfig::rxFifo0
    };
    _devCAN->setFilter(&filter0, 1);

	// Accepta notificacions del dispositiu.
	//
	_devCAN->setNotificationEvent(_canDeviceNotificationEvent);

	// Inicia el dicpositiu FCAN en modus interrupcio.
	//
	_devCAN->start_IRQ();

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);

	// Envia bootup al bus
	//
	bootUp();

	while (!stopSignal()) {

		Message msg;
		while(_queue.pop(msg, (unsigned) -1)) {
			switch (msg.id) {
				case MessageID::canReceive: {

					uint8_t response[8];
					uint8_t nodeId = msg.canReceive.cobid & 0x007F;
					uint16_t cobid = msg.canReceive.cobid & ~0x007F;

					switch (cobid) {
						case COBID::SDO:
							if (nodeId == _nodeId)
								processSDO(msg.canReceive.data, response);
							break;

						case COBID::NMT:
							if ((nodeId == _nodeId) || (nodeId == 0))
								processNMT(msg.canReceive.data);
							break;

						case COBID::SYNC:
							processSYNC();
							break;
					}
					break;

				}
			}
		}
	}

	_devCAN->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el canvi d'estat
///
void CanOpenService::notifyStateChanged() {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::stateChanged}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el canvi de valor en una entrada del diccionari
/// \param    index: L'index de l'entrada.
/// \param    sunIndex: El subindex de l'entrada.
///
void CanOpenService::notifyValueChanged(
	uint16_t index,
	uint8_t subIndex) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::valueChanged},
			.valueChanged {
				.index {index},
				.subIndex {subIndex}
			}
		};

		_erNotification(this, &args);
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

		notifyStateChanged();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un SDO
/// \param    rxData: Les dades de la comanda
/// \param    txData: Les dades de la resposta.
///
void CanOpenService::processSDO(
	const uint8_t *rxData,
	uint8_t *txData) {

	if ((_nodeState == NodeState::preOperational) ||
		(_nodeState == NodeState::operational)) {

		if (_sdoServer.process(rxData, txData).isSuccess())
			; //TODO: sendFrame(COBID::SDOr | nodeId, response, sizeof(response));

	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa SYNC
///
void CanOpenService::processSYNC() {

	if (_nodeState == NodeState::operational) {

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
}


// -----------------------------------------------------------------------
/// \brief    Procesa MNT
/// \param    rxData: Les dades del bloc MNT
///
void CanOpenService::processNMT(
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
/// \brief    Procesa RTPO
/// \param    rxData: Les dades del bloc RTPO
///
void CanOpenService::processRPDO(
	const uint8_t *rxData) {

	if (_nodeState == NodeState::operational) {

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
void CanOpenService::heartBeat() {

	uint8_t txData;
	switch (_nodeState) {
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

	sendFrame(COBID::HeartBeat, &txData, sizeof(txData));
}


/// ----------------------------------------------------------------------
/// \brief    Envia un boot-up al bus.
///
void CanOpenService::bootUp() {

	uint8_t txData = 0;
	sendFrame(COBID::BootUp, &txData, sizeof(txData));
}


unsigned CanOpenService::buildTPDO(
	unsigned tpdoId,
	uint8_t *buffer,
	unsigned bufferSize) {

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
		.id = cobid | (_nodeId & 0x7Fu),
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


/// ----------------------------------------------------------------------
/// \brief    Gestiona les notificacions del modul CAN
/// \param    sender: El remitent. En aquest cas el modulCAN
/// \param    aregs: Els parametres del missatge.
///
void CanOpenService::canDeviceNotificationEventHandler(
	htl::can::CANDevice * const sender,
	htl::can::CANDevice::NotificationEventArgs * const args) {

	switch (args->id) {
		case htl::can::CANDevice::NotificationID::rxFifoNotEmpty:

			Message msg;

			htl::can::RxHeader rxHeader;
			_devCAN->getRxMessage(args->rxFifoNotEmpty.fifo, &rxHeader, msg.canReceive.data, sizeof(msg.canReceive.data));

			msg.id = MessageID::canReceive;
			msg.canReceive.cobid = rxHeader.id;

			_queue.pushISR(msg);

			break;
	}
}
