#ifndef __eosMemoryStream__
#define	__eosMemoryStream__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

    class MemoryStream: public Stream {
        private:
            uint8_t *buffer;
            int bufferSize;
            
    	public:
            MemoryStream(uint8_t *buffer, int bufferSize);
    		~MemoryStream();
            
    		int write(const void *data, int size) override;
    		int read(void *data, int size) override;
            
            inline uint8_t *getBuffer() const { return buffer; }
            inline int getBufferSize() const { return bufferSize; }
    };

}


#endif // __eosMemoryStream__

