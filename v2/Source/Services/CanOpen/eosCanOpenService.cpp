#include "eos.h"
#include "eosTime.h"
#include "rtos/rtosTask.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"
#include "Services/CanOpen/eosCanOpenService.h"
#include "Services/canopen/eosCanOpenProtocol.h"


import Eos.Math;
import Eos.Services.CanOpen.HeartbeatProducer;
import Eos.Services.CanOpen.NmtMaster;


constexpr const char *serviceName = "CanOpen";
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::normal;
constexpr uint32_t serviceStackDepth = 256;

constexpr unsigned defTimeout = 25;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
eos::CanOpenService::CanOpenService(
	InitParams const &params) :

    _devCAN {params.devCAN},
	_dictionary {params.dictionary},
	_canDevice_notificationEvent {*this, &CanOpenService::canDevice_notificationEventHandler},
	_nodeId {(uint8_t)(params.nodeId & 0x7F)},
	_nodeState {NodeState::initializing},
	_messageQueue {_messageQueueSize},

	_heartbeatProducer {nullptr},
	_nmtMaster {nullptr}{
}


void eos::CanOpenService::enableNotificationEvent(
	INotificationEvent &event) {

	_notificationEventRaiser.enable(event);
}


void eos::CanOpenService::disableNotificationEvent() {

	_notificationEventRaiser.disable();
}


void eos::CanOpenService::enableWriteRequestEvent(
	IWriteRequestEvent &event) {

	_writeRequestEventRaiser.enable(event);
}


void eos::CanOpenService::disableWriteRequestEvent() {

	_writeRequestEventRaiser.disable();
}


void eos::CanOpenService::enableSYNCReceivedEvent(
	ISYNCReceivedEvent &event) {

	_syncReceivedEventRaiser.enable(event);
}


void eos::CanOpenService::disableSYNCReceivedEvent() {
	_syncReceivedEventRaiser.disable();
}


void eos::CanOpenService::enableTPDOReceivedEvent(
	ITPDOReceivedEvent &event) {

	_tpdoReceivedEventRaiser.enable(event);
}


void eos::CanOpenService::disableTPDOReceivedEvent() {

	_tpdoReceivedEventRaiser.disable();
}


void eos::CanOpenService::enableHeartbeatReceivedEvent(
	IHeartbeatReceivedEvent &event) {

	_heartbeatReceivedEventRaiser.enable(event);
}


void eos::CanOpenService::disbleHeartbeatReceivedEvent() {

	_heartbeatReceivedEventRaiser.disable();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
/// \param    params: Parametres d'inicialitzacio.
///
void eos::CanOpenService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackDepth = serviceStackDepth;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief    Executa els procesos del servei.
///
void eos::CanOpenService::onExecute() {

	configureCANDevice();
	configureCANFilters();
	configureHeartbeat();
	configureNmtMaster();

    // Accepta notificacions del dispositiu.
	//
	_devCAN->enableNotificationEvent(_canDevice_notificationEvent);

	// Inicia el dispositiu FCAN en modus interrupcio.
	//
	_devCAN->start_IRQ();

	// Emet bootup i espera 500ms
	//
	auto hb = reinterpret_cast<CanOpenHeartbeatProducer*>(_heartbeatProducer);
	hb->sendBoot();
	rtos::Task::delay(eos::Time::fromMiliseconds(500));

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);

	while (!stopSignal()) {

		Message message;
		while(_messageQueue.pop(message, Time::fromMiliseconds(1000))) {
			switch (message.id) {

				// Ha canviat una entrada del diccionari
				//
				case MessageID::entryChanged:
					processEntryChanged(message.entryChanged);
					break;

				// Canvia l'estat del node.
				//
				case MessageID::changeNodeState:
					processChangeNodeState(message.changeNodeState);
					break;

				// S'ha rebut una trama CANOpen
				//
				case MessageID::frameReceived:
					processFrameReceived(message.frameReceived);
					break;

				// Cal enviar un trama CANOpen
				//
				case MessageID::sendFrame:
					processSendFrame(message.sendFrame);
					break;

				default:
					break;
			}
		}
	}

	_devCAN->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Configura el productor de heartbeat.
///
void eos::CanOpenService::configureHeartbeat() {

	auto heartbeatProducer = new CanOpenHeartbeatProducer(this);
	heartbeatProducer->start();

	_heartbeatProducer = heartbeatProducer;
}


/// ----------------------------------------------------------------------
// \brief     Configura el MNT Master.
///
void eos::CanOpenService::configureNmtMaster() {

	auto nmtMaster = new CanOpenNmtMaster(this);

	_nmtMaster = nmtMaster;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el dispositiu CAN
///
void eos::CanOpenService::configureCANDevice() {

    htl::can::CANDevice::InitParams initParams = {
    	.clockDivider = htl::can::ClockDivider::div1,
		.frameFormat = htl::can::FrameFormat::classic,
		.mode = htl::can::Mode::normal,
		.autoRetransmission = true,
		.transmitPause = true,
		.protocolException = false,
		.nominalPrescaler = 2,
		.nominalSyncJumpWidth = 16,
		.nominalTimeSeg1 = 63,
		.nominalTimeSeg2 = 16,
		.dataPrescaler = 1,
		.dataSyncJumpWidth = 4,
		.dataTimeSeg1 = 5,
		.dataTimeSeg2 = 4,
		.stdFiltersNbr = 6, // Nombre de filtres utilitzats
		.extFiltersNbr = 0,
		.qfMode = htl::can::QFMode::fifo
    };
    _devCAN->initialize(&initParams);

    _devCAN->setGlobalFilter(
    	htl::can::NonMatchingFrames::reject,
		htl::can::NonMatchingFrames::reject,
		htl::can::RejectRemoteFrames::filterRemote,
		htl::can::RejectRemoteFrames::filterRemote);
}


/// ----------------------------------------------------------------------
/// \brief    Configura els filtres CAN
///
void eos::CanOpenService::configureCANFilters() {

	unsigned filterIndex = 0;

	htl::can::Filter filter;
	filter.idType = htl::can::IdentifierType::standard;
	filter.type = htl::can::FilterType::mask;
	filter.config = htl::can::FilterConfig::rxFifo0;

	// Accepta els missatges SDO que suporta aquest node
	// Si existeix l'entrada 1200:1, aleshores hi ha servidor SDO en el node,
	// en cas contrari no cal definir els filtres.
	//
	uint32_t cobidSDO;
	if (_dictionary->readU32(0x1200, 0x01, cobidSDO)) {
		filter.id1 = (cobidSDO & 0x780) | _nodeId;
		filter.id2 = 0x7FFu;
		_devCAN->setFilter(&filter, filterIndex++);
	}

	// Accepta els missatges NMT
	//
	filter.id1 = COBID::NMT;
	filter.id2 = 0x7FFu;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges Headbead, sense importar el nodeId
	//
	filter.id1 = COBID::Heartbeat,
	filter.id2 = 0x780u;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges SYNC
	//
	filter.id1 = COBID::SYNC,
	filter.id2 = 0x7FFu;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges TPDO, sense importar el nodeId
	//
	filter.id1 = COBID::TPDO1,
	filter.id2 = 0x780u;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges RPDO suportats per aquest node
	//
	filter.id1 = COBID::RPDO1 | _nodeId,
	filter.id2 = 0x780u;
	_devCAN->setFilter(&filter, filterIndex++);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant l'estat del node canvia.
///
void eos::CanOpenService::onNodeStateChanged() {

	if (_notificationEventRaiser) {

		NotificationEventArgs args = {
			.id {NotificationID::stateChanged},
			.stateChanged {
				.state {_nodeState}
			}
		};

		_notificationEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant es reb un SYNC desde un node remot.
///
void eos::CanOpenService::onSYNCReceived() {

	if (_syncReceivedEventRaiser) {

		SYNCReceivedEventArgs args = {
		};

		_syncReceivedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quan es fa una sol·licitut d'escriptura desde
///           un node remot.
/// \param    index: El index
/// \param    subIndex: El subindex.
/// \param    value: El valor.
///
void eos::CanOpenService::onWriteU8Request(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value) {

	if (_writeRequestEventRaiser) {

		WriteRequestEventArgs args = {
			.index {index},
			.subIndex {subIndex},
			.value {
				.u8 {value}
			}
		};

		_writeRequestEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quan es fa una sol·licitut d'escriptura desde un
///           node remot.
/// \param    index: El index
/// \param    subIndex: El subindex.
/// \param    value: El valor.
///
void eos::CanOpenService::onWriteU16Request(
	uint16_t index,
	uint8_t subIndex,
	uint16_t value) {

	if (_writeRequestEventRaiser) {

		WriteRequestEventArgs args = {
			.index {index},
			.subIndex {subIndex},
			.value {
				.u16 {value}
			}
		};

		_writeRequestEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quan es fa una sol·licitut d'escriptura desde un
///           node remot.
/// \param    index: El index
/// \param    subIndex: El subindex.
/// \param    value: El valor.
///
void eos::CanOpenService::onWriteU32Request(
	uint16_t index,
	uint8_t subIndex,
	uint32_t value) {

	if (_writeRequestEventRaiser) {

		WriteRequestEventArgs args = {
			.index {index},
			.subIndex {subIndex},
			.value {
				.u32 {value}
			}
		};

		_writeRequestEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Ec crida quant es reb un TPDO d'un node remot
/// \param    cobId: El COBID del TPDO
/// \param    data: Les dades.
/// \param    dataLen: La longitut de les dades.
///
void eos::CanOpenService::onTPDOReceived(
	CobID cobId,
	const uint8_t *data,
	uint32_t dataLen) {

	if (_tpdoReceivedEventRaiser) {

		TPDOReceivedEventArgs args = {
			.cobId {cobId},
			.dataLen {(uint8_t)dataLen},
			.data {data}
		};

		_tpdoReceivedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quan es reb un Heartbeat desde un node remot
/// \param    nodeId: El node emisor
/// \param    state: L'estat del node emisor.
///
void eos::CanOpenService::onHeartbeatReceived(
	NodeID nodeId,
	NodeState nodeState) {

	if (_heartbeatReceivedEventRaiser) {

		HeartbeatReceivedEventArgs args = {
			.nodeId {nodeId},
			.nodeState {nodeState}
		};

		_heartbeatReceivedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Realitza el canvi d'estat i notifica els canvis
/// \param    newNodeState: El nou estat
///
void eos::CanOpenService::changeNodeState(
	NodeState newNodeState) {

	if (_nodeState != newNodeState) {
		_nodeState = newNodeState;
		onNodeStateChanged();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'entryChanged'
/// \param    msg: Els parametres del missatge.
///
void eos::CanOpenService::processEntryChanged(
	const EntryChanged &msg) {

	// Si esta en modus operacional, comprova si cal generar TPDO's
	//
	if (_nodeState == NodeState::operational) {

		// Comprova les entrades 0x1800 per si hi ha TPDO asincrones
		//
		uint8_t tpdoMax = 4;
		for (uint8_t tpdo = 0; tpdo < tpdoMax; tpdo++) {

			// Verifica que la entrada, estigui mapejada en un TPDO
			//
			if (isMapped(tpdo, msg.entryId)) {
				uint32_t flags;
				uint8_t transmissionType;

				if (_dictionary->readU32(0x1800 + tpdo, 0x01, flags) &&
					_dictionary->readU8(0x1800 + tpdo, 0x02, transmissionType)) {

					if ((transmissionType == 254) && ((flags & (1 << 31)) == 0))
						sendTPDO(tpdo);
				}
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'changeNodeState'
/// \param    msg: Els parametres del missatge.
///
void eos::CanOpenService::processChangeNodeState(
	const ChangeNodeState &msg) {

	changeNodeState(msg.nodeState);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'sendFrame'
/// \param    msg: Els parametres del missatge.
///
void eos::CanOpenService::processSendFrame(
	const SendFrame &msg) {

	sendFrame(CobID(msg.cobid), msg.data, msg.dataLen, Time::fromMiliseconds(20));
}



/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived'
/// \param    msg: Els parammetres del missatge.
///
void eos::CanOpenService::processFrameReceived(
	const FrameReceived &msg) {

	CobID cobId(msg.cobid);

	if (cobId.isNMT())
		processNMT(msg.data[0], msg.data[1]);

	else if (cobId.isSYNC())
		processSYNC();

	else if (cobId.isTIME())
		processTIME();

	else if (cobId.isHeartbeat())
		processHeartbeat(cobId.nodeId(), msg.data[0]);

	else if (cobId.base() == COBID::SDO)
		processSDO(msg.data);

	else if ((cobId.base() == COBID::RPDO1) ||
		     (cobId.base() == COBID::RPDO2) ||
		     (cobId.base() == COBID::RPDO3) ||
		     (cobId.base() == COBID::RPDO4))
		processRPDO(cobId, msg.data, msg.dataLen);

	else if ((cobId.base() == COBID::TPDO1) ||
		     (cobId.base() == COBID::TPDO2) ||
		     (cobId.base() == COBID::TPDO3) ||
		     (cobId.base() == COBID::TPDO4))
	    processTPDO(cobId, msg.data, msg.dataLen);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges Heartbeat.
/// \param    nodeId: El node origen del missatge.
/// \param    state: L'estat del node.
///
void eos::CanOpenService::processHeartbeat(
	NodeID nodeId,
	uint8_t state) {

	NodeState nodeState = NodeState::error;
	switch (state) {
		case 0x00: // boot-up
			nodeState = NodeState::initializing;
			break;

		case 0x04: // stopped
			nodeState = NodeState::stoped;
			break;

		case 0x05: // operational
			nodeState = NodeState::operational;
			break;

		case 0x7F: // preoperational
			nodeState = NodeState::preOperational;
			break;
	}

	onHeartbeatReceived(nodeId, nodeState);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges NMT
/// \param    command: La comanda NMT
/// \param    nodeId: El identificador del node on aplicar la comanda
///
void eos::CanOpenService::processNMT(
	uint8_t command,
	NodeID nodeId) {

	if ((nodeId == _nodeId) || (nodeId == 0)) {
		switch (command) {
			case 0x01:
				changeNodeState(NodeState::operational);
				break;

			case 0x02:
				changeNodeState(NodeState::stoped);
				break;

			case 0x80:
				changeNodeState(NodeState::preOperational);
				break;

			case 0x81:
				break;

			case 0x82:
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges SDO
/// \param    data: Dades del missatge.
///
void eos::CanOpenService::processSDO(
	const uint8_t *data) {

	uint8_t response[8];
	uint32_t errorCode = SdoError::none;

	// Comprova l'estat del node
	//
	if ((_nodeState != NodeState::preOperational) &&
		(_nodeState != NodeState::operational))
		errorCode = SdoError::unsupportedAccesssToObject;

	// Initiate SDO download (Expedited)
	//
	else if ((data[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP)) {

		uint16_t index = data[1] | (data[2] << 8);
		uint8_t subIndex = data[3];

		auto entryId = _dictionary->find(index, subIndex);
		if (entryId == (typeof(entryId)) -1)
			errorCode = SdoError::objectDoesNotExistInDictionary;

		else {
			if (!_dictionary->canWrite(entryId))
				errorCode = SdoError::attemptToWriteReadOnlyObject;

			else {
				uint8_t size = 4 - ((data[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8: {
						uint8_t value = data[4];
						onWriteU8Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned16: {
						uint16_t value = (data[4] << 8) | (data[5] << 16);
						onWriteU16Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned32: {
						uint32_t value = data[4] | (data[5] << 8) | (data[6] << 16) |
								(data[7] << 24);
						onWriteU32Request(index, subIndex, value);
						break;
					}

					default:
						errorCode = SdoError::dataTypeDoesNotMatch;
						break;
				}
			}
		}

		if (errorCode == SdoError::none) {
			response[0] = SDO0::SCS_DL;
			response[4] = 0;
			response[5] = 0;
			response[6] = 0;
			response[7] = 0;
		}
	}

	// Initiate SDO download (Normal)
	//
	else if ((data[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_SEG)) {
		//onInitiateDownloadNormal(query, response);
	}

	// Download segment
	//
	else if ((data[0] & SDO0::CCS_Msk) == SDO0::CCS_DNSEG) {
		//onDownloadSegment(query, response);
	}

	// Initiate SDO upload
	//
	else if ((data[0] & SDO0::CCS_Msk) == SDO0::CCS_UP) {

		uint16_t index = data[1] | (data[2] << 8);
		uint8_t subIndex = data[3];
		unsigned length = 0;

		auto entryId = _dictionary->find(index, subIndex);
		if (entryId == (unsigned) -1)
			errorCode = SdoError::objectDoesNotExistInDictionary;
		else {
			if (!_dictionary->canRead(entryId))
				errorCode = SdoError::attemptToWriteReadOnlyObject;
			else {
				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8: {
						uint8_t value;
						_dictionary->readU8(entryId, value);
						response[4] = value;
						break;
					}

					case CoType::unsigned16: {
						uint16_t value;
						_dictionary->readU16(entryId, value);
						response[4] = value & 0xFF;
						response[5] = (value >> 8) & 0xFF;
						break;
					}

					case CoType::unsigned32: {
						uint32_t value;
						_dictionary->readU32(entryId, value);
						response[4] = value & 0xFF;
						response[5] = (value >> 8) & 0xFF;
						response[6] = (value >> 16) & 0xFF;
						response[7] = (value >> 24) & 0xFF;
						break;
					}

					default:
						errorCode = SdoError::dataTypeDoesNotMatch;
						break;
				}
			}
		}

		if (errorCode == SdoError::none) {

			// Comprova la longitut per seleccionar el tipus de transmissio
			//
			if (length <= 4) {

				// Expedited
				//
				response[0] = SDO0::SCS_UL | SDO0::E_EXP | SDO0::S_SIZE | (((4 - length) << SDO0::SIZE_Pos) & SDO0::SIZE_Msk);
			}
			else {

				// Segmented
				//
				response[0] = SDO0::SCS_UL | SDO0::E_SEG | SDO0::S_SIZE;
				response[4] = length & 0xFF;
				response[5] = (length >> 8) & 0xFF;
				response[6] = (length >> 16) & 0xFF;
				response[7] = (length >> 24) & 0xFF;
			}
		}
	}

	// Upload segment
	//
	else if ((data[0] & SDO0::CCS_Msk) == SDO0::CCS_UPSEG) {
		//onUploadSegment(query, response);
	}

	// Error SDO
	//
	else
		errorCode = SdoError::commandSpecifierNotValid;

	// Prepara la resposta
	//
	response[1] = data[1];
	response[2] = data[2];
	response[3] = data[3];
	if (errorCode != SdoError::none) {
		response[0] = SDO0::CCS_ABORT;
		response[4] = errorCode & 0xFF;
		response[5] = (errorCode >> 8) & 0xFF;
		response[6] = (errorCode >> 16) & 0xFF;
		response[7] = (errorCode >> 24) & 0xFF;
	}

	// Envia la resposta
	//
	uint32_t cobidSDOr;
	if (_dictionary->readU32(0x1200, 0x02, cobidSDOr))
		sendFrame(CobID(cobidSDOr & 0x7FF, _nodeId), response, sizeof(response), Time::fromMiliseconds(defTimeout));
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges TIME
///
void eos::CanOpenService::processTIME() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges SYNC
///
void eos::CanOpenService::processSYNC() {

	onSYNCReceived();

	if (_nodeState == NodeState::operational) {

		// Comprova les  entrades 0x1800 per si hi han TPDOs sincrons
		// per enviar
		//
		uint8_t tpdoMax = 4;
		for (uint8_t tpdo = 0; tpdo < tpdoMax; tpdo++) {

			uint32_t flags;
			uint8_t transmissionType;

			if (_dictionary->readU32(0x1800 + tpdo, 0x01, flags) &&
				_dictionary->readU8(0x1800 + tpdo, 0x02, transmissionType)) {

				if ((transmissionType <= 240) && ((flags & (1 << 31)) == 0))
					sendTPDO(tpdo);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges TPDO
/// \param    cobid: El COB-ID
/// \param    data: Dades del missatge.
///
void eos::CanOpenService::processTPDO(
	CobID cobId,
	const uint8_t *data,
	uint32_t dataLen) {

	// Notifica a l'aplicacio que hi ha un TPDO per procesar provinent d'un
	// node remot
	//
	onTPDOReceived(cobId, data, dataLen);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges RPDO
/// \param    cobid: El COB-ID
/// \param    data: Dades del missatge.
///
void eos::CanOpenService::processRPDO(
	CobID cobId,
	const uint8_t *data,
	uint32_t dataLen) {

	uint32_t rpdoCOBID;
	if (_dictionary->readU32(0x1400, 0x01, rpdoCOBID) && (rpdoCOBID == cobId.base())) {

		const uint8_t *pData = data;

		uint32_t map;
		if (_dictionary->readU32(0x1600, 0x01, map)) {

			uint16_t index = (map >> 16) & 0xFFFF;
			uint8_t subIndex = (map >> 8) & 0xFF;
			uint8_t size = (map & 0xFF) / 8;

			auto entryId = _dictionary->find(index, subIndex);
			if (entryId != (typeof(entryId)) -1) {

				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8:
						if (size == sizeof(uint8_t)) {
							uint8_t value = 0;
							value |= *pData++;
							onWriteU8Request(index, subIndex, value);
						}
						break;

					case CoType::unsigned16:
						if (size == sizeof(uint16_t)) {
							uint16_t value = 0;
							value |= *pData++;
							value |= *pData++ << 8;
							onWriteU16Request(index, subIndex, value);
						}
						break;

					case CoType::unsigned32:
						if (size == sizeof(uint32_t)) {
							uint32_t value = 0;
							value |= *pData++;
							value |= *pData++ << 8;
							value |= *pData++ << 16;
							value |= *pData++ << 24;
							onWriteU32Request(index, subIndex, value);
						}
						break;

					default:
						break;
				}
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Canvia l'estat del node.
/// \param    nodeState: El nou estat.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   El resultat de l'operacio.
///
eos::Result eos::CanOpenService::setNodeState(
	NodeState nodeState,
	Time blockTime) {

	Message message = {
		.id {MessageID::changeNodeState},
		.changeNodeState {
			.nodeState {nodeState}
		}
	};

	if (_messageQueue.push(message, blockTime))
		return eos::Result::ErrorCodes::ok;

	return eos::Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del node.
/// \return   L'estat.
///
eos::CanOpenService::NodeState eos::CanOpenService::getNodeState() const {

	return _nodeState;
}


eos::NodeID eos::CanOpenService::getNodeId() const {

	return _nodeId;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t al diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor.
/// \param    mask: La mascara de bits del valor.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
/// \remarks  La escriptura es posa en cua per un procesament posterior. Si
///           cal, es genera TPDO.
///
bool eos::CanOpenService::writeU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value,
	uint8_t mask,
	Time blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			uint8_t oldValue;
			if (_dictionary->readU8(entryId, oldValue))
				if (_dictionary->writeU8(entryId, (oldValue & ~mask) | (value & mask))) {
					Message message = {
						.id {MessageID::entryChanged},
						.entryChanged {
							.entryId {entryId}
						}
					};
					ok = _messageQueue.push(message, blockTime);
				}
			}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t al diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor.
/// \param    mask: La mascara de bits del valor.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
/// \remarks  La escriptura es posa en cua per un procesament posterior. Si
///           cal, es genera TPDO.
///
bool eos::CanOpenService::writeU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t value,
	uint16_t mask,
	Time blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (unsigned) -1)
		if (_dictionary->canWrite(entryId)) {
			uint16_t oldValue;
			if (_dictionary->readU16(entryId, oldValue))
				if (_dictionary->writeU16(entryId, (oldValue & ~mask) | (value & mask))) {
					Message message = {
						.id {MessageID::entryChanged},
						.entryChanged {
							.entryId {entryId}
						}
					};
					ok = _messageQueue.push(message, blockTime);
				}
			}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t al diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor.
/// \param    mask: La mascara de bits del valor.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
/// \remarks  La escriptura es posa en cua per un procesament posterior. Si
///           cal, es genera TPDO.
///
bool eos::CanOpenService::writeU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t value,
	uint32_t mask,
	Time blockTime) {

	auto ok = false;

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId != (typeof(entryId)) -1)
		if (_dictionary->canWrite(entryId)) {
			uint32_t oldValue;
			if (_dictionary->readU32(entryId, oldValue))
				if (_dictionary->writeU32(entryId, (oldValue & ~mask) | (value & mask))) {
					Message message = {
						.id {MessageID::entryChanged},
						.entryChanged {
							.entryId {entryId}
						}
					};
					ok = _messageQueue.push(message, blockTime);
				}
			}

	return ok;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor de uint8_t del diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool eos::CanOpenService::readU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

	return _dictionary->readU8(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor uint16_t del diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool eos::CanOpenService::readU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) {

	return _dictionary->readU16(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor uint32_t del diccionari local
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool eos::CanOpenService::readU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) {

	return _dictionary->readU32(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Posa un node en estat 'operational'.
/// \param    nodeId: Node destinatari.
/// \param    blockTie: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::start(
	NodeID nodeId,
	Time blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return eos::Result::ErrorCodes::errorParameter;

	else
		return emitNMT(0x01, nodeId, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Posar un node en estat 'stoped'
/// \param    nodeId: Node destinatati
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
eos::Result eos::CanOpenService::stop(
	NodeID nodeId,
	Time blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return eos::Result::ErrorCodes::errorParameter;

	else
		return emitNMT(0x02, nodeId, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Posar un node en estat 'pre-operational'.
/// \param    nodeId: Node destinatati
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::enterPreOperational(
	NodeID nodeId,
	Time blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return eos::Result::ErrorCodes::errorParameter;

	else
		return emitNMT(0x80, nodeId, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un node un node.
/// \param    nodeId: Node destinatati
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::resetNode(
	NodeID nodeId,
	Time blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return eos::Result::ErrorCodes::errorParameter;

	else
		return emitNMT(0x81, nodeId, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza les comunicacions d'un node.
/// \param    nodeId: Node destinatati
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::resetCommunication(
	NodeID nodeId,
	Time blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return eos::Result::ErrorCodes::errorParameter;

	else
		return emitNMT(0x82, nodeId, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Envia un TPDOx al bus
/// \param    tpdo: El identificador del TPDOx
///
void eos::CanOpenService::sendTPDO(
	uint8_t tpdo) {

	uint8_t maxCount;
	if (_dictionary->readU8(0x1A00 | tpdo, 0x00, maxCount) && maxCount > 0) {

		uint8_t data[8];
		uint8_t *pData = data;
		uint8_t dataLen = 0;

		// Mapeja els elements un a un
		//
		bool ok = true;
		for (auto count = 0; (count < maxCount) && ok; count++) {

			uint32_t mapInfo;
			ok = _dictionary->readU32(0x1A00 | tpdo, count + 1, mapInfo);
			if (ok) {

				uint16_t mapIndex = (mapInfo >> 16) & 0xFFFF;
				uint8_t mapSubIndex = (mapInfo >> 8) & 0xFF;
				unsigned mapLength = (mapInfo & 0xFF) / 8;

				auto entryId = _dictionary->find(mapIndex, mapSubIndex);
				ok = entryId != (unsigned) -1;
				if (ok) {
					switch (mapLength) {
						case 1:
							ok = (dataLen + sizeof(uint8_t)) < sizeof(data);
							if (ok) {
								uint8_t value;
								ok = _dictionary->readU8(entryId, value);
								if (ok) {
									*(pData++) = value;
									dataLen += sizeof(uint8_t);
								}
							}
							break;

						case 2:
							ok = (dataLen + sizeof(uint16_t)) < sizeof(data);
							if (ok) {
								uint16_t value;
								ok = _dictionary->readU16(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									dataLen += sizeof(uint16_t);
								}
							}
							break;

						case 4:
							ok = (dataLen + sizeof(uint32_t)) < sizeof(data);
							if (ok) {
								uint32_t value;
								ok = _dictionary->readU32(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									*(pData++) = (value >> 16) & 0xFF;
									*(pData++) = (value >> 24) & 0xFF;
									dataLen += sizeof(uint32_t);
								}
							}
							break;

						default:
							ok = false;
							break;
					}
				}
			}
		}

		if (ok) {
			uint32_t cobid;
			if (_dictionary->readU32(0x1800 + tpdo, 0x01, cobid))
				sendFrame(CobID(cobid & 0x7FF, _nodeId), data, dataLen, Time::fromMiliseconds(100));
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmet una trama.
/// \param    cobId: El identificador.
/// \param    data: Les dades.
/// \param    blockTime: Temps maxim d'espera.
/// \return   True si tot es correcte.
///
eos::Result eos::CanOpenService::sendFrame(
	CobID cobId,
	const uint8_t *data,
	uint32_t length,
	Time blockTime) {

	// Espera que el buffer no estigui ple
	//
	if (!_devCAN->waitTxBufferNotFull(blockTime).isOK())
		return Result::ErrorCodes::busy;

	// Prepara la trama
	//
	htl::can::DataLength len;
	switch (length) {
		case 1:
			len = htl::can::DataLength::len1;
			break;

		case 2:
			len = htl::can::DataLength::len2;
			break;

		case 3:
			len = htl::can::DataLength::len3;
			break;

		case 4:
			len = htl::can::DataLength::len4;
			break;

		case 5:
			len = htl::can::DataLength::len5;
			break;

		case 6:
			len = htl::can::DataLength::len6;
			break;

		case 7:
			len = htl::can::DataLength::len7;
			break;

		case 8:
			len = htl::can::DataLength::len8;
			break;

		default:
			return Result::ErrorCodes::errorParameter;
	}

	htl::can::TxHeader header = {
		.id = (uint16_t)  cobId,
		.idType = htl::can::IdentifierType::standard,
		.dataLength = len,
		.frameType = htl::can::FrameType::dataFrame,
		.errorStateFlag = htl::can::ErrorStateFlag::active,
		.bitrateSwitching = htl::can::BitrateSwitching::off,
		.fdFormat = htl::can::FDFormat::can,
		.txEventFifoControl = htl::can::TxEventFifoControl::noStore,
		.messageMarker = 0x00
	};

	// Afegeix la trama a la cua de sortida
	//
	auto result = _devCAN->addTxMessage(&header, data);
	if (!result.isOK())
		return result;

	// Espera que es transmiteixi, i si cal aborta la transmissio
	//
	if (!_devCAN->waitTxBufferEmpty(blockTime).isOK()) {
		_devCAN->abortTxBufferTransmission();
		return Result::ErrorCodes::timeout;
	}

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'event de notificacio del modul CAN.
/// \param    sender: El remitent. En aquest cas el modulCAN.
/// \param    aregs: Els parametres del missatge.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void eos::CanOpenService::canDevice_notificationEventHandler(
	htl::can::CANDevice * const sender,
	htl::can::CANDevice::NotificationEventArgs * const args) {

	static const uint8_t dataLenTbl[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
	};

	switch (args->id) {
		case htl::can::CANDevice::NotificationID::rxFifoNotEmpty: {

			Message message;
			htl::can::RxHeader rxHeader;

			_devCAN->getRxMessage(args->rxFifoNotEmpty.fifo, &rxHeader, message.frameReceived.data, sizeof(message.frameReceived));
			uint8_t dataLen = dataLenTbl[(unsigned)rxHeader.dataLength];

			message.id = MessageID::frameReceived;
			message.frameReceived.cobid = rxHeader.id;
			message.frameReceived.dataLen = dataLen;
			_messageQueue.pushISR(message);

			break;
		}

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Emet una trama
/// \param    cobId: El identificador.
/// \param    data: Les dades.
/// \param    length: La longitut de les dades en bytes.
/// \param    blockTime: Temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::emitFrame(
	CobID cobId,
	const uint8_t *data,
	uint32_t length,
	Time blockTime) {

	if (length > _canFrameSize)
		return eos::Result::ErrorCodes::errorParameter;

	Message message;
	message.id = MessageID::sendFrame;
	message.sendFrame.cobid = cobId;
	message.sendFrame.dataLen = length;
	if ((length > 0) && (data != nullptr))
		memcpy(message.sendFrame.data, data, length);

	return _messageQueue.push(message, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Emet un missatge NMT.
/// \param    command: La comanda.
/// \param    nodeId: Node destinatari.
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::emitNMT(
	uint8_t command,
	uint8_t nodeId,
	Time blockTime) {

	uint8_t data[2];
	data[0] = command;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	auto nmtMaster = reinterpret_cast<CanOpenNmtMaster*>(_nmtMaster);
	if (nmtMaster != nullptr)
		return nmtMaster->sendCommand(nodeId, (CanOpenNmtMaster::Command)command, blockTime);
	else
		return Result::ErrorCodes::errorUnsupported;
}


/// ----------------------------------------------------------------------
/// \brief    Emet un missatge SYNC
/// \param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
eos::Result eos::CanOpenService::emitSYNC(
	Time blockTime) {

	uint32_t options;
	if (_dictionary->readU32(0x1005, 0x00, options) &&
		eos::Bits::isSet(options, (uint32_t)(1 << 30))) {

		CobID cobId = CobID(options & 0x007F);

		return emitFrame(cobId, nullptr, 0, blockTime);
	}

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Emet un missatge RPDO
/// \brief    nodeId: El node desti.
/// \param    rpdoId: El idenfificador del RTPDO.
/// \param    data: Les dades a transmetre
/// \param    dataLen: La longitut de les dades a transmetre.
/// \return   El resultat de l'operacio.
///
eos::Result eos::CanOpenService::emitRPDO(
	NodeID nodeId,
	uint8_t rpdoId,
	const uint8_t *data,
	uint32_t dataLen,
	Time timeout) {

	Message message = {
		.id {MessageID::sendFrame},
		.sendFrame {
			.cobid {CobID(COBID::RPDO1, ((uint16_t)rpdoId << 8) | ((uint16_t)nodeId & 0x007F))},
			.dataLen {(uint8_t)dataLen}
		}
	};
	memcpy(message.sendFrame.data, data, dataLen);

	if (_messageQueue.push(message, timeout))
		return Result::ErrorCodes::ok;

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si una entrada esta mapejada en un TPDO
/// \param    tpdo: El TPDO
/// \param    entryId: El identificador de l'entrada.
/// \return   True si esta mapejada.
///
bool eos::CanOpenService::isMapped(
	uint8_t tpdo,
	uint32_t entryId) {

	uint8_t numMaps;
	if (_dictionary->readU8(0x1A00 + tpdo, 0, numMaps)) {
		for (auto i = 0; i < numMaps; i++) {

			uint32_t map;
			if (_dictionary->readU32(0x1A00 + tpdo, i + 1, map)) {

				uint16_t mapIndex = (map >> 16) & 0xFFFF;
				uint8_t mapSubIndex = (map >> 8) & 0xFF;
				if (entryId == _dictionary->find(mapIndex, mapSubIndex))
					return true;
			}
		}
	}

	return false;
}
