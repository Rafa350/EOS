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
			struct InitParams {
				htl::can::CANDevice * devCAN;
				unsigned nodeId;
				const CoDictionaryEntry * dictionary;
				unsigned dictionarySize;
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
        		bootup,
        		stoped,
        		preOperational,
				operational,
				error
        	};

		private:
			htl::can::CANDevice * const _devCAN;
        	CANDeviceNotificationEvent _canDeviceNotificationEvent;
        	const CoDictionaryEntry * const _dictionary;
        	unsigned const _dictionarySize;
			unsigned const _nodeId;
			NodeState _nodeState;
			MessageQueue _queue;

		private:
            void canDeviceNotificationEventHandler(htl::can::CANDevice * const sender, htl::can::CANDevice::NotificationEventArgs * const args);

            const CoDictionaryEntry * findEntry(uint16_t index, uint8_t subIndex) const;
            void processSDO(const htl::can::RxHeader * rxHeader, const uint8_t *data);

            void sendHeartbeat();

		protected:
		    void onInitialize(ServiceParams &params) override;
			void onExecute() override;

		public:
			CanOpenService(InitParams const &params);

	};
}


#endif // __eosCanOpenService__
