#pragma once
#ifndef __eosTextStreamWriter__
#define __eosTextStreamWriter__


#include "eos.h"


namespace eos {
    
    /// \brief Objecte per escriure en un stream.
    ///
    class TextStreamWriter {
        private:
            uint8_t * const _begin;
            uint8_t * const _end;
            uint8_t * _ptr;
            
        public:
            TextStreamWriter(uint8_t *buffer, unsigned size);
            
            bool write(uint8_t data);
            bool write(uint16_t data);
            bool write(uint32_t data);
            inline bool write(int8_t data) { return write(static_cast<uint8_t>(data)); }
            inline bool write(int16_t data) { return write(static_cast<uint16_t>(data)); }
            inline bool write(int32_t data) { return write(static_cast<uint32_t>(data)); }
            bool write(const uint8_t *data, unsigned size);
            bool write(const char *fmt, ...);
            bool write(bool data);

            inline const uint8_t * data() const {
                return _begin;
            }

            inline uint16_t length() const {
                return _ptr - _begin;
            }
    };
    
}


#endif // __eosTextStreamWriter__
