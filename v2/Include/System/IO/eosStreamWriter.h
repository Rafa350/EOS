#ifndef __eosStreamWriter__
#define __eosStreamWriter__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {
    
    /// \brief Objecte per escriure en un stream.
    ///
    class StreamWriter {
        private:
            Stream &stream;
            
        public:
            StreamWriter(Stream &stream);
            
            void write(uint8_t data);
            void write(uint16_t data);
            void write(uint32_t data);
            void write(const void *data, int size);
            
            inline Stream& getStream() const { return stream; }
    };
    
}


#endif // __eosStreamWriter__
