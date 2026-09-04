module;


#include "eos.h"
#include "eosResults.h"


export module Eos.System.IO.Formatters.Binary;


export import Eos.System.IO.Streams;


export namespace eos {

    class BinaryReader final {
        private:
            const uint8_t * const _begin;
            const uint8_t * const _end;
            const uint8_t * _ptr;

        public:
            BinaryReader(const uint8_t *buffer, unsigned bufferSize);

            inline void reset() { _ptr = _begin; }

            inline uint8_t peek() const { return *_ptr; }

            bool readU8(uint8_t &data);
            bool readU16(uint16_t &data);
            bool readU32(uint32_t &data);
            bool readI8(int8_t &data);
            bool readI16(int16_t &data);
            bool readI32(int32_t &data);
            bool read(uint8_t *data, unsigned size);

            inline bool eof() const { return _ptr == _end; }

            inline const uint8_t *data() const { return _begin; }
            inline unsigned length() const { return _ptr - _begin; }
    };

    class BinaryWriter final {
        private:
            uint8_t * const _begin;
            uint8_t * const _end;
            uint8_t * _ptr;

        public:
            BinaryWriter(uint8_t *buffer, unsigned bufferSize);

            inline void clear() { _ptr = _begin; }

            bool writeU8(uint8_t data);
            bool writeU16(uint16_t data);
            bool writeU32(uint32_t data);

            inline bool writeI8(int8_t data) {
            	return writeU8(static_cast<uint8_t>(data));
            }

            inline bool writI16(int16_t data) {
            	return writeU16(static_cast<uint16_t>(data));
            }

            inline bool writeI32(int32_t data) {
            	return writeU32(static_cast<uint32_t>(data));
            }

            bool write(const uint8_t *data, unsigned size);

            inline bool write(bool data) {
            	return writeU8(static_cast<uint8_t>(data));
            }

            inline const uint8_t * data() const { return _begin; }
            inline unsigned length() const { return _ptr - _begin; }
    };
}
