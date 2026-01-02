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

	class CanOpenService: public Service {
		public:
        	enum class NodeState {
        		initializing,
        		stoped,
        		preOperational,
				operational,
				error
        	};

        	enum class NotificationID {
				stateChanged,
				valueChangeRequest,
				valueChanged
			};
        	struct NotificationEventArgs {
        		NotificationID id;
        		union {
        			struct {
        				uint16_t index;
        				uint8_t subIndex;
        				bool fromBus;
        			} valueChanged;
        			struct {
        				uint16_t index;
        				uint8_t subIndex;
        				uint32_t value;
        				bool fromBus;
        			} valueChangeRequest;
        		};
        	};
			using NotificationEventRaiser = EventRaiser<CanOpenService, NotificationEventArgs>;
			using INotificationEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

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
				frameReceived,
				sendFrame,
				writeU8,
				writeU16,
				writeU32,
				writeBool
			};
			struct Message {
				MessageID id;
				union {
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
					struct {
						unsigned entryId;
						uint8_t value;
						uint8_t mask;
					} writeU8;
					struct {
						unsigned entryId;
						uint16_t value;
						uint16_t mask;
					} writeU16;
					struct {
						unsigned entryId;
						uint32_t value;
						uint32_t mask;
					} writeU32;
					struct {
						unsigned entryId;
						bool value;
					} writeBool;
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
            void processValueChanged(unsigned entryId, bool raiseNotification);
            void processWriteU8(unsigned entryId, uint8_t value, uint8_t mask);
            void processWriteU16(unsigned entryId, uint16_t value, uint16_t mask);
            void processWriteU32(unsigned entryId, uint32_t value, uint32_t mask);
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

            void raiseStateChangedNotificationEvent();
            void raiseValueChangeRequestNotificationEvent(uint16_t index, uint8_t subIndex, uint8_t value, bool fromBus);
            void raiseValueChangedNotificationEvent(uint16_t index, uint8_t subIndex, bool fromBus);
            void raiseSYNCReceivedEvent();
			void raiseTPDOReceivedEvent(CobID cobId, const uint8_t *data, unsigned dataLen);
			void raiseHeartbeatReceivedEvent(NodeID nodeId, NodeState state);

            void changeNodeState(NodeState newNodeState);
            virtual void beforeChangeNodeState();
            virtual void afterChangeNodeState();

		public:
			CanOpenService(InitParams const &params);

            // Operacions amb el dicionary
            //
            void writeU8(uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask);
            void writeU16(uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask);
            void writeU32(uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask);
            bool readU8(uint16_t index, uint8_t subIndex, uint8_t &value);
            bool readU16(uint16_t index, uint8_t subIndex, uint16_t &value);
            bool readU32(uint16_t index, uint8_t subIndex, uint32_t &value);

            // Operacions SYNC
            //
            Result emitSYNC(unsigned timeout);

            // Operacions SDO
			//
			Result emitSDO_Upload(unsigned nodeId, uint16_t index, uint8_t subIndex, unsigned timeout);
			Result emitSDO_InitiateUpload(unsigned timeout);
			Result emitSDO_SegmentUpload(unsigned timeout);
			Result emitSDO_Download(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value, unsigned timeout);
			Result emitSDO_Download(unsigned nodeId, uint16_t index, uint8_t subindex, const uint8_t data, uint32_t length, unsigned timeout);
			Result emitSDO_InitiateDownload(unsigned timeout);
			Result emitSDO_SegmentDownload(unsigned timeout);
			Result emitSDO_Abort(unsigned timeout);

			// Operacions NMT
			//
			Result emitNMT(uint8_t command, NodeID nodeId, unsigned timeout);
			Result emitNMT_StartNode(NodeID nodeId, unsigned timeout);
			Result emitNMT_StopNode(NodeID nodeId, unsigned timeout);
			Result emitNMT_EnterPreOperational(NodeID nodeId, unsigned timeout);
			Result emitNMT_ResetNode(NodeID nodeId, unsigned timeout);
			Result emitNMT_ResetCommunication(NodeID nodeId, unsigned timeout);

			// Operacio heartbeat
			//
			Result emitHeartbeat(unsigned timeout);

			// Operacions RPDO
			//
			Result emitRPDO(NodeID nodeId, uint8_t rpdoId, const uint8_t *data, unsigned dataLen, unsigned timeout);

            inline void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
            	_erNotification.set(event, enabled);
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
