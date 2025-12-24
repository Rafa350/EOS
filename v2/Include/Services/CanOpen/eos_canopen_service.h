#pragma once
#ifndef __eos_canopen_service__
#define __eos_canopen_service__


#include "eos.h"
#include "htl/STM32/htlCAN.h"
#include "Services/eosService.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"


namespace eos {

	class CanOpenDictionary;

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
				valueChanged,
				sync
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

			struct InitParams {
				htl::can::CANDevice * devCAN;
				uint8_t nodeId;
				CanOpenDictionary *dictionary;
			};

		private:
			enum class MessageID {
				canReceive,
				canSend,
				odChanged,
				odWriteU8,
				odWriteU16,
				odWriteU32,
				heartbead
			};
			struct Message {
				MessageID id;
				union {
					struct {
						uint16_t cobid;
						uint8_t dataLen;
						uint8_t data[8];
					} canReceive;
					struct {
						uint16_t cobid;
						uint8_t dataLen;
						uint8_t data[8];
					} canSend;
					struct {
						unsigned entryId;
						uint8_t value;
						uint8_t mask;
					} odWriteU8;
					struct {
						unsigned entryId;
						uint16_t value;
						uint16_t mask;
					} odWriteU16;
					struct {
						unsigned entryId;
						uint32_t value;
						uint32_t mask;
					} odWriteU32;
					struct {
						unsigned entryId;
					} odChanged;
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
			uint8_t const _nodeId;
			NodeState _nodeState;
			MessageQueue _messageQueue;
			NotificationEventRaiser _erNotification;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);
            void heartbeatTimerEventHandler(Timer * const sender, Timer::TimerEventArgs * const args);

            void configureHeartbeat();
            void configureSDO();
            void configureCANDevice();
            void configureCANFilters();

            void processValueChanged(unsigned entryId, bool raiseNotification);
            void processWriteU8(unsigned entryId, uint8_t value, uint8_t mask);
            void processWriteU16(unsigned entryId, uint16_t value, uint16_t mask);
            void processWriteU32(unsigned entryId, uint32_t value, uint32_t mask);
            void processSDOFrame(const uint8_t *data);
			void processNMTFrame(const uint8_t *data);
			void processSYNCFrame();
			void processRPDOFrame(uint16_t cobid, const uint8_t *data, unsigned dataLen);

			void sendHeartbeat();
			void sendTPDO(uint8_t tpdo);

			bool isMapped(unsigned tpdo, unsigned entryId);

		protected:
			CanOpenService(InitParams const &params);

			void onInitialize(ServiceParams &params) override;
			void onExecute() override;

			virtual void processFrame(uint16_t cobid, const uint8_t *data, unsigned dataLen);
            Result sendFrame(uint16_t cobid, const uint8_t *data, unsigned length, unsigned timeout);

            bool readU8(uint16_t index, uint8_t subIndex, uint8_t &value) const;
            bool readU16(uint16_t index, uint8_t subIndex, uint16_t &value) const;
            bool readU32(uint16_t index, uint8_t subIndex, uint32_t &value) const;

            void raiseStateChangedNotificationEvent();
            void raiseSyncNotificationEvent();
            void raiseValueChangeRequestNotificationEvent(uint16_t index, uint8_t subIndex, uint8_t value, bool fromBus);
            void raiseValueChangedNotificationEvent(uint16_t index, uint8_t subIndex, bool fromBus);

            void changeNodeState(NodeState newNodeState);
            virtual void beforeChangeNodeState();
            virtual void afterChangeNodeState();

		public:
            void odWriteU8(uint16_t index, uint8_t subIndex, uint8_t value, uint8_t mask);
            void odWriteU16(uint16_t index, uint8_t subIndex, uint16_t value, uint16_t mask);
            void odWriteU32(uint16_t index, uint8_t subIndex, uint32_t value, uint32_t mask);

            bool odReadU8(uint16_t index, uint8_t subIndex, uint8_t &value);

            void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
            	_erNotification.set(event, enabled);
            }
	};
}


#endif // __eos_canopen_service__
