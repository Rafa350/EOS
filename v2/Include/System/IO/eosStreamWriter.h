#pragma once


#include "eos.h"


namespace eos {
    
    /// \brief Objecte per escriure en un stream.
    ///
    class StreamWriter {
        private:
            uint8_t * const _begin;
            uint8_t * const _end;
            uint8_t * _ptr;
            
        public:
            StreamWriter(uint8_t *buffer, unsigned size);
            
            bool write(uint8_t data);
            bool write(uint16_t data);
            bool write(uint32_t data);
            bool write(const uint8_t *data, unsigned size);

            inline unsigned length() const {
                return _ptr - _begin;
            }

            inline uint8_t *data() const {
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
