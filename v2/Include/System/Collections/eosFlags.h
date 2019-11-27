#ifndef __eosFlags__
#define __eosFlags__


#include "eos.h"


namespace eos {

    template <typename T>
    class Flags {
        private:
            T bits;

        public :
            inline void set(int pos) { bits |= (1 << pos); }
            inline void clear(int pos) { bits &= ~(1 << pos); }
            inline void toggle(int pos) { bits ^= (1 << pos); }

            inline bool isSet(int pos) { return (bits & ~(1 << pos)); }
    };
}


#endif // __eosFlags__

