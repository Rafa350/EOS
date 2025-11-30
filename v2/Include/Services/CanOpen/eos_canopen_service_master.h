#pragma once
#ifndef __eos_canopen_service_master__
#define __eos_canopen_service_master__


#include "eos.h"
#include "Services/CanOpen/eos_canopen_service.h"


namespace eos {

	class CanOpenServiceMaster final: public CanOpenService {
		protected:
			void process(uint16_t cobid, const uint8_t *data) override;

		public:
			CanOpenServiceMaster(InitParams const &params);

			void sdoUpload(unsigned nodeId, uint16_t index, uint8_t subIndex);
			void sdoInitiateUpload();
			void sdoSegmentUpload();
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value);
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, const uint8_t data, uint32_t length);
			void sdoInitiateDownload();
			void sdoSegmentDownload();
			void sdoAbort();
	};
}


#endif // __eos_canopen_service_master__
