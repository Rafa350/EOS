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
            MemoryStream(uint8_t *buffer, unsigned size);

            Stream::Result initialize(uint8_t *buffer, unsigned size);

            unsigned getPosition() const;
            void setPosition(unsigned position);

    		Stream::Result write(const uint8_t *data, unsigned length, unsigned *count = nullptr) override;
    		Stream::Result read(uint8_t *data, unsigned size, unsigned *count = nullptr) override;

            inline uint8_t *data() const { return _begin; }
            inline unsigned size() const { return _end - _begin; }
    };

}
