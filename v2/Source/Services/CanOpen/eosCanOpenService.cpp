module;


#include "eos.h"
#include "eosTime.h"
#include "rtos/rtosTask.h"
#include "HTL/STM32/htlCAN.h"
#include "RTOS/rtosTimer.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"
#include "Services/canopen/eosCanOpenProtocol.h"
#include "System/Core/eosQueue.h"


export module Eos.Services.CanOpen;


import Eos.Math;
import Eos.Services.Service;


export namespace eos {

	using NodeID = uint8_t;

	class CobID {
		private:
			static constexpr uint16_t _baseNMT = COBID::NMT;
			static constexpr uint16_t _baseSYNC = COBID::SYNC;
			static constexpr uint16_t _baseTIME = COBID::TIME;
			static constexpr uint16_t _baseHeartbeat = COBID::Heartbeat;

		private:
			uint16_t _value;

		public:
			constexpr explicit CobID(uint16_t value): _value {value & 0x7FF} {}
			constexpr explicit CobID(uint16_t base, NodeID nodeId): _value {(base & 0x780) | (nodeId & 0x7F)} {}

			inline operator uint16_t() const { return value(); }
			inline bool operator == (CobID other) const { return _value == other._value; }
			inline bool operator != (CobID other) const { return _value != other._value; }

			inline uint16_t value() const { return _value; }
			inline uint16_t base() const { return _value & 0x780; }
			inline NodeID nodeId() const { return _value & 0x7F; }

			inline bool isNMT() const { return _value == _baseNMT; }
			inline bool isSYNC() const { return _value == _baseSYNC; }
			inline bool isTIME() const { return _value == _baseTIME; }
			inline bool isHeartbeat() const { return (_value & 0x780) == _baseHeartbeat; }

			static constexpr CobID makeNMT() { return CobID(_baseNMT); }
			static constexpr CobID makeSYNC() { return CobID(_baseSYNC); }
			static constexpr CobID makeTIME() { return CobID(_baseTIME); }
			static constexpr CobID makeHeartbeat(NodeID nodeId) { return CobID(_baseHeartbeat, nodeId); }
	};

	class CanOpenService final: public Service {
		public:
        	enum class NodeState {
        		initializing,
        		stoped,
        		preOperational,
				operational,
				error
        	};

        	enum class NotificationID {
				stateChanged
			};
        	struct NotificationEventArgs {
        		NotificationID id;
        		union {
        			struct {
        				NodeState state;
        			} stateChanged;
        		};
        	};
        	using NotificationEventRaiser = EventRaiser<CanOpenService, NotificationEventArgs>;
			using INotificationEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

			struct WriteRequestEventArgs {
				uint16_t index;
				uint8_t subIndex;
				union {
					uint8_t u8;
					uint16_t u16;
					uint32_t u32;
					bool b;
				} value;
			};
			using WriteRequestEventRaiser = EventRaiser<CanOpenService, WriteRequestEventArgs>;
			using IWriteRequestEvent = WriteRequestEventRaiser::IEvent;
			template <typename Instance_> using WriteRequestEvent = WriteRequestEventRaiser::Event<Instance_>;

			struct TPDOReceivedEventArgs {
				CobID cobId;
				uint8_t dataLen;
				const uint8_t *data;
			};
			using TPDOReceivedEventRaiser = EventRaiser<CanOpenService, TPDOReceivedEventArgs>;
			using ITPDOReceivedEvent = TPDOReceivedEventRaiser::IEvent;
			template <typename Instance_> using TPDOReceivedEvent = TPDOReceivedEventRaiser::Event<Instance_>;

			struct SYNCReceivedEventArgs {
			};
			using SYNCReceivedEventRaiser = EventRaiser<CanOpenService, SYNCReceivedEventArgs>;
			using ISYNCReceivedEvent = SYNCReceivedEventRaiser::IEvent;
			template <typename Instance_> using SYNCReceivedEvent = SYNCReceivedEventRaiser::Event<Instance_>;

			struct HeartbeatReceivedEventArgs {
				NodeID nodeId;
				NodeState nodeState;
			};
			using HeartbeatReceivedEventRaiser = EventRaiser<CanOpenService, HeartbeatReceivedEventArgs>;
			using IHeartbeatReceivedEvent = HeartbeatReceivedEventRaiser::IEvent;
			template <typename Instance_> using HeartbeatReceivedEvent = HeartbeatReceivedEventRaiser::Event<Instance_>;

			struct InitParams {
				htl::can::CANDevice * devCAN;
				NodeID nodeId;
				CanOpenDictionary *dictionary;
			};

		private:
			static constexpr uint32_t _messageQueueSize = 15;
			static constexpr uint32_t _canFrameSize = 8;

		private:
			enum class MessageID {
				initialized,
				entryChanged,
				frameReceived,
				transmitFrame,
				changeNodeState
			};
			struct EntryChanged {
				uint32_t entryId;
			};
			struct FrameReceived {
				uint16_t cobid;
				uint8_t dataLen;
				uint8_t data[_canFrameSize];
			};
			struct TransmitFrame {
				uint16_t cobid;
				uint8_t dataLen;
				uint8_t data[_canFrameSize];
			};
			struct ChangeNodeState {
				NodeState nodeState;
			};
			struct Message {
				MessageID id;
				union {
					EntryChanged entryChanged;
					FrameReceived frameReceived;
					TransmitFrame transmitFrame;
					ChangeNodeState changeNodeState;
				};
			};
        	using MessageQueue = Queue<Message>;

		private:
			htl::can::CANDevice * const _devCAN;
			htl::can::CANDevice::NotificationEvent<CanOpenService> _canDevice_notificationEvent;
			rtos::Timer::Event<CanOpenService> _timer_notificationEvent;
			rtos::Timer _timer;
        	CanOpenDictionary * const _dictionary;
			NodeID const _nodeId;
			NodeState _nodeState;
			MessageQueue _messageQueue;
			NotificationEventRaiser _notificationEventRaiser;
			WriteRequestEventRaiser _writeRequestEventRaiser;
			TPDOReceivedEventRaiser _tpdoReceivedEventRaiser;
        	SYNCReceivedEventRaiser _syncReceivedEventRaiser;
        	HeartbeatReceivedEventRaiser _heartbeatReceivedEventRaiser;

		private:
            void canDevice_notificationEventHandler(htl::can::CANDevice *sender, htl::can::CANDevice::NotificationEventArgs *args);
			void timer_notificationEventHandler(rtos::Timer *timer, rtos::Timer::EventArgs *args);

            void configureCANDevice();
            void configureCANFilters();
            void configureHeartbeat();

            void processMessage(const Message &message);
            void processMessage_Initialized();
			void processMessage_FrameReceived(const FrameReceived &args);
			void processMessage_FrameReceived_NMT(const FrameReceived &args);
			void processMessage_FrameReceived_Heartbeat(const FrameReceived &args);
			void processMessage_FrameReceived_TPDO(const FrameReceived &args);
			void processMessage_FrameReceived_SYNC(const FrameReceived &args);
			void processMessage_FrameReceived_TIME(const FrameReceived &args);
            void processMessage_FrameReceived_SDO(const FrameReceived &args);
			void processMessage_FrameReceived_RPDO(const FrameReceived &args);
            void processMessage_EntryChanged(const EntryChanged &args);
            void processMessage_ChangeNodeState(const ChangeNodeState &args);
            void processMessage_TransmitFrame(const TransmitFrame &args);

            Result postMessage_TransmitFrame(CobID cobId, const uint8_t *data, uint32_t length, Time blockTime);

            void processSDO(const uint8_t *data);
			void processRPDO(CobID cobId, const uint8_t *data, uint32_t dataLen);

			void sendTPDO(uint8_t tpdo);

			bool isMapped(uint8_t tpdo, uint32_t entryId);

			Result transmitFrame(CobID cobId, const uint8_t *data, uint32_t length, Time blockTime);

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

			Result emitNMT(uint8_t command, NodeID nodeId, Time blockTime);

            void onNodeStateChanged();

            void onWriteU8Request(uint16_t index, uint8_t subIndex, uint8_t value);
            void onWriteU16Request(uint16_t index, uint8_t subIndex, uint16_t value);
            void onWriteU32Request(uint16_t index, uint8_t subIndex, uint32_t value);
            void onSYNCReceived();
			void onTPDOReceived(CobID cobId, const uint8_t *data, uint32_t dataLen);
			void onHeartbeatReceived(NodeID nodeId, NodeState nodeState);

            void changeNodeState(NodeState newNodeState);

		public:
			CanOpenService(InitParams const &params);
			CanOpenService(const CanOpenService &) = delete;
			CanOpenService(const CanOpenService &&) = delete;

			Result setNodeState(NodeState nodeState, Time blockTime);
			NodeState getNodeState() const;
			NodeID getNodeId() const;

            // Lectura i escriptura en el dicionari local
            //
            bool writeU8(uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask, Time blockTime);
            bool writeU16(uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask, Time blockTime);
            bool writeU32(uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask, Time blockTime);
            bool readU8(uint16_t index, uint8_t subIndex, uint8_t &value);
            bool readU16(uint16_t index, uint8_t subIndex, uint16_t &value);
            bool readU32(uint16_t index, uint8_t subIndex, uint32_t &value);

            // Lectura i escriptura en el dicionari remot (Protocol SDO)
            //
            bool writeU8(NodeID nodeId, uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask);
            bool writeU16(NodeID nodeId, uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask);
            bool writeU32(NodeID nodeId, uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask);
            bool readU8(NodeID nodeId, uint16_t index, uint8_t subIndex, uint8_t &value);
            bool readU16(NodeID nodeId, uint16_t index, uint8_t subIndex, uint16_t &value);
            bool readU32(NodeID nodeId, uint16_t index, uint8_t subIndex, uint32_t &value);

            // Canvia l'estat d'un node remot (Protocol NMT)
            //
			Result start(NodeID nodeId, Time blockTime);
			Result stop(NodeID nodeId, Time blockTime);
			Result enterPreOperational(NodeID nodeId, Time blockTime);
			Result resetNode(NodeID nodeId, Time blockTime);
			Result resetCommunication(NodeID nodeId, Time blockTime);

            // Senyal de sincronitzacio al bus (Protocol SYNC)
            //
            Result emitSYNC(Time timeout);

			// Emet missatges RPDO
			//
			Result emitRPDO(NodeID nodeId, uint8_t rpdoId, const uint8_t *data, uint32_t dataLen, Time timeout);

			// Habilita i deshabilita els events
			//
            void enableNotificationEvent(INotificationEvent &event);
            void disableNotificationEvent();

			void enableWriteRequestEvent(IWriteRequestEvent &event);
			void disableWriteRequestEvent();

			void enableSYNCReceivedEvent(ISYNCReceivedEvent &event);
			void disableSYNCReceivedEvent();

			void enableTPDOReceivedEvent(ITPDOReceivedEvent &event);
			void disableTPDOReceivedEvent();

			void enableHeartbeatReceivedEvent(IHeartbeatReceivedEvent &event);
			void disbleHeartbeatReceivedEvent();
	};
}


constexpr const char *serviceName = "CanOpen";
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::normal;
constexpr uint32_t serviceStackDepth = 256 + 64;

constexpr unsigned defTimeout = 25;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    params: Els parametres d'inicialitzacio
///
eos::CanOpenService::CanOpenService(
	InitParams const &params) :

    _devCAN {params.devCAN},
	_canDevice_notificationEvent {*this, &CanOpenService::canDevice_notificationEventHandler},
	_timer_notificationEvent {*this, &CanOpenService::timer_notificationEventHandler},
	_timer {rtos::Timer::Mode::autoRestart, nullptr, _timer_notificationEvent},
	_dictionary {params.dictionary},
	_nodeId {(uint8_t)(params.nodeId & 0x7F)},
	_nodeState {NodeState::initializing},
	_messageQueue {_messageQueueSize} {
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

	// Configura les comunicacions CAN
	//
	configureCANDevice();
	configureCANFilters();

	// Configura la generacio de heartbeat
	//
	configureHeartbeat();

    // Inicia les comunicacions CAN
	//
	_devCAN->enableNotificationEvent(_canDevice_notificationEvent);
	_devCAN->start_IRQ();

	// Genera el missatge 'initialized' i el porta a la cua
	//
	Message msg;
	msg.id = MessageID::initialized;
	_messageQueue.push(msg, eos::Times::infinite);

	// Repeteix mentre no es canceli la tasca
	//
	while (!stopSignal()) {

		// Procesa els missatges de la cua
		//
		Message message;
		while(_messageQueue.pop(message, Time::fromMiliseconds(1000)))
			processMessage(message);
	}

	// Finalitza les comunicacions CAN
	//
	_devCAN->stop();
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
/// \brief    Configura la produccio dels heartbeats.
///
void eos::CanOpenService::configureHeartbeat() {

	// Obte l'interval entre beats.
	//
	uint16_t interval;
	if (readU16(0x1017, 0, interval) && interval > 0) {

		// Activa el temporitzador
		//
		_timer.start(Time::fromMiliseconds(interval), Time::fromMiliseconds(100));
	}
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
/// \brief    Procesa els missatges
/// \param    message: El missatge a procesar.
///
void eos::CanOpenService::processMessage(
	const Message &message) {

	switch (message.id) {

		// Notifica que el node s'acaba d'inicialitzar.
		//
		case MessageID::initialized:
			processMessage_Initialized();
			break;

		// Notifica que ha canviat una entrada del diccionari
		//
		case MessageID::entryChanged:
			processMessage_EntryChanged(message.entryChanged);
			break;

		// Notifica que s'ha rebut una trama CANOpen
		//
		case MessageID::frameReceived:
			processMessage_FrameReceived(message.frameReceived);
			break;

		// Ordena canviar l'estat del node.
		//
		case MessageID::changeNodeState:
			processMessage_ChangeNodeState(message.changeNodeState);
			break;

		// Ordena enviar enviar un trama CANOpen
		//
		case MessageID::transmitFrame:
			processMessage_TransmitFrame(message.transmitFrame);
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'initialized'
///
void eos::CanOpenService::processMessage_Initialized() {

	// Emet un boot-up
	//
	uint8_t data[1];
	data[0] =  0;

	CobID cobId = CobID::makeHeartbeat(_nodeId);

	transmitFrame(cobId, data, sizeof(data), Time::fromMiliseconds(100));

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'entryChanged'
/// \param    args: Els parametres del missatge.
///
void eos::CanOpenService::processMessage_EntryChanged(
	const EntryChanged &args) {

	// Si esta en modus operacional, comprova si cal generar TPDO's
	//
	if (_nodeState == NodeState::operational) {

		// Comprova les entrades 0x1800 per si hi ha TPDO asincrones
		//
		uint8_t tpdoMax = 4;
		for (uint8_t tpdo = 0; tpdo < tpdoMax; tpdo++) {

			// Verifica que la entrada, estigui mapejada en un TPDO
			//
			if (isMapped(tpdo, args.entryId)) {
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
/// \param    args: Els parametres del missatge.
///
void eos::CanOpenService::processMessage_ChangeNodeState(
	const ChangeNodeState &args) {

	changeNodeState(args.nodeState);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'sendFrame'
/// \param    args: Els parametres del missatge.
///
void eos::CanOpenService::processMessage_TransmitFrame(
	const TransmitFrame &args) {

	transmitFrame(
		CobID(args.cobid),
		args.data,
		args.dataLen,
		Time::fromMiliseconds(50));
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived'
/// \param    args: Els parammetres del missatge.
///
void eos::CanOpenService::processMessage_FrameReceived(
	const FrameReceived &args) {

	CobID cobId(args.cobid);

	if (cobId.isNMT())
		processMessage_FrameReceived_NMT(args);

	else if (cobId.isSYNC())
		processMessage_FrameReceived_SYNC(args);

	else if (cobId.isTIME())
		processMessage_FrameReceived_TIME(args);

	else if (cobId.isHeartbeat())
		processMessage_FrameReceived_Heartbeat(args);

	else if (cobId.base() == COBID::SDO)
		processMessage_FrameReceived_SDO(args);

	else if ((cobId.base() == COBID::RPDO1) ||
		     (cobId.base() == COBID::RPDO2) ||
		     (cobId.base() == COBID::RPDO3) ||
		     (cobId.base() == COBID::RPDO4))
		processMessage_FrameReceived_RPDO(args);

	else if ((cobId.base() == COBID::TPDO1) ||
		     (cobId.base() == COBID::TPDO2) ||
		     (cobId.base() == COBID::TPDO3) ||
		     (cobId.base() == COBID::TPDO4))
	    processMessage_FrameReceived_TPDO(args);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' Heartbeat.
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_Heartbeat(
	const FrameReceived &args) {

	auto state = args.data[0];
	auto nodeId = CobID(args.cobid).nodeId();

	if ((_nodeState == NodeState::preOperational) ||
		(_nodeState == NodeState::operational)) {

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
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' NMT
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_NMT(
	const FrameReceived &args) {

	auto comand = args.data[0];
	auto nodeId = args.data[1];

	if ((_nodeState == NodeState::preOperational) ||
		(_nodeState == NodeState::operational) ||
		(_nodeState == NodeState::stoped)) {

		if ((nodeId == _nodeId) || (nodeId == 0)) {
			switch (comand) {
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
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' SDO
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_SDO(
	const FrameReceived &args) {

	uint8_t response[8];
	uint32_t errorCode = SdoError::none;

	// Comprova l'estat del node
	//
	if ((_nodeState != NodeState::preOperational) &&
		(_nodeState != NodeState::operational))
		errorCode = SdoError::unsupportedAccesssToObject;

	// Initiate SDO download (Expedited)
	//
	else if ((args.data[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP)) {

		uint16_t index = args.data[1] | (args.data[2] << 8);
		uint8_t subIndex = args.data[3];

		auto entryId = _dictionary->find(index, subIndex);
		if (entryId == (typeof(entryId)) -1)
			errorCode = SdoError::objectDoesNotExistInDictionary;

		else {
			if (!_dictionary->canWrite(entryId))
				errorCode = SdoError::attemptToWriteReadOnlyObject;

			else {
				uint8_t size = 4 - ((args.data[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8: {
						uint8_t value = args.data[4];
						onWriteU8Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned16: {
						uint16_t value = (args.data[4] << 8) | (args.data[5] << 16);
						onWriteU16Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned32: {
						uint32_t value = args.data[4] | (args.data[5] << 8) | (args.data[6] << 16) |
								(args.data[7] << 24);
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
	else if ((args.data[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_SEG)) {
		//onInitiateDownloadNormal(query, response);
	}

	// Download segment
	//
	else if ((args.data[0] & SDO0::CCS_Msk) == SDO0::CCS_DNSEG) {
		//onDownloadSegment(query, response);
	}

	// Initiate SDO upload
	//
	else if ((args.data[0] & SDO0::CCS_Msk) == SDO0::CCS_UP) {

		uint16_t index = args.data[1] | (args.data[2] << 8);
		uint8_t subIndex = args.data[3];
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
	else if ((args.data[0] & SDO0::CCS_Msk) == SDO0::CCS_UPSEG) {
		//onUploadSegment(query, response);
	}

	// Error SDO
	//
	else
		errorCode = SdoError::commandSpecifierNotValid;

	// Prepara la resposta
	//
	response[1] = args.data[1];
	response[2] = args.data[2];
	response[3] = args.data[3];
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
		transmitFrame(CobID(cobidSDOr & 0x7FF, _nodeId), response, sizeof(response), Time::fromMiliseconds(defTimeout));
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' TIME
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_TIME(
	const FrameReceived &args) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' SYNC
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_SYNC(
	const FrameReceived &args) {

	if (_nodeState == NodeState::operational) {

		onSYNCReceived();

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
/// \brief    Procesa els missatges 'FrameReceived' TPDO
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_TPDO(
	const FrameReceived &args) {

	if (_nodeState == NodeState::operational) {

		// Notifica a l'aplicacio que hi ha un TPDO per procesar provinent d'un
		// node remot
		//
		onTPDOReceived(CobID(args.cobid), args.data, args.dataLen);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el missatge 'FrameReceived' RPDO
/// \param    args: Parametres del missatge
///
void eos::CanOpenService::processMessage_FrameReceived_RPDO(
	const FrameReceived &args) {

	auto cobId = CobID(args.cobid);

	uint32_t rpdoCOBID;
	if (_dictionary->readU32(0x1400, 0x01, rpdoCOBID) && (rpdoCOBID == cobId.base())) {

		const uint8_t *pData = args.data;

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


/// ----------------------------------------------------------------------
/// \brief    Obte l'identificador del node.
/// \return   El identificador del node.
///
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
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
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
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
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
/// \remarks  La notificacio 'EntryChanged' es posa en cua.
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
/// \param    blockTime: El temps maxim d'espera.
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

	// Emet la comanda NMT Start
	//
	uint8_t data[2];
	data[0] = 0x01;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return postMessage_TransmitFrame(cobId, data, sizeof(data), blockTime);
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

	// Emet la comanda NMT Stop
	//
	uint8_t data[2];
	data[0] = 0x02;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return postMessage_TransmitFrame(cobId, data, sizeof(data), blockTime);
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

	// Emet la comanda NMT Enter Pre-Operational
	//
	uint8_t data[2];
	data[0] = 0x80;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return postMessage_TransmitFrame(cobId, data, sizeof(data), blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Reseteja un node..
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

	// Emet la comanda NMT Reset Node
	//
	uint8_t data[2];
	data[0] = 0x81;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return postMessage_TransmitFrame(cobId, data, sizeof(data), blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Reseteja les comunicacions d'un node.
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

	// Emet la comanda NMT Rerset Comunication
	//
	uint8_t data[2];
	data[0] = 0x82;
	data[1] = nodeId;

	CobID cobId = CobID::makeNMT();

	return postMessage_TransmitFrame(cobId, data, sizeof(data), blockTime);
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
				transmitFrame(CobID(cobid & 0x7FF, _nodeId), data, dataLen, Time::fromMiliseconds(100));
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
eos::Result eos::CanOpenService::transmitFrame(
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
/// \brief    Procesa els events de notificacio del temporitzador.
/// \param    sender: El remitent del missatge.
/// \param    args: Parametres del event.
///
void eos::CanOpenService::timer_notificationEventHandler(
	rtos::Timer *sender,
	rtos::Timer::EventArgs *args) {

	uint8_t data[1];
	switch (_nodeState) {
		case CanOpenService::NodeState::stoped:
			data[0] = 4;
			break;

		case CanOpenService::NodeState::preOperational:
			data[0] = 0x7F;
			break;

		case CanOpenService::NodeState::operational:
			data[0] = 5;
			break;

		case CanOpenService::NodeState::error:
			data[0] = 0x80;
			break;

		default:
			return;
	}

	CobID cobId = CobID::makeHeartbeat(_nodeId);

	postMessage_TransmitFrame(cobId, data, sizeof(data), Time::fromMiliseconds(100));
}


/// ----------------------------------------------------------------------
/// \brief    Gestiona l'event de notificacio del modul CAN.
/// \param    sender: El remitent. En aquest cas el modulCAN.
/// \param    aregs: Els parametres del missatge.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void eos::CanOpenService::canDevice_notificationEventHandler(
	htl::can::CANDevice *sender,
	htl::can::CANDevice::NotificationEventArgs *args) {

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
eos::Result eos::CanOpenService::postMessage_TransmitFrame(
	CobID cobId,
	const uint8_t *data,
	uint32_t length,
	Time blockTime) {

	if (length > _canFrameSize)
		return eos::Result::ErrorCodes::errorParameter;

	Message message;
	message.id = MessageID::transmitFrame;
	message.transmitFrame.cobid = cobId;
	message.transmitFrame.dataLen = length;
	if ((length > 0) && (data != nullptr))
		memcpy(message.transmitFrame.data, data, length);

	return _messageQueue.push(message, blockTime) ? Result::ErrorCodes::ok : Result::ErrorCodes::timeout;
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

		return postMessage_TransmitFrame(cobId, nullptr, 0, blockTime);
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
		.id {MessageID::transmitFrame},
		.transmitFrame {
			.cobid {CobID(COBID::RPDO1, ((uint16_t)rpdoId << 8) | ((uint16_t)nodeId & 0x007F))},
			.dataLen {(uint8_t)dataLen}
		}
	};
	memcpy(message.transmitFrame.data, data, dataLen);

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
