#pragma once
#ifndef __appLedService__
#define __appLedService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"


namespace app {

	class LedService: public eos::Service {
		public:
			static constexpr uint32_t stackSize = 128;
			static constexpr const char *serviceName = "LED";

		public:
			LedService();

		protected:
			void onInitialize() override;
			void onTask() override;
	};

}


#endif // __appLedService__
