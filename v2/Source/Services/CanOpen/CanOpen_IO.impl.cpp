module Eos.Services.CanOpen;


using namespace eos;
using namespace eos::hardware::fdcan;


/// ---------------------------------------------------------------------------
/// @brief    Configura el dispositiu CAN
///
void CanOpenService::configureCANDevice() {

    CANDevice::InitParams initParams = {
    	.clockDivider = ClockDivider::div1,
		.frameFormat = FrameFormat::classic,
		.mode = Mode::normal,
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
		.qfMode = QFMode::fifo
    };
    _devCAN->initialize(&initParams);

    _devCAN->setGlobalFilter(
    	NonMatchingFrames::reject,
		NonMatchingFrames::reject,
		RejectRemoteFrames::filterRemote,
		RejectRemoteFrames::filterRemote);
}


/// ---------------------------------------------------------------------------
/// @brief    Configura els filtres CAN
///
void CanOpenService::configureCANFilters() {

	unsigned filterIndex = 0;

	Filter filter;
	filter.idType = IdentifierType::standard;
	filter.type = FilterType::mask;
	filter.config = FilterConfig::rxFifo0;

	// Accepta els missatges SDO que suporta aquest node
	// Si existeix l'entrada 1200:1, aleshores hi ha servidor SDO en el node,
	// en cas contrari no cal definir els filtres.
	//
	UInt32 cobidSDO;
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


/// ---------------------------------------------------------------------------
/// @brief    Transmet una trama.
/// @param    cobId: El identificador.
/// @param    data: Les dades.
/// @param    blockTime: Temps maxim d'espera.
/// \return   True si tot es correcte.
///
StdResult CanOpenService::transmitFrame(
	CobID cobId,
	const UInt8 *data,
	UInt32 length,
	Ticks blockTime) {

	// Espera que el buffer no estigui ple
	//
	if (!_devCAN->waitTxBufferNotFull(blockTime).isOk())
		return StdErrorCode::busy;

	// Prepara la trama
	//
	DataLength len;
	switch (length) {
		case 1:
			len = DataLength::len1;
			break;

		case 2:
			len = DataLength::len2;
			break;

		case 3:
			len = DataLength::len3;
			break;

		case 4:
			len = DataLength::len4;
			break;

		case 5:
			len = DataLength::len5;
			break;

		case 6:
			len = DataLength::len6;
			break;

		case 7:
			len = DataLength::len7;
			break;

		case 8:
			len = DataLength::len8;
			break;

		default:
			return StdErrorCode::errorParameter;
	}

	TxHeader header = {
		.id = (UInt16)  cobId,
		.idType = hardware::fdcan::IdentifierType::standard,
		.dataLength = len,
		.frameType = FrameType::dataFrame,
		.errorStateFlag = ErrorStateFlag::active,
		.bitrateSwitching = BitrateSwitching::off,
		.fdFormat = FDFormat::can,
		.txEventFifoControl = TxEventFifoControl::noStore,
		.messageMarker = 0x00
	};

	// Afegeix la trama a la cua de sortida
	//
	auto result = _devCAN->addTxMessage(&header, data);
	if (!result.isOk())
		return StdErrorCode::error;

	// Espera que es transmeti, i si cal aborta la transmissio
	//
	if (!_devCAN->waitTxBufferEmpty(blockTime).isOk()) {
		_devCAN->abortTxBufferTransmission();
		return StdErrorCode::timeout;
	}

	return StdErrorCode::ok;
}


/// ---------------------------------------------------------------------------
/// @brief    Gestiona l'event de notificacio del modul CAN.
/// @param    sender: El remitent. En aquest cas el modulCAN.
/// @param    aregs: Els parametres del missatge.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void CanOpenService::canDevice_notificationEventHandler(
	CANDevice *sender,
	CANDevice::NotificationEventArgs *args) {

	static const UInt8 dataLenTbl[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
	};

	switch (args->id) {
		case CANDevice::NotificationID::rxFifoNotEmpty: {

			Message message;
			RxHeader rxHeader;

			_devCAN->getRxMessage(args->rxFifoNotEmpty.fifo, &rxHeader, message.frameReceived.data, sizeof(message.frameReceived));
			UInt8 dataLen = dataLenTbl[(unsigned)rxHeader.dataLength];

			message.id = MessageID::frameReceived;
			message.frameReceived.cobid = rxHeader.id;
			message.frameReceived.dataLen = dataLen;
			_messageQueue.pushISR(message);

			break;
		}
	}
}
