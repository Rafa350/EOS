#pragma once
#ifndef __eosCanOpenService__
#define __eosCanOpenService__


#include "eos.h"
#include "htl/STM32/htlCAN.h"
#include "Services/eosService.h"
#include "Services/CanOPen/eosCanOpenSDOServer.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class CanOpenDictionary;

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
			using IEvent = NotificationEventRaiser::IEvent;
			template <typename Instance_> using Event = NotificationEventRaiser::Event<Instance_>;

        	enum class NodeType {
				master,
				slave
			};

			struct InitParams {
				htl::can::CANDevice * devCAN;
				uint8_t nodeId;
				NodeType nodeType;
				CanOpenDictionary *dictionary;
			};

		private:
			enum class MessageID {
				canReceive
			};
			struct Message {
				MessageID id;
				union {
					struct {
						uint16_t cobid;
						uint8_t data[8];
					} canReceive;
				};
			};
        	using CANDeviceNotificationEvent = htl::can::CANDevice::NotificationEvent<CanOpenService>;
        	using MessageQueue = Queue<Message>;

		private:
			htl::can::CANDevice * const _devCAN;
        	CANDeviceNotificationEvent _canDeviceNotificationEvent;
        	const CanOpenDictionary * const _dictionary;
			uint8_t const _nodeId;
			NodeType const _nodeType;
			NodeState _nodeState;
			MessageQueue _queue;
			NotificationEventRaiser _erNotification;
			CanOpenSDOServer _sdoServer;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);

            void processSDO(const uint8_t *rxData, uint8_t *txData);
            void processSYNC();
            void processNMT(const uint8_t *rxData);
            void processRPDO(const uint8_t *rdData);

            unsigned buildTPDO(unsigned tpdoId, uint8_t *buffer, unsigned bufferSize);

            void sendFrame(uint16_t cobid, const uint8_t *txData, unsigned txLength);

            void changeNodeState(NodeState newNodeState);

            void notifyStateChanged();
            void notifyValueChanged(uint16_t index, uint8_t subIndex);

		protected:
		    void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			CanOpenService(InitParams const &params);

			void sdoUpload(unsigned nodeId, uint16_t index, uint8_t subIndex);
			void sdoInitiateUpload();
			void sdoSegmentUpload();
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value);
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, const uint8_t data, uint32_t length);
			void sdoInitiateDownload();
			void sdoSegmentDownload();
			void sdoAbort();

			void bootUp();
            void heartBeat();

            inline NodeState getNodeState() const {
            	return _nodeState;
            }

            inline uint16_t getNodeId() const {
            	return _nodeId;
            }
	};
}


#endif // __eosCanOpenService__
