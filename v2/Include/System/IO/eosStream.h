#pragma once

#include "eos.h"
#include "System/eosResults.h"


namespace eos {

    class Stream {
    	public:
    		virtual ~Stream() = default;

    		virtual ResultU32 write(const uint8_t *data, unsigned length) = 0;
    		virtual ResultU32 read(uint8_t *data, unsigned size) = 0;
    };

}
