#ifndef __eosFlags__
#define __eosFlags__


#include "eos.h"


namespace eos {

    template <typename T>
    class Flags {
        private:
            T bits;

        public :
            inline void set(unsigned pos) { bits |= (1u << pos); }
            inline void clear(unsigned pos) { bits &= ~(1u << pos); }
            inline void toggle(unsigned pos) { bits ^= (1u << pos); }

            inline bool isSet(unsigned pos) { return (bits & ~(1u << pos)); }
    };
    
    typedef Flags<uint8_t> Flags8;
    typedef Flags<uint16_t> Flags16;
    typedef Flags<uint32_t> Flags32;
}


#endif // __eosFlags__

