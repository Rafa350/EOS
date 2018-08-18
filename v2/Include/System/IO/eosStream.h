#ifndef __eosStream__
#define	__eosStream__


#include "eos.h"

#include <stdint.h>


namespace eos {


    class Stream {
    	public:
    		virtual ~Stream() {}
    		virtual uint32_t write(void *data, uint32_t size) = 0;
    		virtual uint32_t read(void *data, uint32_t size) = 0;
    };

}


#endif // __eosStream__

