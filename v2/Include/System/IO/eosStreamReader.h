#pragma once


// EOS includes
//
#include "eos.h"


namespace eos {

    class StreamReader {
        private:
            const uint8_t * const _begin;
            const uint8_t * const _end;
            const uint8_t * _ptr;

        public:
            StreamReader(const uint8_t *buffer, uint32_t size);

            inline uint8_t peek() const {
                return *_ptr;
            }

            bool read(uint8_t &data);
            bool read(uint16_t &data);
            bool read(uint32_t &data);
            bool read(int8_t &data);
            bool read(int16_t &data);
            bool read(int32_t &data);
            bool read(uint8_t *data, unsigned size);

            inline bool eof() const {
                return _ptr == _end;
            }

            inline unsigned length() const {
                return _ptr - _begin;
            }

            inline const uint8_t * data() const {
                return _begin;
            }

            inline const uint8_t* begin() const {
                return _begin;
            }

            inline const uint8_t* end() const {
                return _end;
            }
    };

}
