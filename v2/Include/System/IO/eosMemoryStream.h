#pragma once

#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

	/// \brief Stream en memoria de tamany fix.
	///
    class MemoryStream final: public Stream {
        private:
            uint8_t * const _begin;
            uint8_t * const _end;
            uint8_t *_ptr;

    	public:
            MemoryStream();
            MemoryStream(uint8_t *buffer, uint32_t size);

            Result initialize(uint8_t *buffer, uint32_t size);

            uint32_t getPosition() const;
            void setPosition(uint32_t position);

    		ResultU32 write(const uint8_t *buffer, uint32_t length) override;
    		ResultU32 read(uint8_t *buffer, uint32_t bufferSize) override;

            inline uint8_t *data() const { return _begin; }
            inline uint32_t size() const { return _end - _begin; }
    };

}
