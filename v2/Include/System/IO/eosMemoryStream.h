#pragma once


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

    class MemoryStream: public Stream {
        private:
            uint8_t *_buffer;
            uint16_t _bufferSize;
            
    	public:
            MemoryStream(uint8_t *buffer, uint16_t bufferSize);
    		~MemoryStream();
            
    		uint16_t write(const uint8_t *data, uint16_t size) override;
    		uint16_t read(uint8_t *data, uint16_t size) override;
            
            inline uint8_t *getBuffer() const { return buffer; }
            inline int getBufferSize() const { return bufferSize; }
    };

}
