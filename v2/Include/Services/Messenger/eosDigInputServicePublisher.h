#pragma once


#include "eos.h"
#include "Services/DigInput/eosDigInputService.h"
#include "Services/Messenger/eosMessagePublisher.h"


namespace eos {

	class DigInputServiceNotificationEventPublisher final: public MessagePublisher {
		private:
    		using NotificationEvent = eos::DigInputService::NotificationEvent<DigInputServiceNotificationEventPublisher>;

		private:
    		NotificationEvent _notificationEvent;

		private:
			void NotificationEventHandler(eos::DigInputService * const sender, eos::DigInputService::NotificationEventArgs * const args);

		public:
			DigInputServiceNotificationEventPublisher(DigInputService *service);
	};
}
