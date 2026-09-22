module;


#include "stdint.h"


export module Eos.Types;


export namespace eos {

    using U8 = uint8_t;
    using U16 = uint16_t;
    using U32 = uint32_t;

    using I8 = int8_t;
    using I16 = int16_t;
    using I32 = int32_t;

    template <typename T_>
    class ArrayAdapter {
        private:
            T_* const _data;
            U32 const _size;

        public:
            ArrayAdapter(T_ *data, U32 size): _data {data}, _size {size} {}
            ArrayAdapter(const ArrayAdapter &other): _data {other._data}, _size {other._size} {}

            T_* getData() const { return _data; }
            U32 getSize() const { return _size; }
    };

    using U8Array = ArrayAdapter<U8>;
    using U16Array = ArrayAdapter<U16>;
    using U32Array = ArrayAdapter<U32>;
}
