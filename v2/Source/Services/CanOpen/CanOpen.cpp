module;

#include <cstring>


export module Eos.Services.CanOpen;

export import Eos.Services.CanOpen._Types;

import Eos.Bits;
import Eos.Concepts;
import Eos.Events;
import Eos.Hardware.FDCAN;
import Eos.Math;
import Eos.Result;
import Eos.Services.CanOpen.Dictionary;
import Eos.Services.CanOpen.Protocol;
import Eos.Services.Service;
import Eos.System.Core.Queue;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;
import Eos.System.Core.Timer;
import Eos.Types;


using namespace eos;
using namespace eos::hardware::fdcan;


export namespace eos {

	class CanOpenService final: public Service {
		private:
			using DevCAN = CANDevice;

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
				UInt16 index;
				UInt8 subIndex;
				union {
					UInt8 u8;
					UInt16 u16;
					UInt32 u32;
					bool b;
				} value;
			};
			using WriteRequestEventRaiser = EventRaiser<CanOpenService, WriteRequestEventArgs>;
			using IWriteRequestEvent = WriteRequestEventRaiser::IEvent;
			template <typename Instance_> using WriteRequestEvent = WriteRequestEventRaiser::Event<Instance_>;

			struct TPDOReceivedEventArgs {
				CobID cobId;
				UInt8 dataLen;
				const UInt8 *data;
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

		private:
			static constexpr UInt32 _messageQueueSize = 15;
			static constexpr UInt32 _canFrameSize = 8;

		private:
			enum class MessageID {
				initialized,
				entryChanged,
				frameReceived,
				transmitFrame,
				changeNodeState
			};
			struct EntryChanged {
				UInt32 entryId;
			};
			struct FrameReceived {
				UInt16 cobid;
				UInt8 dataLen;
				UInt8 data[_canFrameSize];
			};
			struct TransmitFrame {
				UInt16 cobid;
				UInt8 dataLen;
				UInt8 data[_canFrameSize];
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
			DevCAN * const _devCAN;
			DevCAN::NotificationEvent<CanOpenService> _canDevice_notificationEvent;
			Timer::Event<CanOpenService> _timer_notificationEvent;
			Timer _timer;
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
            void canDevice_notificationEventHandler(DevCAN *sender, DevCAN::NotificationEventArgs *args);
			void timer_notificationEventHandler(Timer *timer, Timer::EventArgs *args);

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

            StdResult postMessage_TransmitFrame(CobID cobId, const UInt8 *data, UInt32 length, Ticks blockTime);

            void processSDO(const UInt8 *data);
			void processRPDO(CobID cobId, const UInt8 *data, UInt32 dataLen);

			void sendTPDO(UInt8 tpdo);

			bool isMapped(UInt8 tpdo, UInt32 entryId);

			StdResult transmitFrame(CobID cobId, const UInt8 *data, UInt32 length, Ticks blockTime);

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

			StdResult emitNMT(UInt8 command, NodeID nodeId, Ticks blockTime);

            void onNodeStateChanged();

            void onWriteU8Request(UInt16 index, UInt8 subIndex, UInt8 value);
            void onWriteU16Request(UInt16 index, UInt8 subIndex, UInt16 value);
            void onWriteU32Request(UInt16 index, UInt8 subIndex, UInt32 value);
            void onSYNCReceived();
			void onTPDOReceived(CobID cobId, const UInt8 *data, UInt32 dataLen);
			void onHeartbeatReceived(NodeID nodeId, NodeState nodeState);

            void changeNodeState(NodeState newNodeState);

		public:
			CanOpenService(DevCAN *devCAN, NodeID nodeId, CanOpenDictionary *dictionary);

			StdResult setNodeState(NodeState nodeState, Ticks blockTime);
			NodeState getNodeState() const;
			NodeID getNodeId() const;

            // Lectura, escriptura i modificacio en el dicionari local
            //
			bool modifyU8(UInt16 index, UInt8 subIndex, UInt8 clearValue, UInt8 setValue, Ticks blockTime);
			bool modifyU16(UInt16 index, UInt8 subIndex, UInt16 clearValue, UInt16 setValue, Ticks blockTime);
			bool modifyU32(UInt16 index, UInt8 subIndex, UInt32 clearValue, UInt32 setValue, Ticks blockTime);
            bool writeU8(UInt16 index, UInt8 subIndex, UInt8 value, Ticks blockTime);
            bool writeU16(UInt16 index, UInt8 subIndex, UInt16 value, Ticks blockTime);
            bool writeU32(UInt16 index, UInt8 subIndex, UInt32 value, Ticks blockTime);
            bool readU8(UInt16 index, UInt8 subIndex, UInt8 &value);
            bool readU16(UInt16 index, UInt8 subIndex, UInt16 &value);
            bool readU32(UInt16 index, UInt8 subIndex, UInt32 &value);

            // Lectura i escriptura en el dicionari remot (Protocol SDO)
            //
            bool writeU8(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt8 value, Ticks blockTime);
            bool writeU16(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt16 value, Ticks blockTime);
            bool writeU32(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt32 value, Ticks blockTime);
            bool readU8(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt8 &value);
            bool readU16(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt16 &value);
            bool readU32(NodeID nodeId, UInt16 index, UInt8 subIndex, UInt32 &value);

            // Canvia l'estat d'un node remot (Protocol NMT)
            //
			StdResult start(NodeID nodeId, Ticks blockTime);
			StdResult stop(NodeID nodeId, Ticks blockTime);
			StdResult enterPreOperational(NodeID nodeId, Ticks blockTime);
			StdResult resetNode(NodeID nodeId, Ticks blockTime);
			StdResult resetCommunication(NodeID nodeId, Ticks blockTime);

            // Senyal de sincronitzacio al bus (Protocol SYNC)
            //
            StdResult emitSYNC(Ticks timeout);

			// Emet missatges RPDO
			//
			StdResult emitRPDO(NodeID nodeId, UInt8 rpdoId, const UInt8 *data, UInt32 dataLen, Ticks blockTime);

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


namespace eos {

	constexpr const char *serviceName = "CanOpen";
	constexpr Task::Priority servicePriority = Task::Priority::normal;
	constexpr UInt32 serviceStackDepth = 256 + 64;

	constexpr unsigned defTimeout = 25;

}


/// ----------------------------------------------------------------------
/// @brief    Constructor del objecte.
/// @param    devCAN: El dispositiu CAN.
/// @param    nideId: El identificador del node.
/// @param    dictionary: El diccionari.
///
CanOpenService::CanOpenService(
	DevCAN *devCAN,
	NodeID nodeId,
	CanOpenDictionary *dictionary) :

    _devCAN {devCAN},
	_canDevice_notificationEvent {*this, &CanOpenService::canDevice_notificationEventHandler},
	_timer_notificationEvent {*this, &CanOpenService::timer_notificationEventHandler},
	_timer {Timer::Mode::autoRestart, nullptr, _timer_notificationEvent},
	_dictionary {dictionary},
	_nodeId {(UInt8)(nodeId & 0x7F)},
	_nodeState {NodeState::initializing},
	_messageQueue {_messageQueueSize} {
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitzacio del servei.
/// @param    params: Parametres d'inicialitzacio.
///
void CanOpenService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackDepth = serviceStackDepth;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// @brief    Executa els procesos del servei.
///
void CanOpenService::onExecute() {

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
	_messageQueue.push(msg, Ticks::infinite());

	// Repeteix mentre no es canceli la tasca
	//
	while (!stopSignal()) {

		// Procesa els missatges de la cua
		//
		Message message;
		while(_messageQueue.pop(message, Ticks::fromMiliseconds(1000)))
			processMessage(message);
	}

	// Finalitza les comunicacions CAN
	//
	_devCAN->stop();
}


void CanOpenService::enableNotificationEvent(
	INotificationEvent &event) {

	_notificationEventRaiser.enable(event);
}


void CanOpenService::disableNotificationEvent() {

	_notificationEventRaiser.disable();
}


void CanOpenService::enableWriteRequestEvent(
	IWriteRequestEvent &event) {

	_writeRequestEventRaiser.enable(event);
}


void CanOpenService::disableWriteRequestEvent() {

	_writeRequestEventRaiser.disable();
}


void CanOpenService::enableSYNCReceivedEvent(
	ISYNCReceivedEvent &event) {

	_syncReceivedEventRaiser.enable(event);
}


void CanOpenService::disableSYNCReceivedEvent() {
	_syncReceivedEventRaiser.disable();
}


void CanOpenService::enableTPDOReceivedEvent(
	ITPDOReceivedEvent &event) {

	_tpdoReceivedEventRaiser.enable(event);
}


void CanOpenService::disableTPDOReceivedEvent() {

	_tpdoReceivedEventRaiser.disable();
}


void CanOpenService::enableHeartbeatReceivedEvent(
	IHeartbeatReceivedEvent &event) {

	_heartbeatReceivedEventRaiser.enable(event);
}


void CanOpenService::disbleHeartbeatReceivedEvent() {

	_heartbeatReceivedEventRaiser.disable();
}


/// ----------------------------------------------------------------------
/// @brief    Configura la produccio dels heartbeats.
///
void CanOpenService::configureHeartbeat() {

	// Obte l'interval entre beats.
	//
	UInt16 interval;
	if (readU16(0x1017, 0, interval) && interval > 0) {

		// Activa el temporitzador
		//
		_timer.start(Ticks::fromMiliseconds(interval), Ticks::fromMiliseconds(100));
	}
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quant l'estat del node canvia.
///
void CanOpenService::onNodeStateChanged() {

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
/// @brief    Es crida quant es reb un SYNC desde un node remot.
///
void CanOpenService::onSYNCReceived() {

	if (_syncReceivedEventRaiser) {

		SYNCReceivedEventArgs args = {
		};

		_syncReceivedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quan es fa una sol·licitut d'escriptura desde
///           un node remot.
/// @param    index: El index
/// @param    subIndex: El subindex.
/// @param    value: El valor.
///
void CanOpenService::onWriteU8Request(
	UInt16 index,
	UInt8 subIndex,
	UInt8 value) {

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
/// @brief    Es crida quan es fa una sol·licitut d'escriptura desde un
///           node remot.
/// @param    index: El index
/// @param    subIndex: El subindex.
/// @param    value: El valor.
///
void CanOpenService::onWriteU16Request(
	UInt16 index,
	UInt8 subIndex,
	UInt16 value) {

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
/// @brief    Es crida quan es fa una sol·licitut d'escriptura desde un
///           node remot.
/// @param    index: El index
/// @param    subIndex: El subindex.
/// @param    value: El valor.
///
void CanOpenService::onWriteU32Request(
	UInt16 index,
	UInt8 subIndex,
	UInt32 value) {

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
/// @brief    Ec crida quant es reb un TPDO d'un node remot
/// @param    cobId: El COBID del TPDO
/// @param    data: Les dades.
/// @param    dataLen: La longitut de les dades.
///
void CanOpenService::onTPDOReceived(
	CobID cobId,
	const UInt8 *data,
	UInt32 dataLen) {

	if (_tpdoReceivedEventRaiser) {

		TPDOReceivedEventArgs args = {
			.cobId {cobId},
			.dataLen {(UInt8)dataLen},
			.data {data}
		};

		_tpdoReceivedEventRaiser(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quan es reb un Heartbeat desde un node remot
/// @param    nodeId: El node emisor
/// @param    state: L'estat del node emisor.
///
void CanOpenService::onHeartbeatReceived(
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
/// @brief    Realitza el canvi d'estat i notifica els canvis
/// @param    newNodeState: El nou estat
///
void CanOpenService::changeNodeState(
	NodeState newNodeState) {

	if (_nodeState != newNodeState) {
		_nodeState = newNodeState;
		onNodeStateChanged();
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa els missatges
/// @param    message: El missatge a procesar.
///
void CanOpenService::processMessage(
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
/// @brief    Procesa el missatge 'initialized'
///
void CanOpenService::processMessage_Initialized() {

	// Emet un boot-up
	//
	UInt8 data[1];
	data[0] =  0;

	CobID cobId = CobID::makeHeartbeat(_nodeId);

	transmitFrame(cobId, data, sizeof(data), Ticks::fromMiliseconds(100));

	// Canvia l'estat a 'preOperational'
	//
	changeNodeState(NodeState::preOperational);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'entryChanged'
/// @param    args: Els parametres del missatge.
///
void CanOpenService::processMessage_EntryChanged(
	const EntryChanged &args) {

	// Si esta en modus operacional, comprova si cal generar TPDO's
	//
	if (_nodeState == NodeState::operational) {

		// Comprova les entrades 0x1800 per si hi ha TPDO asincrones
		//
		UInt8 tpdoMax = 4;
		for (UInt8 tpdo = 0; tpdo < tpdoMax; tpdo++) {

			// Verifica que la entrada, estigui mapejada en un TPDO
			//
			if (isMapped(tpdo, args.entryId)) {
				UInt32 flags;
				UInt8 transmissionType;

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
/// @brief    Procesa el missatge 'changeNodeState'
/// @param    args: Els parametres del missatge.
///
void CanOpenService::processMessage_ChangeNodeState(
	const ChangeNodeState &args) {

	changeNodeState(args.nodeState);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'sendFrame'
/// @param    args: Els parametres del missatge.
///
void CanOpenService::processMessage_TransmitFrame(
	const TransmitFrame &args) {

	transmitFrame(
		CobID::make(args.cobid),
		args.data,
		args.dataLen,
		Ticks::fromMiliseconds(50));
}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'FrameReceived'
/// @param    args: Els parammetres del missatge.
///
void CanOpenService::processMessage_FrameReceived(
	const FrameReceived &args) {

	auto cobId = CobID::make(args.cobid);

	if (cobId.isNMT())
		processMessage_FrameReceived_NMT(args);

	else if (cobId.isSYNC())
		processMessage_FrameReceived_SYNC(args);

	else if (cobId.isTIME())
		processMessage_FrameReceived_TIME(args);

	else if (cobId.isHeartbeat())
		processMessage_FrameReceived_Heartbeat(args);

	else if (cobId.isSDO())
		processMessage_FrameReceived_SDO(args);

	else if ((cobId.base() == CobID::baseRPDO1) ||
		     (cobId.base() == CobID::baseRPDO2) ||
		     (cobId.base() == CobID::baseRPDO3) ||
		     (cobId.base() == CobID::baseRPDO4))
		processMessage_FrameReceived_RPDO(args);

	else if ((cobId.base() == CobID::baseTPDO1) ||
		     (cobId.base() == CobID::baseTPDO2) ||
		     (cobId.base() == CobID::baseTPDO3) ||
		     (cobId.base() == CobID::baseTPDO4))
	    processMessage_FrameReceived_TPDO(args);
}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'FrameReceived' Heartbeat.
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_Heartbeat(
	const FrameReceived &args) {

	auto state = args.data[0];
	auto nodeId = CobID::getNodeID(args.cobid);

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
/// @brief    Procesa el missatge 'FrameReceived' NMT
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_NMT(
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
/// @brief    Procesa el missatge 'FrameReceived' SDO
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_SDO(
	const FrameReceived &args) {

	UInt8 response[8];
	UInt32 errorCode = SdoError::none;

	// Comprova l'estat del node
	//
	if ((_nodeState != NodeState::preOperational) &&
		(_nodeState != NodeState::operational))
		errorCode = SdoError::unsupportedAccesssToObject;

	// Initiate SDO download (Expedited)
	//
	else if ((args.data[0] & (SDO0::CCS_Msk | SDO0::S_Msk | SDO0::E_Msk)) == (SDO0::CCS_DN | SDO0::S_SIZE | SDO0::E_EXP)) {

		UInt16 index = args.data[1] | (args.data[2] << 8);
		UInt8 subIndex = args.data[3];

		auto entryId = _dictionary->find(index, subIndex);
		if (entryId == (typeof(entryId)) -1)
			errorCode = SdoError::objectDoesNotExistInDictionary;

		else {
			if (!_dictionary->canWrite(entryId))
				errorCode = SdoError::attemptToWriteReadOnlyObject;

			else {
				UInt8 size = 4 - ((args.data[0] & SDO0::SIZE_Msk) >> SDO0::SIZE_Pos);
				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8: {
						UInt8 value = args.data[4];
						onWriteU8Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned16: {
						UInt16 value = (args.data[4] << 8) | (args.data[5] << 16);
						onWriteU16Request(index, subIndex, value);
						break;
					}

					case CoType::unsigned32: {
						UInt32 value = args.data[4] | (args.data[5] << 8) | (args.data[6] << 16) |
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

		UInt16 index = args.data[1] | (args.data[2] << 8);
		UInt8 subIndex = args.data[3];
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
						UInt8 value;
						_dictionary->readU8(entryId, value);
						response[4] = value;
						break;
					}

					case CoType::unsigned16: {
						UInt16 value;
						_dictionary->readU16(entryId, value);
						response[4] = value & 0xFF;
						response[5] = (value >> 8) & 0xFF;
						break;
					}

					case CoType::unsigned32: {
						UInt32 value;
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
	UInt32 cobidSDOr;
	if (_dictionary->readU32(0x1200, 0x02, cobidSDOr))
		transmitFrame(CobID::make(cobidSDOr & 0x7FF, _nodeId),
			response, sizeof(response), Ticks::fromMiliseconds(defTimeout));
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa el missatge 'FrameReceived' TIME
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_TIME(
	const FrameReceived &args) {

}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'FrameReceived' SYNC
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_SYNC(
	const FrameReceived &args) {

	if (_nodeState == NodeState::operational) {

		onSYNCReceived();

		// Comprova les  entrades 0x1800 per si hi han TPDOs sincrons
		// per enviar
		//
		UInt8 tpdoMax = 4;
		for (UInt8 tpdo = 0; tpdo < tpdoMax; tpdo++) {

			UInt32 flags;
			UInt8 transmissionType;

			if (_dictionary->readU32(0x1800 + tpdo, 0x01, flags) &&
				_dictionary->readU8(0x1800 + tpdo, 0x02, transmissionType)) {

				if ((transmissionType <= 240) && ((flags & (1 << 31)) == 0))
					sendTPDO(tpdo);
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa els missatges 'FrameReceived' TPDO
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_TPDO(
	const FrameReceived &args) {

	if (_nodeState == NodeState::operational) {

		// Notifica a l'aplicacio que hi ha un TPDO per procesar provinent d'un
		// node remot
		//
		onTPDOReceived(CobID::make(args.cobid), args.data, args.dataLen);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa el missatge 'FrameReceived' RPDO
/// @param    args: Parametres del missatge
///
void CanOpenService::processMessage_FrameReceived_RPDO(
	const FrameReceived &args) {

	auto cobId = CobID::make(args.cobid);

	UInt32 rpdoCOBID;
	if (_dictionary->readU32(0x1400, 0x01, rpdoCOBID) && (rpdoCOBID == cobId.base())) {

		const UInt8 *pData = args.data;

		UInt32 map;
		if (_dictionary->readU32(0x1600, 0x01, map)) {

			UInt16 index = (map >> 16) & 0xFFFF;
			UInt8 subIndex = (map >> 8) & 0xFF;
			UInt8 size = (map & 0xFF) / 8;

			auto entryId = _dictionary->find(index, subIndex);
			if (entryId != (typeof(entryId)) -1) {

				CoType type = _dictionary->getType(entryId);
				switch (type) {
					case CoType::unsigned8:
						if (size == sizeof(UInt8)) {
							UInt8 value = 0;
							value |= *pData++;
							onWriteU8Request(index, subIndex, value);
						}
						break;

					case CoType::unsigned16:
						if (size == sizeof(UInt16)) {
							UInt16 value = 0;
							value |= *pData++;
							value |= *pData++ << 8;
							onWriteU16Request(index, subIndex, value);
						}
						break;

					case CoType::unsigned32:
						if (size == sizeof(UInt32)) {
							UInt32 value = 0;
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
/// @brief    Canvia l'estat del node.
/// @param    nodeState: El nou estat.
/// @param    blockTime: Temps maxim de bloqueig.
/// \return   El resultat de l'operacio.
///
StdResult CanOpenService::setNodeState(
	NodeState nodeState,
	Ticks blockTime) {

	Message message = {
		.id {MessageID::changeNodeState},
		.changeNodeState {
			.nodeState {nodeState}
		}
	};

	if (_messageQueue.push(message, blockTime))
		return StdErrorCode::ok;

	return StdErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Obte l'estat del node.
/// \return   L'estat.
///
CanOpenService::NodeState CanOpenService::getNodeState() const {

	return _nodeState;
}


/// ----------------------------------------------------------------------
/// @brief    Obte l'identificador del node.
/// \return   El identificador del node.
///
NodeID CanOpenService::getNodeId() const {

	return _nodeId;
}


/// ----------------------------------------------------------------------
/// @brief    Envia un TPDOx al bus
/// @param    tpdo: El identificador del TPDOx
///
void eos::CanOpenService::sendTPDO(
	UInt8 tpdo) {

	UInt8 maxCount;
	if (_dictionary->readU8(0x1A00 | tpdo, 0x00, maxCount) && maxCount > 0) {

		UInt8 data[8];
		UInt8 *pData = data;
		UInt8 dataLen = 0;

		// Mapeja els elements un a un
		//
		bool ok = true;
		for (auto count = 0; (count < maxCount) && ok; count++) {

			UInt32 mapInfo;
			ok = _dictionary->readU32(0x1A00 | tpdo, count + 1, mapInfo);
			if (ok) {

				UInt16 mapIndex = (mapInfo >> 16) & 0xFFFF;
				UInt8 mapSubIndex = (mapInfo >> 8) & 0xFF;
				unsigned mapLength = (mapInfo & 0xFF) / 8;

				auto entryId = _dictionary->find(mapIndex, mapSubIndex);
				ok = entryId != (unsigned) -1;
				if (ok) {
					switch (mapLength) {
						case 1:
							ok = (dataLen + sizeof(UInt8)) < sizeof(data);
							if (ok) {
								UInt8 value;
								ok = _dictionary->readU8(entryId, value);
								if (ok) {
									*(pData++) = value;
									dataLen += sizeof(UInt8);
								}
							}
							break;

						case 2:
							ok = (dataLen + sizeof(UInt16)) < sizeof(data);
							if (ok) {
								UInt16 value;
								ok = _dictionary->readU16(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									dataLen += sizeof(UInt16);
								}
							}
							break;

						case 4:
							ok = (dataLen + sizeof(UInt32)) < sizeof(data);
							if (ok) {
								UInt32 value;
								ok = _dictionary->readU32(entryId, value);
								if (ok) {
									*(pData++) = value & 0xFF;
									*(pData++) = (value >> 8) & 0xFF;
									*(pData++) = (value >> 16) & 0xFF;
									*(pData++) = (value >> 24) & 0xFF;
									dataLen += sizeof(UInt32);
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
			UInt32 cobid;
			if (_dictionary->readU32(0x1800 + tpdo, 0x01, cobid))
				transmitFrame(CobID::make(cobid & 0x7FF, _nodeId), data, dataLen, Ticks::fromMiliseconds(100));
		}
	}
}


/// ----------------------------------------------------------------------
/// @brief    Procesa els events de notificacio del temporitzador.
/// @param    sender: El remitent del missatge.
/// @param    args: Parametres del event.
///
void CanOpenService::timer_notificationEventHandler(
	Timer *sender,
	Timer::EventArgs *args) {

	UInt8 data[1];
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

	postMessage_TransmitFrame(cobId, data, sizeof(data), Ticks::fromMiliseconds(100));
}


/// ----------------------------------------------------------------------
/// @brief    Emet una trama
/// @param    cobId: El identificador.
/// @param    data: Les dades.
/// @param    length: La longitut de les dades en bytes.
/// @param    blockTime: Temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult CanOpenService::postMessage_TransmitFrame(
	CobID cobId,
	const UInt8 *data,
	UInt32 length,
	Ticks blockTime) {

	if (length > _canFrameSize)
		return StdErrorCode::errorParameter;

	Message message;
	message.id = MessageID::transmitFrame;
	message.transmitFrame.cobid = cobId;
	message.transmitFrame.dataLen = length;
	if ((length > 0) && (data != nullptr))
		memcpy(message.transmitFrame.data, data, length);

	return _messageQueue.push(message, blockTime) ? StdErrorCode::ok : StdErrorCode::timeout;
}


/// ----------------------------------------------------------------------
/// @brief    Emet un missatge SYNC
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult CanOpenService::emitSYNC(
	Ticks blockTime) {

	UInt32 options;
	if (_dictionary->readU32(0x1005, 0x00, options) &&
		Bits::isSet(options, (UInt32)(1 << 30))) {

		auto cobId = CobID::make(options & 0x007F);

		return postMessage_TransmitFrame(cobId, nullptr, 0, blockTime);
	}

	return StdErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Emet un missatge RPDO
/// @brief    nodeId: El node desti.
/// @param    rpdoId: El idenfificador del RTPDO.
/// @param    data: Les dades a transmetre
/// @param    dataLen: La longitut de les dades a transmetre.
/// \return   El resultat de l'operacio.
///
StdResult CanOpenService::emitRPDO(
	NodeID nodeId,
	UInt8 rpdoId,
	const UInt8 *data,
	UInt32 dataLen,
	Ticks timeout) {

	Message message = {
		.id {MessageID::transmitFrame},
		.transmitFrame {
			.cobid {CobID::make(CobID::baseRPDO1, ((UInt16)rpdoId << 8) | ((UInt16)nodeId & 0x007F))},
			.dataLen {(UInt8)dataLen}
		}
	};
	memcpy(message.transmitFrame.data, data, dataLen);

	if (_messageQueue.push(message, timeout))
		return StdErrorCode::ok;

	return StdErrorCode::error;
}


/// ----------------------------------------------------------------------
/// @brief    Comprova si una entrada esta mapejada en un TPDO
/// @param    tpdo: El TPDO
/// @param    entryId: El identificador de l'entrada.
/// \return   True si esta mapejada.
///
bool CanOpenService::isMapped(
	UInt8 tpdo,
	UInt32 entryId) {

	UInt8 numMaps;
	if (_dictionary->readU8(0x1A00 + tpdo, 0, numMaps)) {
		for (auto i = 0; i < numMaps; i++) {

			UInt32 map;
			if (_dictionary->readU32(0x1A00 + tpdo, i + 1, map)) {

				UInt16 mapIndex = (map >> 16) & 0xFFFF;
				UInt8 mapSubIndex = (map >> 8) & 0xFF;
				if (entryId == _dictionary->find(mapIndex, mapSubIndex))
					return true;
			}
		}
	}

	return false;
}
