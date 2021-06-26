#ifndef __eosColorMath__
#define __eosColorMath__


// EOS includes
//
#include "eos.h"


namespace eos {

    namespace ColorMath {
		uint16_t combineColor_RGB565(uint16_t b, uint16_t f, uint8_t o);
		uint8_t grayAverage(uint8_t r, uint8_t g, uint8_t b);
		uint8_t grayWeight(uint8_t r, uint8_t g, uint8_t b);
    }
}


#endif // __eosColorMath__
