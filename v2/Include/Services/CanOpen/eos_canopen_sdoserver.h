#pragma once
#ifndef __eos_canopen_sdoserver__
#define __eos_canopen_sdoserver__


#include "eos.h"
#include "Services/CanOpen/eos_canopen_dictionary.h"
#include "System/eosResults.h"


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


#endif // __eos_canopen_sdoserver__
