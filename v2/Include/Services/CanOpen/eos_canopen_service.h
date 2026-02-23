#pragma once
#ifndef __eos_canopen_service__
#define __eos_canopen_service__


#include "eos.h"
#include "htl/STM32/htlCAN.h"
#include "Services/eosService.h"
#include "services/canopen/eos_canopen_protocols.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"


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
			using TPDOReceivedEventRaiser = eos::EventRaiser<CanOpenService, TPDOReceivedEventArgs>;
			using ITPDOReceivedEvent = TPDOReceivedEventRaiser::IEvent;
			template <typename Instance_> using TPDOReceivedEvent = TPDOReceivedEventRaiser::Event<Instance_>;

			struct SYNCReceivedEventArgs {
			};
			using SYNCReceivedEventRaiser = eos::EventRaiser<CanOpenService, SYNCReceivedEventArgs>;
			using ISYNCReceivedEvent = SYNCReceivedEventRaiser::IEvent;
			template <typename Instance_> using SYNCReceivedEvent = SYNCReceivedEventRaiser::Event<Instance_>;

			struct HeartbeatReceivedEventArgs {
				NodeID nodeId;
				NodeState state;
			};
			using HeartbeatReceivedEventRaiser = eos::EventRaiser<CanOpenService, HeartbeatReceivedEventArgs>;
			using IHeartbeatReceivedEvent = HeartbeatReceivedEventRaiser::IEvent;
			template <typename Instance_> using HeartbeatReceivedEvent = HeartbeatReceivedEventRaiser::Event<Instance_>;

			struct InitParams {
				htl::can::CANDevice * devCAN;
				NodeID nodeId;
				CanOpenDictionary *dictionary;
			};

		private:
			enum class MessageID {
				entryChanged,
				frameReceived,
				sendFrame
			};
			struct Message {
				MessageID id;
				union {
					struct {
						unsigned entryId;
					} entryChanged;
					struct {
						uint16_t cobid;
						uint8_t dataLen;
						uint8_t data[8];
					} frameReceived;
					struct {
						uint16_t cobid;
						uint8_t dataLen;
						uint8_t data[8];
					} sendFrame;
				};
			};
        	using MessageQueue = Queue<Message>;

        	using CANDeviceNotificationEvent = htl::can::CANDevice::NotificationEvent<CanOpenService>;
        	using TimerEvent = Timer::TimerEvent<CanOpenService>;

		private:
			htl::can::CANDevice * const _devCAN;
        	CanOpenDictionary * const _dictionary;
			TimerEvent _heartbeatTimerEvent;
			Timer _heartbeatTimer;
        	CANDeviceNotificationEvent _canDeviceNotificationEvent;
			NodeID const _nodeId;
			NodeState _nodeState;
			MessageQueue _messageQueue;
			NotificationEventRaiser _erNotification;
			WriteRequestEventRaiser _erWriteRequest;
			TPDOReceivedEventRaiser _erTPDOReceived;
        	SYNCReceivedEventRaiser _erSYNCReceived;
        	HeartbeatReceivedEventRaiser _erHeartbeatReceived;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);
            void heartbeatTimerEventHandler(Timer * const sender, Timer::TimerEventArgs * const args);

            void configureHeartbeat();
            void configureCANDevice();
            void configureCANFilters();

			void processFrame(CobID cobId, const uint8_t *data, unsigned dataLen);
            void processEntryChanged(unsigned entryId);
            void processSDO(const uint8_t *data);
			void processNMT(uint8_t command, uint8_t nodeId);
			void processSYNC();
			void processTIME();
			void processHeartbeat(NodeID nodeId, uint8_t state);
			void processTPDO(CobID cobId, const uint8_t *data, unsigned dataLen);
			void processRPDO(CobID cobId, const uint8_t *data, unsigned dataLen);

			void sendTPDO(uint8_t tpdo);

			bool isMapped(unsigned tpdo, unsigned entryId);

		protected:
			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

            Result sendFrame(CobID cobId, const uint8_t *data, unsigned length, unsigned timeout);
			Result emitHeartbeat(unsigned timeout);
			Result emitNMT(uint8_t command, NodeID nodeId, unsigned timeout);

            void raiseStateChangedNotificationEvent();

            void raiseWriteU8RequestEvent(uint16_t index, uint8_t subIndex, uint8_t value);
            void raiseWriteU16RequestEvent(uint16_t index, uint8_t subIndex, uint16_t value);
            void raiseWriteU32RequestEvent(uint16_t index, uint8_t subIndex, uint32_t value);

            void raiseSYNCReceivedEvent();
			void raiseTPDOReceivedEvent(CobID cobId, const uint8_t *data, unsigned dataLen);
			void raiseHeartbeatReceivedEvent(NodeID nodeId, NodeState state);

            void changeNodeState(NodeState newNodeState);

		public:
			CanOpenService(InitParams const &params);
			CanOpenService(const CanOpenService &) = delete;
			CanOpenService(const CanOpenService &&) = delete;

            // Lectura i escriptura en el dicionari local
            //
            bool writeU8(uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask);
            bool writeU16(uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask);
            bool writeU32(uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask);
            bool readU8(uint16_t index, uint8_t subIndex, uint8_t &value);
            bool readU16(uint16_t index, uint8_t subIndex, uint16_t &value);
            bool readU32(uint16_t index, uint8_t subIndex, uint32_t &value);

            // Lectura i escriptura en el dicionari remot
            //

            // Canvia l'estat d'un node remot
            //
			Result start(NodeID nodeId, unsigned timeout);
			Result stop(NodeID nodeId, unsigned timeout);
			Result enterPreOperational(NodeID nodeId, unsigned timeout);
			Result resetNode(NodeID nodeId, unsigned timeout);
			Result resetCommunication(NodeID nodeId, unsigned timeout);

            // Senyal de sincronitzacio al bus
            //
            Result synchronize(unsigned timeout);

			// Emet missatges RPDO
			//
			Result emitRPDO(NodeID nodeId, uint8_t rpdoId, const uint8_t *data, unsigned dataLen, unsigned timeout);

			// Events
			//
            inline void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
            	_erNotification.set(event, enabled);
            }
			inline void setWriteRequestEvent(IWriteRequestEvent &event, bool enabled = true) {
            	_erWriteRequest.set(event, enabled);
			}
			inline void setSYNCReceivedEvent(ISYNCReceivedEvent &event, bool enabled = true) {
            	_erSYNCReceived.set(event, enabled);
			}
			inline void setTPDOReceivedEvent(ITPDOReceivedEvent &event, bool enabled = true) {
            	_erTPDOReceived.set(event, enabled);
			}
			inline void setHeartbeatReceivedEvent(IHeartbeatReceivedEvent &event, bool enabled = true) {
            	_erHeartbeatReceived.set(event, enabled);
			}
	};
}


#endif // __eos_canopen_service__
