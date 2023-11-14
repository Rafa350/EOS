#pragma once


#include "HTL/htl.h"
#include "HTL/htlTMR.h"


namespace htl {

	namespace tick {

		class TickGenerator {
			private:
				static TickGenerator _instance;
				volatile uint32_t _tickCounter;
				htl::tmr::NotifyEvent<TickGenerator> _tmrNotifyEvent;
			public:
				static constexpr TickGenerator* pInst = &_instance;
                static constexpr TickGenerator& rInst = _instance;
			private:
				TickGenerator();
				TickGenerator(const TickGenerator&) = delete;
				void tmrNotifyEventHandler(htl::tmr::TMRDevice *sender, htl::tmr::NotifyEventArgs &args);
			public:
				void initialize(uint32_t frequency);
				void deinitialize();
				void start();
				void stop();
				uint32_t getTickCount();
				void wait(uint32_t ticks);
				static constexpr TickGenerator* getHandler() {
					return &_instance;
				}
		};
        
        typedef TickGenerator * TickGeneratorHandler;


        inline void delay(uint32_t time) {
            TickGenerator::getHandler()->wait(time);
        }

	}
}

