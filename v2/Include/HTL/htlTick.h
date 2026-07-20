#pragma once
#ifndef __htlTick__
#define __htlTick__


#include "HTL/htl.h"
#include "HTL/htlTMR.h"


namespace htl {
	namespace tick {

		class TickGenerator {
			private:
				using TMRDeviceNotificationEvent = htl::tmr::TMRDevice::NotificationEvent<TickGenerator>;

			private:
				static TickGenerator _instance;
				volatile uint32_t _tickCounter;
				TMRDeviceNotificationEvent _tmrNotificationEvent;

			public:
				static constexpr TickGenerator* pInst = &_instance;
                static constexpr TickGenerator& rInst = _instance;

			private:
				TickGenerator();
				TickGenerator(const TickGenerator&) = delete;
				void tmrNotificationEventHandler(htl::tmr::TMRDevice *sender, htl::tmr::TMRDevice::NotificationEventArgs *args);

			public:
				void initialize(uint32_t frequency);
				void deinitialize();
				void start();
				void stop();
				uint32_t getTick();
				void wait(uint32_t ticks);
		};

	}
}


#endif // __htlTick__
