#pragma once
#ifndef __eosBinaryStreamReader__
#define __eosBinaryStreamReader__


// EOS includes
//
#include "eos.h"


namespace eos {

    class BinaryStreamReader {
        private:
            const uint8_t * const _begin;
            const uint8_t * const _end;
            const uint8_t * _ptr;

        public:
            BinaryStreamReader(const uint8_t *buffer, uint32_t size);

            inline uint8_t peek() const {
                return *_ptr;
            }

            bool readU8(uint8_t &data);
            bool readU16(uint16_t &data);
            bool readU32(uint32_t &data);
            bool readI8(int8_t &data);
            bool readI16(int16_t &data);
            bool readI32(int32_t &data);
            bool read(uint8_t *data, unsigned size);

            inline bool eof() const {
                return _ptr == _end;
            }

            inline const uint8_t * data() const {
                return _begin;
            }

            inline uint32_t length() const {
                return _ptr - _begin;
            }
    };

}


#endif // __eosBinaryStreamReader__
