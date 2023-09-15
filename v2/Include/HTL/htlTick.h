#pragma once
#ifndef __htlTick__
#define __htlTick__


#include "HTL/htl.h"
#include "HTL/htlTMR.h"


namespace htl {

	namespace tick {

		class Tick {
			private:
				static Tick _instance;
				volatile uint32_t _tickCounter;
				htl::tmr::NotifyEvent<Tick> _tmrNotifyEvent;
			private:
				Tick();
				Tick(const Tick&) = delete;
				void tmrNotifyEventHandler(htl::tmr::TMRDevice *sender, htl::tmr::NotifyEventArgs &args);
			public:
				void initialize();
				void deinitialize();
				uint32_t getTickCount();
				void wait(uint32_t time);
				static constexpr Tick* getHandler() {
					return &_instance;
				}
		};

	}
}

#endif // __htlTick__

