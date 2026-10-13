module;


#include "eos.h"


export module Eos.System.IO.Streams;


import Eos.Result;
import Eos.Types;


export namespace eos {

    class Stream: private NonCopyableClass {
    	public:
    		virtual ~Stream() = default;

    		virtual StdResultU32 write(const UInt8 *buffer, UInt32 length) = 0;
    		virtual StdResultU32 read(UInt8 *buffer, UInt32 bufferSize) = 0;
    };

}
