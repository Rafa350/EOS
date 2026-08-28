module;

#include <cstdint>
#include <cmath>


export module Eos.Math;


export namespace eos {

	class Math final {
		public:
			template <typename T>
			static T min(T a, T b);

			template <typename T>
			static T max(T a, T b);

			static uint8_t loByte(uint16_t b);
			static uint8_t hiByte(uint16_t b);

			static void unPack(uint16_t data, uint8_t &b1, uint8_t &b0);
			static void unPack(uint32_t data, uint8_t &b3, uint8_t &b2, uint8_t &b1, uint8_t &b0);
			static void unPack(uint32_t data, uint16_t &w1, uint16_t &w0);

			template <typename T>
			static void swap(T &a, T &b);

			template <typename T>
			static T abs(T v);

			template <typename T>
			static T sqrt(T v);

			static constexpr uint32_t maxU32 = std::numeric_limits<uint32_t>::max();
			static constexpr uint32_t maxU16 = std::numeric_limits<uint16_t>::max();
			static constexpr uint32_t maxU8  = std::numeric_limits<uint8_t>::max();
			static constexpr uint32_t minU32 = std::numeric_limits<uint32_t>::min();
			static constexpr uint32_t minU16 = std::numeric_limits<uint16_t>::min();
			static constexpr uint32_t minU8  = std::numeric_limits<uint8_t>::min();
	};
}


/// ----------------------------------------------------------------------
/// \brief    Obte el minim de dos valors.
/// \param    a: Primer valor.
/// \param    b: Segon valor.
/// \return   El valor minim.
///
template <typename T>
inline T eos::Math::min(
	T a,
	T b) {

	return std::min(a, b);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el maxim de dos valors.
/// \param    a: Primer valor.
/// \param    b: Segon valor.
/// \return   El valor maxim.
///
template <typename T>
inline T eos::Math::max(
	T a,
	T b) {

	return std::max(a, b);
}


/// ----------------------------------------------------------------------
/// \brief    Obte els 8 bits LSB d'un valor de 16 bits.
/// \param    v: El valor de 16 bits
/// \return   Els 8 bits LSB
///
inline uint8_t eos::Math::loByte(
	uint16_t v) {

	return (uint8_t) v;
}


/// ----------------------------------------------------------------------
/// \brief    Obte els 8 bits MSB d'un valor de 16 bits.
/// \param    v: El valor de 16 bits.
/// \return   Els 8 bits MSB.
///
inline uint8_t eos::Math::hiByte(
	uint16_t b) {

	return (uint8_t) (b >> 8);
}


/// ----------------------------------------------------------------------
/// \brief    Separa un uint16_t en dos uint8_t
/// \param    data: El valor d'entrada.
/// \param    b1: Els bits b15 a b8.
/// \param    b0: Els bits b7 a b0.
///
void eos::Math::unPack(
	uint16_t data,
	uint8_t &b1,
	uint8_t &b0) {

	b1 = (data >> 8) & 0x0F;
	b0 = (data >> 0) & 0x0F;
}


/// ----------------------------------------------------------------------
/// \brief    Separa un uint32_t en quatre uint8_t
/// \param    data: El valor d'entrada.
/// \param    b3: Els bits b31 a b24.
/// \param    b2: Els bits b23 a b16.
/// \param    b1: Els bits b15 a b8.
/// \param    b0: Els bits b7 a b0.
///
void eos::Math::unPack(
	uint32_t data,
	uint8_t &b3,
	uint8_t &b2,
	uint8_t &b1,
	uint8_t &b0) {

	b3 = (data >> 24) & 0xFF;
	b2 = (data >> 16) & 0xFF;
	b1 = (data >> 8) & 0xFF;
	b0 = (data >> 0) & 0xFF;
}


/// ----------------------------------------------------------------------
/// \brief    Separa un uint32_t en dos uint16_t
/// \param    data: El valor d'entrada.
/// \param    w1: Els bits b31 a b16.
/// \param    w0: Els bits b15 a b0.
///
void eos::Math::unPack(
	uint32_t data,
	uint16_t &w1,
	uint16_t &w0) {

	w1 = (data >> 16) & 0xFFFF;
	w0 = (data >> 0) & 0xFFFF;
}


/// ----------------------------------------------------------------------
/// \brief    Intervancia dos valors.
/// \param    a: El primer valor.
/// \param    b: El segon valor.
///
template <typename T>
inline void eos::Math::swap(
	T &a,
	T &b) {

	std::swap(a, b);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor absolut d'un nombre.
/// \param    v: El nombre.
/// \return   El resultat de l'operacio.
///
template <typename T>
inline T eos::Math::abs(
	T v) {

	return std::abs(v);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de l'arrel quadrada d'un nombre.
/// \param    v: El nombre.
/// \return   El resultat de l'operacio.
///
template <typename T>
inline T eos::Math::sqrt(
	T v) {

	return std::sqrt(v);
}
