#ifndef __eosStream__
#define	__eosStream__


#include "eos.h"


namespace eos {


    class Stream {
    	public:
    		virtual ~Stream() = default;
    		virtual int write(void *data, int size) = 0;
    		virtual int read(void *data, int size) = 0;
    };

}


#endif // __eosStream__

