#pragma once


#include "htl.h"


namespace htl {

    template <typename T_, uint32_t addr_>
    struct Reg {
        using Type = T_;
        static constexpr uint32_t addr = addr_;
        static inline Type read() {
            return *reinterpret_cast<volatile Type*>(addr);
        }
        static inline void write(Type value) {
            *reinterpret_cast<volatile Type*>(addr) = value;
        }
    };
    
    template <uint32_t addr_> 
    using Reg8 = Reg<uint8_t, addr_>;
    
    template <uint32_t addr_> 
    using Reg16 = Reg<uint16_t, addr_>;
    
    template <uint32_t addr_> 
    using Reg32 = Reg<uint32_t, addr_>;


    template <typename T_, uint32_t addr_, uint32_t pos_, uint32_t width_>
    struct RegField {
        using Type = T_;
        static constexpr uint32_t addr = addr_;
        static constexpr uint32_t pos = pos_;
        static constexpr uint32_t width = width_;
        static constexpr Type mask = (2 ^ width_) - 1;
        static inline Type read() {
            return ((*reinterpret_cast<volatile Type*>(addr)) >> pos) & mask;
        }
        static inline void write(Type value) {
            *reinterpret_cast<volatile Type*>(addr) = 
                ((*reinterpret_cast<volatile Type*>(addr)) & (mask << pos)) | ((value & mask) << pos);
        }
    };

    template <uint32_t addr_, uint32_t pos_, uint32_t width_> 
    using Reg8Field = RegField<uint8_t, addr_, pos_, width_>;
    
    template <uint32_t addr_, uint32_t pos_, uint32_t width_> 
    using Reg16Field = RegField<uint16_t, addr_, pos_, width_>;
    
    template <uint32_t addr_, uint32_t pos_, uint32_t width_> 
    using Reg32Field = RegField<uint32_t, addr_, pos_, width_>;

    
    template <typename T_, uint32_t addr_, uint32_t pos_>
    struct RegFlag {
        using Type = T_;
        static constexpr uint32_t addr = addr_;
        static constexpr uint32_t pos = pos_;
        static constexpr Type mask = 1 << pos;
        static inline bool isSet() {
            return ((*reinterpret_cast<volatile Type*>(addr)) & mask) != 0;
        }
        static inline void set() {
            *reinterpret_cast<volatile Type*>(addr) |= 1 << pos;
        }
        static inline void clear() {
            *reinterpret_cast<volatile Type*>(addr) &= ~(1 << pos);
        }
    };

    template <uint32_t addr_, uint32_t pos_> 
    using Reg8Flag = RegFlag<uint8_t, addr_, pos_>;
    
    template <uint32_t addr_, uint32_t pos_> 
    using Reg16Flag = RegFlag<uint16_t, addr_, pos_>;
    
    template <uint32_t addr_, uint32_t pos_> 
    using Reg32Flag = RegFlag<uint32_t, addr_, pos_>;

} // namespace htl
