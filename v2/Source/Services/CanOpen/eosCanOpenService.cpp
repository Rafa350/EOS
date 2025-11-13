#include "eos.h"
#include "Services/CanOpen/eosCanOpenService.h"


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
	_dictionarySize {params.dictionarySize},
	_nodeId {params.nodeId},
	_nodeState {NodeState::bootup},
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


void CanOpenService::onExecute() {

	// Permet els missatges SDO dirigits especificament al node
	//
    can::Filter filter = {
       	.id1 = 0x600 | (_nodeId & 0x7F),
       	.id2 = 0x7FF,
		.idType = can::IdentifierType::standard,
		.type = can::FilterType::mask,
		.config = can::FilterConfig::rxFifo0
    };
    _devCAN->setFilter(&filter, 0);

	// Accepta notificacions del dispositiu.
	//
	_devCAN->setNotificationEvent(_canDeviceNotificationEvent, true);

	while (!stopSignal()) {

		Message msg;
		while(_queue.pop(msg, 1000)) {
			switch (msg) {
				case Message::rxFifo0: {

					htl::can::RxHeader rxHeader;
					uint8_t rxData[8];

					_devCAN->getRxMessage(htl::can::RxFifoSelection::fifo1, &rxHeader, rxData, sizeof(rxData));

					// Comprova si es el node receptor
					//
					if ((rxHeader.id & 0x7F) == _nodeId) {

						if ((rxHeader.id & ~0x007F) == 0x600)
							processSDO(&rxHeader, rxData);
					}
					break;
				}

				case Message::heartbeat:
					break;
			}
		}
	}
}


void CanOpenService::processSDO(
	const htl::can::RxHeader * rxHeader,
	const uint8_t *data) {

	unsigned nodeId = rxHeader->id & 0x7F;


	uint8_t cs = data[0];
	uint16_t index = data[1] | (data[2] << 8);
	uint8_t subIndex = data[3];
	uint32_t value = data[4] | (data[5] << 8) | (data[6] << 16) | (data [7] << 24);

	auto entry = findEntry(index, subIndex);
	if (entry != nullptr) {

		switch (cs) {
			case 0x22:
			case 0x23:
			case 0x2F:
			case 0x2B:
				if (entry->access == CoAccess::rw || entry->access == CoAccess::wo) {
					switch (entry->type) {
						case CoType::pu8:
							*((uint8_t*)entry->data) = value;
							break;

						case CoType::pu16:
							*((uint16_t*)entry->data) = value;
							break;

						case CoType::pu32:
							*((uint32_t*)entry->data) = value;
							break;

						case CoType::pb:
							*((bool*)entry->data) = value != 0;
							break;
					}
				}
				break;

			case 0x40:
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Envia un heartbeat al bus.
///
void CanOpenService::sendHeartbeat() {

	htl::can::TxHeader txHeader = {
		.id = 0x700 | (_nodeId & 0x7F),
		.idType = htl::can::IdentifierType::standard,
		.dataLength = htl::can::DataLength::len1,
		.frameType = htl::can::FrameType::dataFrame,
		.errorStateFlag = htl::can::ErrorStateFlag::active,
		.bitrateSwitching = htl::can::BitrateSwitching::off,
		.fdFormat = htl::can::FDFormat::can,
		.txEventFifoControl = htl::can::TxEventFifoControl::noStore,
		.messageMarker = 0x00
	};

	uint8_t txData;
	switch (_nodeState) {
		case NodeState::bootup:
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

	_devCAN->addTxMessage(&txHeader, &txData);
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


/// ----------------------------------------------------------------------
/// \brief    Busca una entrada del diccionari.
/// \param    index: L'index a buscar.
/// \param    subIndex: El subIndex a buscar.
/// \return   La entrada o null en cas d'error.
///
const CoDictionaryEntry * CanOpenService::findEntry(
	uint16_t index,
	uint8_t subIndex) const {

	auto ptr = _dictionary;
	auto end = &_dictionary[_dictionarySize];

	while (ptr != end) {
		if ((ptr->index == index) &&
			(ptr->subIndex == subIndex))
			return ptr;
	}

	return nullptr;
}
