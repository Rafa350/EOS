module;


#include "HTL/htl.h"
#include <type_traits>


export module Htl.Regs;


export namespace htl {

    template <typename T_, uint32_t addr_>
    struct Reg {
        static T_ read();
        static void write(T_ value);
    };

    template <uint32_t addr_>
    using Reg8 = Reg<uint8_t, addr_>;

    template <uint32_t addr_>
    using Reg16 = Reg<uint16_t, addr_>;

    template <uint32_t addr_>
    using Reg32 = Reg<uint32_t, addr_>;


    template <typename T_, uint32_t addr_, uint32_t pos_, uint32_t width_>
    struct RegField {
        static T_ read();
        static void write(T_ value);
    };

    template <uint32_t addr_, uint32_t pos_, uint32_t width_>
    using Reg8Field = RegField<uint8_t, addr_, pos_, width_>;

    template <uint32_t addr_, uint32_t pos_, uint32_t width_>
    using Reg16Field = RegField<uint16_t, addr_, pos_, width_>;

    template <uint32_t addr_, uint32_t pos_, uint32_t width_>
    using Reg32Field = RegField<uint32_t, addr_, pos_, width_>;


    template <typename T_, uint32_t addr_, uint32_t pos_>
    struct RegFlag {
        static bool isSet();
        static void set();
        static void clear();
    };

    template <uint32_t addr_, uint32_t pos_>
    using Reg8Flag = RegFlag<uint8_t, addr_, pos_>;

    template <uint32_t addr_, uint32_t pos_>
    using Reg16Flag = RegFlag<uint16_t, addr_, pos_>;

    template <uint32_t addr_, uint32_t pos_>
    using Reg32Flag = RegFlag<uint32_t, addr_, pos_>;

}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el valor d'un registre.
/// \tparam   T_: El tipus de dades del registre.
/// \tparam   addr_: L'adressda del registre.
/// \return   El valor del registre.
///
template <typename T_, uint32_t addr_>
inline T_ htl::Reg<T_, addr_>::read() {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

    return *reinterpret_cast<volatile T_*>(addr_);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor en un registre.
/// \tparam   T_: El tipus de dades del registre.
/// \tparam   addr_: L'adressda del registre.
/// \param    value: El valor a escriure.
/// \return   El valor del registre.
///
template <typename T_, uint32_t addr_>
inline void htl::Reg<T_, addr_>::write(
	T_ value) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	*reinterpret_cast<volatile T_*>(addr_) = value;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el valor d'un camp d'ins d'un registre
/// \tparam   T_:El tipus de dades del registre.
/// \tparam   addr_: L'adressa del registre.
/// \tparamm  pos_: Posicio del camp en bits.
/// \tparam   width_: Amplada del camp en bits.
/// \return   El valor del camp.
///
template <typename T_, uint32_t addr_, uint32_t pos_, uint32_t width_>
inline T_ htl::RegField<T_, addr_, pos_, width_>::read() {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	constexpr T_ mask = (2 ^ width_) - 1;
    return ((*reinterpret_cast<volatile T_*>(addr_)) >> pos_) & mask;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el valor d'un camp d'ins d'un registre
/// \tparam   T_:El tipus de dades del registre.
/// \tparam   addr_: L'adressa del registre.
/// \tparamm  pos_: Posicio del camp en bits.
/// \tparam   width_: Amplada del camp en bits.
/// \param    value: El valor del camp.
///
template <typename T_, uint32_t addr_, uint32_t pos_, uint32_t width_>
inline void htl::RegField<T_, addr_, pos_, width_>::write(
	T_ value) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	constexpr T_ mask = (2 ^ width_) - 1;

	*reinterpret_cast<volatile T_*>(addr_) =
        ((*reinterpret_cast<volatile T_*>(addr_)) & (mask << pos_)) | ((value & mask) << pos_);
}


template <typename T_, uint32_t addr_, uint32_t pos_>
inline bool htl::RegFlag<T_, addr_, pos_>::isSet() {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return ((*reinterpret_cast<volatile T_*>(addr_)) & (1 << pos_)) != 0;
}


template <typename T_, uint32_t addr_, uint32_t pos_>
inline void htl::RegFlag<T_, addr_, pos_>::set() {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	*reinterpret_cast<volatile T_*>(addr_) |= 1 << pos_;
}


template <typename T_, uint32_t addr_, uint32_t pos_>
inline void htl::RegFlag<T_, addr_, pos_>::clear() {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	*reinterpret_cast<volatile T_*>(addr_) &= ~(1 << pos_);
}

