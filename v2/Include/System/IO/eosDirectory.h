#ifndef __eosDirectory__
#define __eosDirectory__


#include "eos.h"
#include "System/Core/eosString.h"


namespace eos {

    class Directory {
        public:
            static bool Exists(const String &directoryName);
    };
}


#endif // __eosDirectory__
