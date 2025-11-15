#pragma once
#ifndef __eosCanOpenService__
#define __eosCanOpenService__


#include "eos.h"
#include "htl/STM32/htlCAN.h"
#include "Services/eosService.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class CanOpenService final: public Service {
		public:
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
			enum class Message {
				rxFifo0,
				rxFifo1,
				heartbeat
			};
        	using CANDeviceNotificationEvent = htl::can::CANDevice::NotificationEvent<CanOpenService>;
        	using MessageQueue = Queue<Message>;

        	enum class NodeState {
        		initializing,
        		stoped,
        		preOperational,
				operational,
				error
        	};

		private:
			htl::can::CANDevice * const _devCAN;
        	CANDeviceNotificationEvent _canDeviceNotificationEvent;
        	const CanOpenDictionary * const _dictionary;
			uint8_t const _nodeId;
			NodeType const _nodeType;
			NodeState _nodeState;
			MessageQueue _queue;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);

            void processSDO(const uint8_t *rxData);
            void processSDO_ExpeditedDownload(const uint8_t *rxData);

            void processMNT(const uint8_t *rxData);

            void sendFrame(uint16_t cobid, const uint8_t *txData, unsigned txLength);

            void changeNodeState(NodeState newNodeState);

		protected:
		    void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			CanOpenService(InitParams const &params);

			void sdoUpload(unsigned nodeId, uint16_t index, uint8_t subIndex);
			void sdoInitiateUpload();
			void sdoSegmentUpload();
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value);
			void sdoInitiateDownload();
			void sdoSegmentDownload();
			void sdoAbort();

            void heartbeat();

            void tpdoTransmit(uint8_t tpdoId);
	};
}


#endif // __eosCanOpenService__
