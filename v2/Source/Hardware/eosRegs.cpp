module;


#include <cstdint>


export module Eos.Hardware.Regs;


import Eos.Concepts;
import Eos.Types;


export namespace eos {

    namespace hardware {

        template <IsUInt T_, std::uintptr_t addr_>
        struct Reg final: private StaticClass<Reg<T_, addr_>> {
            static T_ read();
            static void write(T_ value);
        };

        template <std::uintptr_t addr_>
        using Reg8 = Reg<UInt8, addr_>;

        template <std::uintptr_t addr_>
        using Reg16 = Reg<UInt16, addr_>;

        template <std::uintptr_t addr_>
        using Reg32 = Reg<UInt32, addr_>;


        template <IsUInt T_, std::uintptr_t addr_, UInt32 pos_, UInt32 width_>
        struct RegField final: private StaticClass<RegField<T_, addr_, pos_, width_>> {
            static T_ read();
            static void write(T_ value);
        };

        template <std::uintptr_t addr_, UInt32 pos_, UInt32 width_>
        using Reg8Field = RegField<UInt8, addr_, pos_, width_>;

        template <std::uintptr_t addr_, UInt32 pos_, UInt32 width_>
        using Reg16Field = RegField<UInt16, addr_, pos_, width_>;

        template <std::uintptr_t addr_, UInt32 pos_, UInt32 width_>
        using Reg32Field = RegField<UInt32, addr_, pos_, width_>;


        template <IsUInt T_, std::uintptr_t addr_, UInt32 pos_>
        struct RegFlag final: private StaticClass<RegFlag<T_, addr_, pos_>> {
            static bool isSet();
            static void set();
            static void clear();
        };

        template <std::uintptr_t addr_, UInt32 pos_>
        using Reg8Flag = RegFlag<UInt8, addr_, pos_>;

        template <std::uintptr_t addr_, UInt32 pos_>
        using Reg16Flag = RegFlag<UInt16, addr_, pos_>;

        template <std::uintptr_t addr_, UInt32 pos_>
        using Reg32Flag = RegFlag<UInt32, addr_, pos_>;

    }
}


using namespace eos;
using namespace eos::hardware;


/// ----------------------------------------------------------------------
/// @brief    Llegeix el valor d'un registre.
/// @tparam   T_: El tipus de dades del registre.
/// @tparam   addr_: L'adressda del registre.
/// @return   El valor del registre.
///
template <IsUInt T_, uintptr_t addr_>
T_ Reg<T_, addr_>::read() {

    return *reinterpret_cast<volatile T_*>(addr_);
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un valor en un registre.
/// @tparam   T_: El tipus de dades del registre.
/// @tparam   addr_: L'adressda del registre.
/// @param    value: El valor a escriure.
/// @return   El valor del registre.
///
template <IsUInt T_, uintptr_t addr_>
void Reg<T_, addr_>::write(
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
template <IsUInt T_, uintptr_t addr_, UInt32 pos_, UInt32 width_>
T_ RegField<T_, addr_, pos_, width_>::read() {

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
template <IsUInt T_, uintptr_t addr_, UInt32 pos_, UInt32 width_>
void RegField<T_, addr_, pos_, width_>::write(
	T_ value) {

	constexpr T_ mask = (2 ^ width_) - 1;

	*reinterpret_cast<volatile T_*>(addr_) =
        ((*reinterpret_cast<volatile T_*>(addr_)) & (mask << pos_)) | ((value & mask) << pos_);
}


template <IsUInt T_, uintptr_t addr_, UInt32 pos_>
bool RegFlag<T_, addr_, pos_>::isSet() {

	return ((*reinterpret_cast<volatile T_*>(addr_)) & (1 << pos_)) != 0;
}


template <IsUInt T_, uintptr_t addr_, UInt32 pos_>
void RegFlag<T_, addr_, pos_>::set() {

	*reinterpret_cast<volatile T_*>(addr_) |= 1 << pos_;
}


template <IsUInt T_, uintptr_t addr_, UInt32 pos_>
void RegFlag<T_, addr_, pos_>::clear() {

	*reinterpret_cast<volatile T_*>(addr_) &= ~(1 << pos_);
}
