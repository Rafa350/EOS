#include "eos.h"
#include "services/canopen/eos_canopen_dictionary.h"
#include "services/canopen/eos_canopen_service.h"
#include "services/canopen/eos_canopen_protocols.h"


using namespace eos;
using namespace htl;


constexpr const char *serviceName = "CanOpen";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 256;

constexpr unsigned defTimeout = 25;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
CanOpenService::CanOpenService(
	InitParams const &params) :

    _devCAN {params.devCAN},
	_dictionary {params.dictionary},
	_heartbeatTimerEvent {*this, &CanOpenService::heartbeatTimerEventHandler},
	_heartbeatTimer {true, _heartbeatTimerEvent},
	_canDeviceNotificationEvent {*this, &CanOpenService::canDeviceNotificationEventHandler},
	_nodeId {(uint8_t)(params.nodeId & 0x7F)},
	_nodeState {NodeState::initializing},
	_messageQueue {10} {
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

	configureCANDevice();
	configureCANFilters();
	configureHeartbeat();

    // Accepta notificacions del dispositiu.
	//
	_devCAN->setNotificationEvent(_canDeviceNotificationEvent);

	// Inicia el dispositiu FCAN en modus interrupcio.
	//
	_devCAN->start_IRQ();

	// Envia un boot-up (Heartbeat amb estat 'initializing')
	//
	emitHeartbeat((unsigned) -1);

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);

	while (!stopSignal()) {

		Message msg;
		while(_messageQueue.pop(msg, (unsigned) -1)) {
			switch (msg.id) {

				// S'ha rebut una trama CANOpen
				//
				case MessageID::frameReceived:
					processFrame(CobID(msg.frameReceived.cobid), msg.frameReceived.data, msg.frameReceived.dataLen);
					break;

				// Envia un trama CANOpen
				//
				case MessageID::sendFrame:
					sendFrame(CobID(msg.sendFrame.cobid), msg.sendFrame.data, msg.sendFrame.dataLen, 20);
					break;

				// Escriu un valor de 8 bits al diccionari
			    //
				case MessageID::writeU8:
					processWriteU8(msg.writeU8.entryId, msg.writeU8.value, msg.writeU8.mask);
					break;

				// Escriu un valor de 16 bits al diccionari
				//
				case MessageID::writeU16:
					processWriteU16(msg.writeU16.entryId, msg.writeU16.value, msg.writeU16.mask);
					break;

				// Escriu un valor de 32 bits al diccionari
				//
				case MessageID::writeU32:
					processWriteU8(msg.writeU32.entryId, msg.writeU32.value, msg.writeU32.mask);
					break;

				default:
					break;
			}
		}
	}

	_devCAN->stop();
}


/// ----------------------------------------------------------------------
/// \brief    Configura la generacio de heartbeat.
///
void CanOpenService::configureHeartbeat() {

	uint16_t interval;
	if (_dictionary->readU16(0x1017, 0, interval) && interval > 0)
		_heartbeatTimer.start(interval, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el dispositiu CAN
///
void CanOpenService::configureCANDevice() {

    can::CANDevice::InitParams initParams = {
    	.clockDivider = can::ClockDivider::div1,
		.frameFormat = can::FrameFormat::classic,
		.mode = can::Mode::normal,
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
		.qfMode = can::QFMode::fifo
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
void CanOpenService::configureCANFilters() {

	unsigned filterIndex = 0;

	can::Filter filter;
	filter.idType = can::IdentifierType::standard;
	filter.type = can::FilterType::mask;
	filter.config = can::FilterConfig::rxFifo0;

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
/// \brief    Genera un evenmt 'StateChangedNotification'
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
/// \brief    Genera un event 'SYNCReceived'
///
void CanOpenService::raiseSYNCReceivedEvent() {

	if (_erSYNCReceived.isEnabled()) {

		SYNCReceivedEventArgs args = {
		};

		_erSYNCReceived(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera una event 'ValueChangeRequestNotification'
/// \param    index: L'index de l'entrada.
/// \param    sunIndex: El subindex de l'entrada.
/// \param    value: El valor.
/// \param    fromBus: True si el canvi s'ha ordenat desde el bus.
///
void CanOpenService::raiseValueChangeRequestNotificationEvent(
		uint16_t index,
		uint8_t subIndex,
		uint8_t value,
		bool fromBus) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::valueChangeRequest},
			.valueChangeRequest {
				.index {index},
				.subIndex {subIndex},
				.value {value},
				.fromBus {fromBus}
			}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera una event 'ValueChangedNotification'
/// \param    index: L'index de l'entrada.
/// \param    sunIndex: El subindex de l'entrada.
/// \param    fromBus: True si el canvi s'ha ordenat desde el bus.
///
void CanOpenService::raiseValueChangedNotificationEvent(
	uint16_t index,
	uint8_t subIndex,
	bool fromBus) {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::valueChanged},
			.valueChanged {
				.index {index},
				.subIndex {subIndex},
				.fromBus {fromBus}
			}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event TPDOReceived.
/// \param    cobId: El COBID del TPDO
/// \param    data: Les dades.
/// \param    dataLen: La longitut de les dades.
///
void CanOpenService::raiseTPDOReceivedEvent(
	CobID cobId,
	const uint8_t *data,
	unsigned dataLen) {

	if (_erTPDOReceived.isEnabled()) {

		TPDOReceivedEventArgs args = {
			.cobId {cobId},
			.dataLen {(uint8_t)dataLen},
			.data {data}
		};

		_erTPDOReceived(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Genera un event HeartbeatReceived.
///
void CanOpenService::raiseHeartbeatReceivedEvent(
	uint8_t nodeId,
	NodeState state) {

	if (_erHeartbeatReceived.isEnabled()) {

		HeartbeatReceivedEventArgs args = {
			.nodeId {nodeId},
			.state {state}
		};

		_erHeartbeatReceived(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Realitza el canvi d'estat i notifica els canvis
/// \param    newNodeState: El nou estat
///
void CanOpenService::changeNodeState(
	NodeState newNodeState) {

	if (_nodeState != newNodeState) {
		beforeChangeNodeState();
		_nodeState = newNodeState;
		afterChangeNodeState();
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesos previs al canvi d'estat del node.
///
void CanOpenService::beforeChangeNodeState() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesos posteriors al canvi d'estat del node.
///
void CanOpenService::afterChangeNodeState() {

	raiseStateChangedNotificationEvent();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una trama
/// \param    cobId: El cobid de la trama.
/// \param    data: Les dades de la trama.
/// \param    dataLen: Longitut de les dades en bytes.
///
void CanOpenService::processFrame(
	CobID cobId,
	const uint8_t *data,
	unsigned dataLen) {

	if (cobId.isNMT())
		processNMT(data[0], data[1]);

	else if (cobId.isSYNC())
		processSYNC();

	else if (cobId.isTIME())
		processTIME();

	else if (cobId.isHeartbeat())
		processHeartbeat(cobId.nodeId(), data[0]);

	else if (cobId.base() == COBID::SDO)
		processSDO(data);

	else if ((cobId.base() == COBID::RPDO1) ||
		     (cobId.base() == COBID::RPDO2) ||
		     (cobId.base() == COBID::RPDO3) ||
		     (cobId.base() == COBID::RPDO4))
		processRPDO(cobId, data, dataLen);

	else if ((cobId.base() == COBID::TPDO1) ||
		     (cobId.base() == COBID::TPDO2) ||
		     (cobId.base() == COBID::TPDO3) ||
		     (cobId.base() == COBID::TPDO4))
	    processTPDO(cobId, data, dataLen);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges Heartbeat.
/// \param    nodeId: El node origen del missatge.
/// \param    state: L'estat del node.
///
void CanOpenService::processHeartbeat(
	uint8_t nodeId,
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

	raiseHeartbeatReceivedEvent(nodeId, nodeState);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges NMT
/// \param    command: La comanda NMT
/// \param    nodeId: El identificador del node on aplicar la comanda
///
void CanOpenService::processNMT(
	uint8_t command,
	uint8_t nodeId) {

	if (nodeId == _nodeId) {
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
void CanOpenService::processSDO(
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
		if (entryId == (unsigned) -1)
			errorCode = SdoError::objectDoesNotExistInDictionary;

		else {
			if (!_dictionary->canWrite(entryId))
				errorCode = SdoError::attemptToWriteReadOnlyObject;

			else {
				uint8_t size = 4 - ((data[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
				switch(size) {
					case 1: {
						uint8_t value = data[4];
						_dictionary->writeU8(entryId, value);
						break;
					}

					case 2: {
						uint16_t value = (data[4] << 8) | (data[5] << 16);
						_dictionary->writeU16(entryId, value);
						break;
					}

					case 4: {
						uint32_t value = data[4] | (data[5] << 8) | (data[6] << 16) |
								(data[7] << 24);
						_dictionary->writeU32(entryId, value);
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
				length = _dictionary->getDataLength(entryId);
				switch (length) {
					case 1: {
						uint8_t value;
						_dictionary->readU8(entryId, value);
						response[4] = value;
						break;
					}

					case 2: {
						uint16_t value;
						_dictionary->readU16(entryId, value);
						response[4] = value & 0xFF;
						response[5] = (value >> 8) & 0xFF;
						break;
					}

					case 4: {
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
		sendFrame(CobID(cobidSDOr & 0x7FF, _nodeId), response, sizeof(response), defTimeout);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges TIME
///
void CanOpenService::processTIME() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges SYNC
///
void CanOpenService::processSYNC() {

	raiseSYNCReceivedEvent();

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
void CanOpenService::processTPDO(
	CobID cobId,
	const uint8_t *data,
	unsigned dataLen) {

	raiseTPDOReceivedEvent(cobId, data, dataLen);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els missatges RPDO
/// \param    cobid: El COB-ID
/// \param    data: Dades del missatge.
///
void CanOpenService::processRPDO(
	CobID cobId,
	const uint8_t *data,
	unsigned dataLen) {

	uint32_t rpdoCOBID;
	if (_dictionary->readU32(0x1400, 0x01, rpdoCOBID) && rpdoCOBID == cobId.base()) {

		const uint8_t *pData = data;

		uint32_t map;
		if (_dictionary->readU32(0x1600, 0x01, map)) {
			uint16_t mapIndex = (map >> 16) & 0xFFFF;
			uint8_t mapSubIndex = (map >> 8) & 0xFF;
			uint8_t mapLength = (map & 0xFF) / 8;
			uint32_t value;

			unsigned entryId = _dictionary->find(mapIndex, mapSubIndex);
			if (entryId != (unsigned) -1) {
				bool ok = true;
				switch (mapLength) {
					case 1: {
						uint8_t u8 = 0;
						u8 |= *pData++;
						value = u8;
						break;
					}

					case 2: {
						uint16_t u16 = 0;
						u16 |= *pData++;
						u16 |= *pData++ << 8;
						value = u16;
						break;
					}

					case 4: {
						uint32_t u32 = 0;
						u32 |= *pData++;
						u32 |= *pData++ << 8;
						u32 |= *pData++ << 16;
						u32 |= *pData++ << 24;
						value = u32;
						break;
					}

					default:
						ok = false;
						break;
				}

				if (ok)
					raiseValueChangeRequestNotificationEvent(mapIndex, mapSubIndex, value, true);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una escriptura en el diccionari.
/// \param    entryId: L'entrada del diccionari.
/// \param    value: El valor.
/// \param    mask: Mascara de bits dels bits a canviar.
///
void CanOpenService::processWriteU8(
	unsigned entryId,
	uint8_t value,
	uint8_t mask) {

	uint8_t oldValue;
	if (_dictionary->readU8(entryId, oldValue)) {
		_dictionary->writeU8(entryId, (oldValue & ~mask) | (value & mask));
		processValueChanged(entryId, false);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una escriptura en el diccionari.
/// \param    entryId: L'entrada del diccionari.
/// \param    value: El valor.
/// \param    mask: Mascara de bits dels bits a canviar.
///
void CanOpenService::processWriteU16(
	unsigned entryId,
	uint16_t value,
	uint16_t mask) {

	uint16_t oldValue;
	if (_dictionary->readU16(entryId, oldValue)) {
		_dictionary->writeU16(entryId, (oldValue & ~mask) | (value & mask));
		processValueChanged(entryId, false);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una escriptura en el diccionari.
/// \param    entryId: L'entrada del diccionari.
/// \param    value: El valor.
/// \param    mask: Mascara de bits dels bits a canviar.
///
void CanOpenService::processWriteU32(
	unsigned entryId,
	uint32_t value,
	uint32_t mask) {

	uint32_t oldValue;
	if (_dictionary->readU32(entryId, oldValue)) {
		_dictionary->writeU32(entryId, (oldValue & ~mask) | (value & mask));
		processValueChanged(entryId, false);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa un canvi en el valor d'una entrada del diccionari
/// \param    entryId: Identificador de l'entrada que ha canviat de valor.
/// \param    raiseNotification: Indica si cal generar un event de notificacio.
///
void CanOpenService::processValueChanged(
	unsigned entryId,
	bool raiseNotification) {

	if (_nodeState == NodeState::operational) {

		// Comprova les entrades 0x1800 per si hi ha TPDO asincrones
		//
		uint8_t tpdoMax = 4;
		for (uint8_t tpdo = 0; tpdo < tpdoMax; tpdo++) {

			// Verifica que la entrada, estigui mapejada en un TPDO
			//
			if (isMapped(tpdo, entryId)) {
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

	if (raiseNotification) {
		auto index = _dictionary->getIndex(entryId);
		auto subIndex = _dictionary->getSubIndex(entryId);
		raiseValueChangedNotificationEvent(index, subIndex, false);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t al diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor.
/// \param    mask: La mascara de bits del valor.
/// \remarks  La escriptura es posa en cua per un procesament posterior. Si
///           cal, es genera TPDO.
///
void CanOpenService::writeU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value,
	uint8_t mask) {

	auto entryId = _dictionary->find(index, subIndex);
	if (_dictionary->canWrite(entryId)) {
		Message msg = {
			.id {MessageID::writeU8},
			.writeU8 {
				.entryId {entryId},
				.value {value},
				.mask {mask}
			}
		};
		_messageQueue.push(msg, (unsigned) -1);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor de 8 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

	return _dictionary->readU8(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor de 16 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) {

	return _dictionary->readU16(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor de 32 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) {

	return _dictionary->readU32(index, subIndex, value);
}


/// ----------------------------------------------------------------------
/// \brief    Envia un TPDOx
/// \param    tpdo: El identificador del TPDOx
///
void CanOpenService::sendTPDO(
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
				sendFrame(CobID(cobid & 0x7FF, _nodeId), data, dataLen, 100);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmet una trama.
/// \param    cobId: El identificador.
/// \param    data: Les dades.
/// \param    timeout: Temps maxim d'espera.
/// \return   True si tot es correcte.
///
Result CanOpenService::sendFrame(
	CobID cobId,
	const uint8_t *data,
	unsigned length,
	unsigned timeout) {

	// Espera que el buffer no estigui ple
	//
	if (!_devCAN->waitTxBufferNotFull(timeout).isOK())
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
			len = htl::can::DataLength::len0;
			break;
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
	if (!_devCAN->waitTxBufferEmpty(timeout).isOK()) {
		_devCAN->abortTxBufferTransmission();
		return Result::ErrorCodes::timeout;
	}

	return Result::ErrorCodes::ok;
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'event de notificacio del modul CAN
/// \param    sender: El remitent. En aquest cas el modulCAN
/// \param    aregs: Els parametres del missatge.
///
void CanOpenService::canDeviceNotificationEventHandler(
	htl::can::CANDevice * const sender,
	htl::can::CANDevice::NotificationEventArgs * const args) {

	static const uint8_t dataLenTbl[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
	};

	switch (args->id) {
		case htl::can::CANDevice::NotificationID::rxFifoNotEmpty: {

			Message msg;
			htl::can::RxHeader rxHeader;

			_devCAN->getRxMessage(args->rxFifoNotEmpty.fifo, &rxHeader, msg.frameReceived.data, sizeof(msg.frameReceived));
			uint8_t dataLen = dataLenTbl[(unsigned)rxHeader.dataLength];

			msg.id = MessageID::frameReceived;
			msg.frameReceived.cobid = rxHeader.id;
			msg.frameReceived.dataLen = dataLen;
			_messageQueue.pushISR(msg);

			break;
		}

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'event del temporitzador.
/// \param    sender: El remitent, en aquest cas el timer.
/// \param    args: Parametres del event.
///
void CanOpenService::heartbeatTimerEventHandler(
	Timer * const sender,
	Timer::TimerEventArgs * const args) {

	emitHeartbeat((unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge 'heartbeat'
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitHeartbeat(
	unsigned timeout) {

	uint8_t data = 0;
	switch (_nodeState) {
		case NodeState::initializing:
			data = 0;
			break;

		case NodeState::stoped:
			data = 4;
			break;

		case NodeState::preOperational:
			data = 0x7F;
			break;

		case NodeState::operational:
			data = 5;
			break;

		case NodeState::error:
			data = 0x80;
			break;
	}

	Message msg = {
		.id { MessageID::sendFrame},
		.sendFrame {
			.cobid {CobID::makeHeartbeat(_nodeId)},
			.dataLen {1},
			.data {data}
		}
	};

	if (_messageQueue.push(msg, timeout))
		return Result::ErrorCodes::ok;

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge SYNC
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitSYNC(
	unsigned timeout) {

	uint32_t options;
	if (_dictionary->readU32(0x1005, 0x00, options) &&
		htl::bits::isSet(options, (uint32_t)(1 << 30))) {

		Message msg = {
			.id { MessageID::sendFrame},
			.sendFrame {
				.cobid {CobID(options & 0x007F)},
				.dataLen {0}
			}
		};
		if (_messageQueue.push(msg, timeout))
			return Result::ErrorCodes::ok;
	}

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT.
/// \param    command: La comanda.
/// \param    nodeId: Node destinatari.
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitNMT(
	uint8_t command,
	uint8_t nodeId,
	unsigned timeout) {

	Message msg = {
		.id {MessageID::sendFrame},
		.sendFrame {
			.cobid {CobID::makeNMT()},
			.dataLen {2},
			.data {command, nodeId}
		}
	};
	if (_messageQueue.push(msg, timeout))
		return Result::ErrorCodes::ok;

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT per posar un node en
///           estat 'operational'.
/// \param    nodeId: Node destinatari.
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitNMT_StartNode(
	uint8_t nodeId,
	unsigned timeout) {

	return emitNMT(0x01, nodeId, timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT per posar un node en estat 'stoped'
/// \param    nodeId: Node destinatati
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
Result CanOpenService::emitNMT_StopNode(
	uint8_t nodeId,
	unsigned timeout) {

	return emitNMT(0x02, nodeId, timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT per posar un node en
///           estat 'pre-operational'.
/// \param    nodeId: Node destinatati
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitNMT_EnterPreOperational(
	uint8_t nodeId,
	unsigned timeout) {

	return emitNMT(0x80, nodeId, timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT per reiniciar un node.
/// \param    nodeId: Node destinatati
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitNMT_ResetNode(
	uint8_t nodeId,
	unsigned timeout) {

	return emitNMT(0x81, nodeId, timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge NMT per reiniciar nomes les
///           comunicacions d'un node.
/// \param    nodeId: Node destinatati
/// \param    timeout: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
Result CanOpenService::emitNMT_ResetCommunication(
	uint8_t nodeId,
	unsigned timeout) {

	return emitNMT(0x82, nodeId, timeout);
}


/// ----------------------------------------------------------------------
/// \brief    Genera un missatge RPDO
/// \brief    nodeId: El node desti.
/// \param    rpdoId: El idenfificador del RTPDO.
/// \param    data: Les dades a transmetre
/// \param    dataLen: La longitut de les dades a transmetre.
/// \return   El resultat de l'operacio.
///
Result CanOpenService::emitRPDO(
		uint8_t nodeId,
		uint8_t rpdoId,
		const uint8_t *data,
		unsigned dataLen,
		unsigned timeout) {

	Message msg = {
		.id {MessageID::sendFrame},
		.sendFrame {
			.cobid {CobID(COBID::RPDO1, ((uint16_t)rpdoId << 8) | ((uint16_t)nodeId & 0x007F))},
			.dataLen {(uint8_t)dataLen}
		}
	};
	memcpy(msg.sendFrame.data, data, dataLen);

	if (_messageQueue.push(msg,  timeout))
		return Result::ErrorCodes::ok;

	return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si una entrada esta mapejada en un TPDO
/// \param    tpdo: El TPDO
/// \param    entryId: El identificador de l'entrada.
/// \return   True si esta mapejada.
///
bool CanOpenService::isMapped(
	unsigned tpdo,
	unsigned entryId) {

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
