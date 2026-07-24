#pragma once

#include "eos.h"
#include "eosResults.h"


namespace eos {

    class Stream {
    	public:
    		virtual ~Stream() = default;

    		virtual ResultU32 write(const uint8_t *buffer, uint32_t length) = 0;
    		virtual ResultU32 read(uint8_t *buffer, uint32_t bufferSize) = 0;
    };

}
