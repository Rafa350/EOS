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
	_messageQueue {5} {

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
	sendHeartbeat();
	Task::delay(1000);

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);

	while (!stopSignal()) {

		Message msg;
		while(_messageQueue.pop(msg, (unsigned) -1)) {
			switch (msg.id) {

				// S'ha rebut un missatge CANOpen
				//
				case MessageID::canReceive:
					processFrame(msg.canReceive.cobid, msg.canReceive.data, msg.canReceive.dataLen);
					break;

				// Escriu un valor de 8 bits al diccionari
			    //
				case MessageID::odWriteU8:
					processWriteU8(msg.odWriteU8.entryId, msg.odWriteU8.value, msg.odWriteU8.mask);
					break;

				// Escriu un valor de 8 bits al diccionari
				//
				case MessageID::odWriteU16:
					processWriteU16(msg.odWriteU16.entryId, msg.odWriteU16.value, msg.odWriteU16.mask);
					break;

				// Escriu un valor de 8 bits al diccionari
				//
				case MessageID::odWriteU32:
					processWriteU8(msg.odWriteU32.entryId, msg.odWriteU32.value, msg.odWriteU32.mask);
					break;

				// Cal que enviar un headbeat.
				//
				case MessageID::heartbead:
					sendHeartbeat();
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
	if (readU16(0x1017, 0, interval) && interval > 0)
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
	if (readU32(0x1200, 0x01, cobidSDO)) {
		filter.id1 = (cobidSDO & 0x7FF) | _nodeId;
		filter.id2 = 0x7FFu;
		_devCAN->setFilter(&filter, filterIndex++);
	}

	// Accepta els missatges NMT
	//
	filter.id1 = COBID::NMT;
	filter.id2 = 0x7FFu;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges Headbead
	//
	filter.id1 = COBID::Heartbeat,
	filter.id2 = 0x780u;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges SYNC
	//
	filter.id1 = COBID::SYNC,
	filter.id2 = 0x7FFu;
	_devCAN->setFilter(&filter, filterIndex++);

	// Accepta els missatges TPDO
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
/// \brief    Genera un event 'SyncNotification'
///
void CanOpenService::raiseSyncNotificationEvent() {

	if (_erNotification.isEnabled()) {

		NotificationEventArgs args = {
			.id {NotificationID::sync}
		};

		_erNotification(this, &args);
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
/// \param    cobid: El cobid de la trama.
/// \param    data: Les dades de la trama.
/// \param    dataLen: Longitut de les dades en bytes.
///
void CanOpenService::processFrame(
	uint16_t cobid,
	const uint8_t *data,
	unsigned dataLen) {

	switch (cobid & 0xF80) {

		case COBID::SYNC:
			processSYNCFrame();
			break;

		case COBID::TIME:
			break;

		case COBID::NMT:
			processNMTFrame(data);
			break;

		case COBID::SDO:
			processSDOFrame(data);
			break;

		case COBID::RPDO1:
		case COBID::RPDO2:
		case COBID::RPDO3:
		case COBID::RPDO4:
			processRPDOFrame(cobid & 0xF80, data, dataLen);
			break;

		default:
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una trama NMT
/// \param    data: Dades del missatge.
///
void CanOpenService::processNMTFrame(
	const uint8_t *data) {

	if (data[1] == _nodeId) {
		switch (data[0]) {
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
/// \brief    Procesa una trama SDO
/// \param    data: Dades del missatge.
///
void CanOpenService::processSDOFrame(
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
	if (readU32(0x1200, 0x02, cobidSDOr))
		sendFrame((cobidSDOr & 0x7FF) | _nodeId, response, sizeof(response), defTimeout);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una trama SYNC
///
void CanOpenService::processSYNCFrame() {

	if (_nodeState == NodeState::operational) {

		raiseSyncNotificationEvent();

		// Comprova les  entrades 0x1800 per si hi han TPDOs sincrons
		// per enviar
		//
		uint8_t tpdoMax = 4;
		for (uint8_t tpdo = 0; tpdo < tpdoMax; tpdo++) {

			uint32_t flags;
			uint8_t transmissionType;

			if (readU32(0x1800 + tpdo, 0x01, flags) &&
				readU8(0x1800 + tpdo, 0x02, transmissionType)) {

				if ((transmissionType <= 240) && ((flags & (1 << 31)) == 0))
					sendTPDO(tpdo);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa una trama RPDO
/// \param    cobid: El COB-ID
/// \param    data: Dades del missatge.
///
void CanOpenService::processRPDOFrame(
	uint16_t cobid,
	const uint8_t *data,
	unsigned dataLen) {

	uint32_t rpdoCOBID;
	if (readU32(0x1400, 0x01, rpdoCOBID) && rpdoCOBID == cobid) {

		const uint8_t *pData = data;

		uint32_t map;
		if (readU32(0x1600, 0x01, map)) {
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

	// Procesa TPDO's asociat a event de cavi de valor
	//
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

				if (readU32(0x1800 + tpdo, 0x01, flags) &&
					readU8(0x1800 + tpdo, 0x02, transmissionType)) {

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
void CanOpenService::odWriteU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t value,
	uint8_t mask) {

	auto entryId = _dictionary->find(index, subIndex);
	if (_dictionary->canWrite(entryId)) {
		Message msg = {
			.id {MessageID::odWriteU8},
			.odWriteU8 {
				.entryId {entryId},
				.value {value},
				.mask {mask}
			}
		};
		_messageQueue.push(msg, (unsigned) -1);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Envia un 'heartbeat' al bus.
///
void CanOpenService::sendHeartbeat() {

	uint16_t cobid = COBID::Heartbeat | (_nodeId & 0x7F);
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

	sendFrame(cobid, &data, sizeof(data), defTimeout);
}


/// ----------------------------------------------------------------------
/// \brief    Envia un TPDOx
/// \param    tpdo: El identificador del TPDOx
///
void CanOpenService::sendTPDO(
	uint8_t tpdo) {

	uint8_t maxCount;
	if (readU8(0x1A00 | tpdo, 0x00, maxCount) && maxCount > 0) {

		uint8_t data[8];
		uint8_t *pData = data;
		uint8_t dataLen = 0;

		// Mapeja els elements un a un
		//
		bool ok = true;
		for (auto count = 0; (count < maxCount) && ok; count++) {

			uint32_t mapInfo;
			ok = readU32(0x1A00 | tpdo, count + 1, mapInfo);
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
			if (readU32(0x1800 + tpdo, 0x01, cobid))
				sendFrame((cobid & 0x7FF) | _nodeId, data, dataLen, 100);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Transmet una trama.
/// \param    cobid: El identificador.
/// \param    data: Les dades.
/// \param    timeout: Temps maxim d'espera.
/// \return   True si tot es correcte.
///
Result CanOpenService::sendFrame(
	uint16_t cobid,
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
		.id = cobid,
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
		case htl::can::CANDevice::NotificationID::rxFifoNotEmpty:

			Message msg;

			htl::can::RxHeader rxHeader;
			_devCAN->getRxMessage(args->rxFifoNotEmpty.fifo, &rxHeader, msg.canReceive.data, sizeof(msg.canReceive.data));

			msg.id = MessageID::canReceive;
			msg.canReceive.dataLen = dataLenTbl[(unsigned)rxHeader.dataLength];
			msg.canReceive.cobid = rxHeader.id;

			_messageQueue.pushISR(msg);

			break;

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

	Message msg;

	msg.id = MessageID::heartbead;
	_messageQueue.push(msg, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un valor de 8 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor obtingut.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) const {

	auto entryId = _dictionary->find(index, subIndex);

	if (entryId == (unsigned) -1)
		return false;
	else
		return _dictionary->readU8(entryId, value);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un valor de 16 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor obtingut.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU16(
	uint16_t index,
	uint8_t subIndex,
	uint16_t &value) const {

	auto entryId = _dictionary->find(index, subIndex);

	if (entryId == (unsigned) -1)
		return false;
	else
		return _dictionary->readU16(entryId, value);
}


/// ----------------------------------------------------------------------
/// \brief    Obte un valor de 32 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: El subindex.
/// \param    value: El valor obtingut.
/// \return   True si tot es correcte.
///
bool CanOpenService::readU32(
	uint16_t index,
	uint8_t subIndex,
	uint32_t &value) const {

	auto entryId = _dictionary->find(index, subIndex);

	if (entryId == (unsigned) -1)
		return false;
	else
		return _dictionary->readU32(entryId, value);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor de 8 bits del diccionari
/// \param    index: L'index.
/// \param    subIndex: EWl subindex.
/// \param    El valor lleigit.
/// \return   True si tot es correcte.
///
bool CanOpenService::odReadU8(
	uint16_t index,
	uint8_t subIndex,
	uint8_t &value) {

	auto entryId = _dictionary->find(index, subIndex);
	if (entryId == (unsigned) -1)
		return false;
	else
		return _dictionary->readU8(entryId, value);
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
	if (readU8(0x1A00 + tpdo, 0, numMaps)) {
		for (auto i = 0; i < numMaps; i++) {

			uint32_t map;
			if (readU32(0x1A00 + tpdo, i + 1, map)) {

				uint16_t mapIndex = (map >> 16) & 0xFFFF;
				uint8_t mapSubIndex = (map >> 8) & 0xFF;
				if (entryId == _dictionary->find(mapIndex, mapSubIndex))
					return true;
			}
		}
	}

	return false;
}
