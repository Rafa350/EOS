module;

#include <cstdint>
#include <cmath>


export module Eos.Math;

import Eos.Types;


export namespace eos {

	class Math final: private StaticClass<Math> {

		public:
			/// @brief  Obte el minim de dos valors.
			/// @param  a: Primer valor.
			/// @param  b: Segon valor.
			/// @return El valor minim.
			///
			template <typename T>
			static T min(T a, T b) { return std::min(a, b); }

			/// @brief  Obte el maxim de dos valors.
			/// @param  a: Primer valor.
			/// @param  b: Segon valor.
			/// @return El valor maxim.
			///
			template <typename T>
			static T max(T a, T b) { return std::max(a, b); }

			static inline UInt8 loByte(UInt16 b);
			static inline UInt8 hiByte(UInt16 b);

			static void unPack(UInt16 data, UInt8 &b1, UInt8 &b0);
			static void unPack(UInt32 data, UInt8 &b3, UInt8 &b2, UInt8 &b1, UInt8 &b0);
			static void unPack(UInt32 data, UInt16 &w1, UInt16 &w0);

			/// @brief  Intercanvia dos valors.
			/// @param  a: El primer valor.
			/// @param  b: El segon valor.
			///
			template <typename T>
			static void swap(T &a, T &b) { return std::swap(a, b); }

			/// @brief  Obte el valor absolut d'un nombre.
			/// @param  v: El nombre.
			/// @return El resultat de l'operacio.
			///
			template <typename T>
			static T abs(T v) { return std::abs(v); }

			/// @brief  Obte el valor de l'arrel quadrada d'un nombre.
			/// @param  v: El nombre.
			/// @return El resultat de l'operacio.
			///
			template <typename T>
			static T sqrt(T v) { return std::sqrt(v); }

			static constexpr auto maxU32 = std::numeric_limits<UInt32>::max();
			static constexpr auto maxU16 = std::numeric_limits<UInt16>::max();
			static constexpr auto maxU8  = std::numeric_limits<UInt8>::max();
			static constexpr auto minU32 = std::numeric_limits<UInt32>::min();
			static constexpr auto minU16 = std::numeric_limits<UInt16>::min();
			static constexpr auto minU8  = std::numeric_limits<UInt8>::min();

			static constexpr auto maxI32 = std::numeric_limits<Int32>::max();
			static constexpr auto maxI16 = std::numeric_limits<Int16>::max();
			static constexpr auto maxI8  = std::numeric_limits<Int8>::max();
			static constexpr auto minI32 = std::numeric_limits<Int32>::min();
			static constexpr auto minI16 = std::numeric_limits<Int16>::min();
			static constexpr auto minI8  = std::numeric_limits<Int8>::min();
	};
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Obte els 8 bits LSB d'un valor de 16 bits.
/// @param    v: El valor de 16 bits
/// @return   Els 8 bits LSB
///
UInt8 Math::loByte(
	UInt16 v) {

	return (UInt8) v;
}


/// ----------------------------------------------------------------------
/// @brief    Obte els 8 bits MSB d'un valor de 16 bits.
/// @param    v: El valor de 16 bits.
/// @return   Els 8 bits MSB.
///
UInt8 Math::hiByte(
	UInt16 b) {

	return (UInt8) (b >> 8);
}


/// ----------------------------------------------------------------------
/// @brief    Separa un UInt16 en dos UInt8
/// @param    data: El valor d'entrada.
/// @param    b1: Els bits b15 a b8.
/// @param    b0: Els bits b7 a b0.
///
void Math::unPack(
	UInt16 data,
	UInt8 &b1,
	UInt8 &b0) {

	b1 = (data >> 8) & 0x0F;
	b0 = (data >> 0) & 0x0F;
}


/// ----------------------------------------------------------------------
/// @brief    Separa un UInt32 en quatre UInt8
/// @param    data: El valor d'entrada.
/// @param    b3: Els bits b31 a b24.
/// @param    b2: Els bits b23 a b16.
/// @param    b1: Els bits b15 a b8.
/// @param    b0: Els bits b7 a b0.
///
void Math::unPack(
	UInt32 data,
	UInt8 &b3,
	UInt8 &b2,
	UInt8 &b1,
	UInt8 &b0) {

	b3 = (data >> 24) & 0xFF;
	b2 = (data >> 16) & 0xFF;
	b1 = (data >> 8) & 0xFF;
	b0 = (data >> 0) & 0xFF;
}


/// ----------------------------------------------------------------------
/// @brief    Separa un UInt32 en dos UInt16
/// @param    data: El valor d'entrada.
/// @param    w1: Els bits b31 a b16.
/// @param    w0: Els bits b15 a b0.
///
void Math::unPack(
	UInt32 data,
	UInt16 &w1,
	UInt16 &w0) {

	w1 = (data >> 16) & 0xFFFF;
	w0 = (data >> 0) & 0xFFFF;
}
