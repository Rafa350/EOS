#pragma once
#ifndef __eosCanOpenSdoServer__
#define __eosCanOpenSdoServer__


#include "eos.h"
#include "eosResults.h"
#include "Services/CanOpen/eosCanOpenDictionary.h"


namespace eos {

	class CanOpenDictionary;

	class SDOServer {
		private:
			CanOpenDictionary * const _dictionary;

		private:
			void upload(const uint8_t *request, uint8_t *response);
			void uploadSegment(const uint8_t *request, uint8_t *response);
			void download(const uint8_t *request, uint8_t *response);
			void downloadStart(const uint8_t *request, uint8_t *response);
			void downloadSegment(const uint8_t *request, uint8_t *response);

			void raiseWriteU8RequestEvent(uint16_t index, uint8_t subIndex, uint8_t value);
			void raiseWriteU16RequestEvent(uint16_t index, uint8_t subIndex, uint16_t value);
			void raiseWriteU32RequestEvent(uint16_t index, uint8_t subIndex, uint32_t value);

		public:
			SDOServer(CanOpenDictionary *dictionary);

			void processFrame(const uint8_t *request, uint8_t *response);
	};
}


#endif // __eosCanOpenSdoServer__
