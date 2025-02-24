#pragma once
#ifndef __htlTick__
#define __htlTick__


#include "HTL/htl.h"
#include "HTL/htlTMR.h"


namespace htl {
	namespace tick {

		class TickGenerator {
			private:
				static TickGenerator _instance;
				volatile unsigned _tickCounter;
				htl::tmr::NotifyEvent<TickGenerator> _tmrNotifyEvent;
			public:
				static constexpr TickGenerator* pInst = &_instance;
                static constexpr TickGenerator& rInst = _instance;
			private:
				TickGenerator();
				TickGenerator(const TickGenerator&) = delete;
				void tmrNotifyEventHandler(htl::tmr::NotifyID id, htl::tmr::NotifyEventArgs * const args);
			public:
				void initialize(unsigned frequency);
				void deinitialize();
				void start();
				void stop();
				unsigned getTick();
				void wait(unsigned ticks);
		};

	}
}


#endif // __htlTick__
