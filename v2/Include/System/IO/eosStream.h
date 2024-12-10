#pragma once

#include "eos.h"
#include "System/eosResults.h"


namespace eos {

    class Stream {
    	public:
    		virtual ~Stream() = default;

    		virtual Result write(const uint8_t *data, unsigned length, unsigned *count = nullptr) = 0;
    		virtual Result read(uint8_t *data, unsigned size, unsigned *count = nullptr) = 0;
    };

}
