#pragma once
#ifndef __eos_canopen_sdo_server__
#define __eos_canopen_sdo_server__


#include "eos.h"
#include "System/eosResults.h"


namespace eos {

	class CanOpenDictionary;

	class CanOpenSDOServer final {
		public:
			enum class State {
				idle,
				downloading,
				uploading
			};

		private:
			CanOpenDictionary * const _dictionary;
			State _state;
			unsigned _maxCount;
			unsigned _count;
			bool _toggle;

		private:
            void onInitiateDownloadExpedited(const uint8_t *query, uint8_t *response);
            void onInitiateDownloadNormal(const uint8_t *query, uint8_t *response);
            void onDownloadSegment(const uint8_t *query, uint8_t *response);
            void onInitiateUpload(const uint8_t *query, uint8_t *response);
            void onUploadSegment(const uint8_t *query, uint8_t *response);
            void onAbort(const uint8_t *query, uint8_t *response);

		public:
			CanOpenSDOServer(CanOpenDictionary *dictionary);

            Result process(const uint8_t *query, uint8_t *response);

            inline State getState() const { return _state; }
            inline bool isBusy() const { return _state != State::idle; }
	};
}


#endif // __eos_canopen_sdoserver__




