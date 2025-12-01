#pragma once
#ifndef __eos_canopen_service_slave__
#define __eos_canopen_service_slave__


#include "eos.h"
#include "Services/CanOpen/eos_canopen_service.h"
#include "Services/CanOpen/eos_canopen_sdo_server.h"
#include "Services/CanOpen/eos_canopen_tpdo_transmitter.h"


namespace eos {

	class CanOpenServiceSlave final: public CanOpenService {
		private:
			CanOpenSDOServer _sdoServer;
			CanOpenTPDOTransmitter _tpdoTransmitter;

		private:
			void processSDO(const uint8_t *data);
			void processNMT(const uint8_t *data);
			void processSYNC();

		protected:
			void process(uint16_t cobid, const uint8_t *data) override;

		public:
			CanOpenServiceSlave(InitParams const &params);

			void sendTPDO(unsigned tpdoId);
	};
}


#endif // __eos_canopen_service_slave__
