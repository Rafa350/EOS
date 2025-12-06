#pragma once
#ifndef __eos_canopen_service__
#define __eos_canopen_service__


#include "eos.h"
#include "htl/STM32/htlCAN.h"
#include "Services/eosService.h"
#include "System/Core/eosQueue.h"


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
				valueChanged
			};
        	struct NotificationEventArgs {
        		NotificationID id;
        		union {
        			struct {
        				uint16_t index;
        				uint8_t subIndex;
        			} valueChanged;
        		};
        	};
			using NotificationEventRaiser = eos::EventRaiser<CanOpenService, NotificationEventArgs>;
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
				entryValueChanged,
				heartbead
			};
			struct Message {
				MessageID id;
				union {
					struct {
						uint16_t cobid;
						uint8_t data[8];
					} canReceive;
					struct {
						unsigned entryId;
						bool raiseNotification;
					} entryValueChanged;
				};
			};
        	using CANDeviceNotificationEvent = htl::can::CANDevice::NotificationEvent<CanOpenService>;
        	using MessageQueue = Queue<Message>;

		private:
			htl::can::CANDevice * const _devCAN;
        	CANDeviceNotificationEvent _canDeviceNotificationEvent;
        	CanOpenDictionary * const _dictionary;
			uint8_t const _nodeId;
			NodeState _nodeState;
			MessageQueue _queue;
			NotificationEventRaiser _erNotification;
			unsigned _tickCount;
			unsigned _maxTickCount;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);

            void processRPDO(const uint8_t *rdData);
            void processValueChanged(unsigned entryId, bool raiseNotification);
            void processHeartBeat();

            unsigned buildTPDO(unsigned tpdoId, uint8_t *buffer, unsigned bufferSize);

            void notifyValueChanged(unsigned entryId, bool raiseNotification);

		protected:
		    void onInitialize(ServiceParams &params) override;
			void onExecute() override;

			virtual void process(uint16_t cobid, const uint8_t *data) = 0;

			void sendSDOUpload(unsigned nodeId, uint16_t index, uint8_t subIndex);
			void sendSDOInitiateUpload();
			void sendSDOSegmentUpload();
			void sendSDODownload(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value);
			void sendSDOInitiateDownload();
			void sendSDOSegmentDownload();
			void sendSDOAbort();

            void sendFrame(uint16_t cobid, const uint8_t *data, unsigned length);

            void raiseStateChangedNotificationEvent();
            void raiseValueChangedNotificationEvent(uint16_t index, uint8_t subIndex);

            void changeNodeState(NodeState newNodeState);

		public:
			CanOpenService(InitParams const &params);

            void notifyValueChanged(uint16_t index, uint8_t subIndex, bool raiseNotification = false);
			void notifyValueChanged(const void *ptr, bool raiseNotification = false);

            void tickISR();

            void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
            	_erNotification.set(event, enabled);
            }

            inline NodeState getNodeState() const {
            	return _nodeState;
            }

            inline uint16_t getNodeId() const {
            	return _nodeId;
            }

            // TODO: public per test unicament
            void sendHeartBeat();
	};
}


#endif // __eos_canopen_service__
