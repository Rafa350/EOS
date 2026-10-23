module;


#include <cstdint>


export module Eos.Types;


export namespace eos {

    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;

    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;

    
    template <typename T_>
    class BufferAdapter {
        public:
            using DataType = T_;
            using DataPtr = DataType*;

        private:
            DataPtr const _data;
            UInt32 const _size;

        public:
            BufferAdapter(DataPtr data, UInt32 size): _data {data}, _size {size} {}
            BufferAdapter(const BufferAdapter &other): _data {other._data}, _size {other._size} {}

            DataPtr getData() const { return _data; }
            UInt32 getSize() const { return _size; }
    };

    using UInt8Buffer = BufferAdapter<UInt8>;
    using UInt16Buffer = BufferAdapter<UInt16>;
    using UInt32Buffer = BufferAdapter<UInt32>;


    class NonCopyableClass {
        protected:
            NonCopyableClass() = default;  // Permet que les classes filles es construeixin
            ~NonCopyableClass() = default; // Permet que les classes filles es destrueixin

        public:
            // Eliminem la còpia de forma explícita
            NonCopyableClass(const NonCopyableClass&) = delete;
            NonCopyableClass& operator=(const NonCopyableClass&) = delete;

            // Eliminen el moviment de forma explicita
            NonCopyableClass(NonCopyableClass&&) = delete;
            NonCopyableClass& operator=(NonCopyableClass&&) = delete;
    };


    template <typename T_>
    class StaticClass {
        protected:
            // Evita completament la instanciació de qualsevol forma
            StaticClass() = delete;
            ~StaticClass() = delete;

        public:
            // Elimina explícitament la còpia i el moviment
            StaticClass(const StaticClass&) = delete;
            StaticClass& operator=(const StaticClass&) = delete;
            StaticClass(StaticClass&&) = delete;
            StaticClass& operator=(StaticClass&&) = delete;
    };
}
