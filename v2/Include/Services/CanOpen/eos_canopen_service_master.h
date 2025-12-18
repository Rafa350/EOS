#pragma once
#ifndef __eos_canopen_service_master__
#define __eos_canopen_service_master__


#include "eos.h"
#include "System/eosEvents.h"
#include "Services/CanOpen/eos_canopen_service.h"


namespace eos {

	class CanOpenMasterService final: public CanOpenService {
		public:
			struct TPDOReceivedEventArgs {
				uint16_t cobid;
				uint8_t dataLen;
				const uint8_t *data;
			};
			using TPDOReceivedEventRaiser = eos::EventRaiser<CanOpenMasterService, TPDOReceivedEventArgs>;
			using ITPDOReceivedEvent = TPDOReceivedEventRaiser::IEvent;
			template <typename Instance_> using TPDOReceivedEvent = TPDOReceivedEventRaiser::Event<Instance_>;

		private:
			TPDOReceivedEventRaiser _erTPDOReceived;

		protected:
			void processFrame(uint16_t cobid, const uint8_t *data, unsigned dataLen) override;
			void processHeartbeat(uint8_t nodeId, uint8_t status);
			void processTPDOFrame(uint16_t cobid, const uint8_t *data, unsigned dataLen);

			void raiseTPDOReceivedEvent(uint16_t cobid, const uint8_t *data, unsigned dataLen);

		public:
			CanOpenMasterService(InitParams const &params);

			// Operacions SDO
			//
			Result sdoUpload(unsigned nodeId, uint16_t index, uint8_t subIndex, unsigned timeout);
			void sdoInitiateUpload();
			void sdoSegmentUpload();
			Result sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, uint32_t value, unsigned timeout);
			void sdoDownload(unsigned nodeId, uint16_t index, uint8_t subindex, const uint8_t data, uint32_t length, unsigned timeout);
			void sdoInitiateDownload();
			void sdoSegmentDownload();
			void sdoAbort();

			// Operacions NMT
			//
			Result nmtStartNode(uint8_t nodeId, unsigned timeout);
			Result nmtStopNode(uint8_t nodeId);
			Result nmtEnterPreOperational(uint8_t nodeId);
			Result nmtResetNode(uint8_t nodeId);
			Result nmtResetCommunication(uint8_t nodeId);

			// Operacions SYNC
			//
			Result sync(unsigned timeout);

			void setTPDOReceivedEvent(ITPDOReceivedEvent &event, bool enabled = true);
	};
}


#endif // __eos_canopen_service_master__
