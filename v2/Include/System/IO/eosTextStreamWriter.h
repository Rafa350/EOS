#pragma once
#ifndef __eosTextStreamWriter__
#define __eosTextStreamWriter__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {

    /// \brief Objecte per escriure en un stream.
    ///
    class TextStreamWriter {
        private:
    		Stream *_stream;

        public:
            TextStreamWriter();
            TextStreamWriter(Stream *stream);

            void initialize(Stream *stream);

            bool writeU8(uint8_t data);
            bool writeU16(uint16_t data);
            bool writeU32(uint32_t data);
            bool writeU8Hex(uint8_t data);
            bool writeU16Hex(uint16_t data);
            bool writeU32Hex(uint32_t data);
            bool writeI8(int8_t data);
            bool writeI16(int16_t data);
            bool writeI32(int32_t data);
            bool writeChar(char data);
            bool writeString(const char *data);
            bool writeBool(bool data);
    };

}


#endif // __eosTextStreamWriter__
