#ifndef __eosMemoryStream__
#define	__eosMemoryStream__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

    class MemoryStream: public Stream {
        private:
            uint8_t *buffer;
            int bufferSize;
            int position;
            
    	public:
            MemoryStream(uint8_t *buffer, int bufferSize);
    		~MemoryStream();
            
    		int write(const uint8_t *data, int size) override;
    		int read(uint8_t *data, int size) override;
            
            inline uint8_t *getBuffer() const { return buffer; }
            inline int getBufferSize() const { return bufferSize; }
            inline int getAvailableSize() const { return bufferSize - position; }
            inline int getPosition() const { return position; }
    };

}


#endif // __eosMemoryStream__

