#ifndef __eosStream__
#define	__eosStream__


#include "eos.h"


namespace eos {

    class Stream {
    	public:
    		virtual ~Stream() = default;
    		virtual int write(const uint8_t *data, int size) = 0;
    		virtual int read(uint8_t *data, int size) = 0;
    };

}


#endif // __eosStream__

