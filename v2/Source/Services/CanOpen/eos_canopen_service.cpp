#include "eos.h"
#include "services/canopen/eos_canopen_dictionary.h"
#include "services/canopen/eos_canopen_service.h"
#include "services/canopen/eos_canopen_protocols.h"


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
	_queue {5} {

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
    _devCAN->setFilter(&filter1, 1);

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

				// S'ha rebut un missatge CANOpen
				//
				case MessageID::canReceive: {
					process(msg.canReceive.cobid, msg.canReceive.data);
/*
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
					}*/
					break;
				}

				// Ha canviat un valor en el diccionari
				//
				case MessageID::entryValueChanged:
					processValueChanged(msg.entryValueChanged.entryId, msg.entryValueChanged.raiseNotification);
					break;
			}
		}
	}

	_devCAN->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio de canvi d'estat
///
void CanOpenService::raiseStateChangedNotificationEvent() {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::stateChanged}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera una notificacio de canvi de valor en una entrada
///           del diccionari
/// \param    index: L'index de l'entrada.
/// \param    sunIndex: El subindex de l'entrada.
///
void CanOpenService::raiseValueChangedNotificationEvent(
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

		raiseStateChangedNotificationEvent();
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
/// \brief    Procesa un canvi en el valor d'una entrada del diccionari
/// \param    entryId: Identificador de l'entrada.
/// \param    raiseNotification: Indica si cal generar un event de notificacio.
///
void CanOpenService::processValueChanged(
	unsigned entryId,
	bool raiseNotification) {

	// Si esta operacional, comprova si cal generar TPDO's
	//
	if (_nodeState == NodeState::operational) {

	}

	if (raiseNotification) {
		auto index = _dictionary->getIndex(entryId);
		auto subIndex = _dictionary->getSubIndex(entryId);
		raiseValueChangedNotificationEvent(index, subIndex);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha canviat un valor del diccionari
/// \param    index: L'index de la entrada.
/// \param    aubIndex: Subindex de la entrada.
/// \param    Indica si cal generar una notificacio.
///
void CanOpenService::notifyValueChanged(
	uint16_t index,
	uint8_t subIndex,
	bool raiseNotification) {

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1)
		notifyValueChanged(entryId, raiseNotification);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha canviat un valor del diccionari
/// \param    ptr: Punter al valor modificat.
/// \param    Indica si cal generar una notificacio.
///
void CanOpenService::notifyValueChanged(
	const void *ptr,
	bool raiseNotification) {

	auto entryId = _dictionary->find(ptr);
	if (entryId != (unsigned) -1)
		notifyValueChanged(entryId, raiseNotification);
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que ha canviat un valor del diccionari
/// \param    entryId: Identificador de la entrada.
/// \param    Indica si cal generar una notificacio.
///
void CanOpenService::notifyValueChanged(
	unsigned entryId,
	bool raiseNotification) {

	Message msg = {
		.id {MessageID::entryValueChanged},
		.entryValueChanged {
			.entryId {entryId},
			.raiseNotification {raiseNotification}
		}
	};
	_queue.push(msg, (unsigned) -1);
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
