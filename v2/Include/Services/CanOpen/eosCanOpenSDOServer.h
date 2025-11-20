#pragma once
#ifndef __eosCanOpenSDOServer__
#define __eosCanOpenSDOServer__


#include "eos.h"
#include "System/eosResults.h"


namespace eos {

	class CanOpenDictionary;

	class CanOpenSDOServer {
		private:
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

		public:
			CanOpenSDOServer(CanOpenDictionary *dictionary);

            Result process(const uint8_t *query, uint8_t *response);
            void processInitiateDownloadExpedited(const uint8_t *query, uint8_t *response);
            void processInitiateDownloadNormal(const uint8_t *query, uint8_t *response);
            void processDownloadSegment(const uint8_t *query, uint8_t *response);
            void processInitiateUpload(const uint8_t *query, uint8_t *response);
            void processUploadSegment(const uint8_t *query, uint8_t *response);
            void processAbort(const uint8_t *query, uint8_t *response);
	};
}


#endif // __eosCanOpenSDOServer__




