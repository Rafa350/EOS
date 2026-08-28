#pragma once
#ifndef __eosCanOpenService__
#define __eosCanOpenService__


#include "eos.h"
#include "eosEvents.h"
#include "eosTime.h"
#include "HTL/STM32/htlCAN.h"
#include "RTOS/rtosTimer.h"
#include "Services/eosService.h"
#include "services/CanOpen/eosCanOpenProtocol.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class CanOpenDictionary;

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
				entryChanged,
				frameReceived,
				sendFrame,
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
			struct SendFrame {
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
					SendFrame sendFrame;
					ChangeNodeState changeNodeState;
				};
			};
        	using MessageQueue = Queue<Message>;

		private:
			htl::can::CANDevice * const _devCAN;
        	CanOpenDictionary * const _dictionary;
			htl::can::CANDevice::NotificationEvent<CanOpenService> _canDevice_notificationEvent;
			NodeID const _nodeId;
			NodeState _nodeState;
			MessageQueue _messageQueue;
			NotificationEventRaiser _notificationEventRaiser;
			WriteRequestEventRaiser _writeRequestEventRaiser;
			TPDOReceivedEventRaiser _tpdoReceivedEventRaiser;
        	SYNCReceivedEventRaiser _syncReceivedEventRaiser;
        	HeartbeatReceivedEventRaiser _heartbeatReceivedEventRaiser;

        	void *_heartbeatProducer;
        	void *_nmtMaster;

		private:
            void canDevice_notificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);

            void configureHeartbeat();
            void configureNmtMaster();
            void configureCANDevice();
            void configureCANFilters();

			void processFrameReceived(const FrameReceived &msg);
            void processEntryChanged(const EntryChanged &msg);
            void processChangeNodeState(const ChangeNodeState &msg);
            void processSendFrame(const SendFrame &msg);

            void processSDO(const uint8_t *data);
			void processNMT(uint8_t command, NodeID nodeId);
			void processSYNC();
			void processTIME();
			void processHeartbeat(NodeID nodeId, uint8_t state);
			void processTPDO(CobID cobId, const uint8_t *data, uint32_t dataLen);
			void processRPDO(CobID cobId, const uint8_t *data, uint32_t dataLen);

			void sendTPDO(uint8_t tpdo);

			bool isMapped(uint8_t tpdo, uint32_t entryId);

			Result sendFrame(CobID cobId, const uint8_t *data, uint32_t length, Time blockTime);

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

            // Lectura i escriptura en el dicionari remot (Via protocol SDO)
            //
            bool writeU8(NodeID nodeId, uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask);
            bool writeU16(NodeID nodeId, uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask);
            bool writeU32(NodeID nodeId, uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask);
            bool readU8(NodeID nodeId, uint16_t index, uint8_t subIndex, uint8_t &value);
            bool readU16(NodeID nodeId, uint16_t index, uint8_t subIndex, uint16_t &value);
            bool readU32(NodeID nodeId, uint16_t index, uint8_t subIndex, uint32_t &value);

            // Canvia l'estat d'un node remot (Via protocol NMT)
            //
			Result start(NodeID nodeId, Time blockTime);
			Result stop(NodeID nodeId, Time blockTime);
			Result enterPreOperational(NodeID nodeId, Time blockTime);
			Result resetNode(NodeID nodeId, Time blockTime);
			Result resetCommunication(NodeID nodeId, Time blockTime);

            // Senyal de sincronitzacio al bus
            //
            Result emitSYNC(Time timeout);

			// Emet missatges RPDO
			//
			Result emitRPDO(NodeID nodeId, uint8_t rpdoId, const uint8_t *data, uint32_t dataLen, Time timeout);

			// Emet una trama
			//
			Result emitFrame(CobID cobId, const uint8_t *data, uint32_t length, Time blockTime);

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


#endif // __eosCanOpenService__
