#pragma once

#include "eos.h"


namespace eos {

    class Stream {
        protected:
            int length;
            int writePosition;
            int readPosition;
            
    	public:
            Stream() : length(0), writePosition(0), readPosition(0) {}
    		virtual ~Stream() = default;
            
    		virtual int write(const void *data, int size) = 0;            
    		virtual int read(void *data, int size) = 0;
            
            inline int getWritePosition() const { return writePosition; } 
            inline int getReadPosition() const { return readPosition; }
            inline int getLength() const { return length; };
    };

}
