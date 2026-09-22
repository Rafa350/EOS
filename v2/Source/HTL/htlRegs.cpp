module;


#include "HTL/htl.h"


export module Htl.Regs;


import Eos.Concepts;
import Eos.Types;


export namespace htl {

    template <eos::IsUInt T_, uintptr_t addr_>
    struct Reg final: private eos::StaticClass<Reg<T_, addr_>> {
        static T_ read();
        static void write(T_ value);
    };

    template <uintptr_t addr_>
    using Reg8 = Reg<uint8_t, addr_>;

    template <uintptr_t addr_>
    using Reg16 = Reg<uint16_t, addr_>;

    template <uintptr_t addr_>
    using Reg32 = Reg<uint32_t, addr_>;


    template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_, uint32_t width_>
    struct RegField final: private eos::StaticClass<RegField<T_, addr_, pos_, width_>> {
        static T_ read();
        static void write(T_ value);
    };

    template <uintptr_t addr_, uint32_t pos_, uint32_t width_>
    using Reg8Field = RegField<uint8_t, addr_, pos_, width_>;

    template <uintptr_t addr_, uint32_t pos_, uint32_t width_>
    using Reg16Field = RegField<uint16_t, addr_, pos_, width_>;

    template <uintptr_t addr_, uint32_t pos_, uint32_t width_>
    using Reg32Field = RegField<uint32_t, addr_, pos_, width_>;


    template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_>
    struct RegFlag final: private eos::StaticClass<RegFlag<T_, addr_, pos_>> {
        static bool isSet();
        static void set();
        static void clear();
    };

    template <uintptr_t addr_, uint32_t pos_>
    using Reg8Flag = RegFlag<uint8_t, addr_, pos_>;

    template <uintptr_t addr_, uint32_t pos_>
    using Reg16Flag = RegFlag<uint16_t, addr_, pos_>;

    template <uintptr_t addr_, uint32_t pos_>
    using Reg32Flag = RegFlag<uint32_t, addr_, pos_>;

}


/// ----------------------------------------------------------------------
/// @brief    Llegeix el valor d'un registre.
/// @tparam   T_: El tipus de dades del registre.
/// @tparam   addr_: L'adressda del registre.
/// @return   El valor del registre.
///
template <eos::IsUInt T_, uintptr_t addr_>
inline T_ htl::Reg<T_, addr_>::read() {

    return *reinterpret_cast<volatile T_*>(addr_);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor en un registre.
/// @tparam   T_: El tipus de dades del registre.
/// @tparam   addr_: L'adressda del registre.
/// @param    value: El valor a escriure.
/// @return   El valor del registre.
///
template <eos::IsUInt T_, uintptr_t addr_>
inline void htl::Reg<T_, addr_>::write(
	T_ value) {

	*reinterpret_cast<volatile T_*>(addr_) = value;
}


/// ----------------------------------------------------------------------
/// @brief    Llegeix el valor d'un camp d'ins d'un registre
/// @tparam   T_:El tipus de dades del registre.
/// @tparam   addr_: L'adressa del registre.
/// @tparam   pos_: Posicio del camp en bits.
/// @tparam   width_: Amplada del camp en bits.
/// @return   El valor del camp.
///
template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_, uint32_t width_>
inline T_ htl::RegField<T_, addr_, pos_, width_>::read() {

	constexpr T_ mask = (2 ^ width_) - 1;
    return ((*reinterpret_cast<volatile T_*>(addr_)) >> pos_) & mask;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el valor d'un camp d'ins d'un registre
/// @tparam   T_:El tipus de dades del registre.
/// @tparam   addr_: L'adressa del registre.
/// @tparam   pos_: Posicio del camp en bits.
/// @tparam   width_: Amplada del camp en bits.
/// @param    value: El valor del camp.
///
template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_, uint32_t width_>
inline void htl::RegField<T_, addr_, pos_, width_>::write(
	T_ value) {

	constexpr T_ mask = (2 ^ width_) - 1;

	*reinterpret_cast<volatile T_*>(addr_) =
        ((*reinterpret_cast<volatile T_*>(addr_)) & (mask << pos_)) | ((value & mask) << pos_);
}


template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_>
inline bool htl::RegFlag<T_, addr_, pos_>::isSet() {

	return ((*reinterpret_cast<volatile T_*>(addr_)) & (1 << pos_)) != 0;
}


template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_>
inline void htl::RegFlag<T_, addr_, pos_>::set() {

	*reinterpret_cast<volatile T_*>(addr_) |= 1 << pos_;
}


template <eos::IsUInt T_, uintptr_t addr_, uint32_t pos_>
inline void htl::RegFlag<T_, addr_, pos_>::clear() {

	*reinterpret_cast<volatile T_*>(addr_) &= ~(1 << pos_);
}
