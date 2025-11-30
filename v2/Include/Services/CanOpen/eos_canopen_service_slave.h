#pragma once
#ifndef __eos_canopen_service_slave__
#define __eos_canopen_service_slave__


#include "eos.h"
#include "Services/CanOpen/eos_canopen_service.h"
#include "Services/CanOpen/eos_canopen_sdoserver.h"


namespace eos {

	class CanOpenServiceSlave final: public CanOpenService {
		private:
			CanOpenSDOServer _sdoServer;

		private:
			void processSDO(const uint8_t *data);
			void processNMT(const uint8_t *data);
			void processSYNC();

		protected:
			void process(uint16_t cobid, const uint8_t *data) override;

		public:
			CanOpenServiceSlave(InitParams const &params);
	};
}


#endif // __eos_canopen_service_slave__
