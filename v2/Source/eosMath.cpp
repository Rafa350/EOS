module;

#include <cstdint>
#include <cmath>


export module EosMath;


export namespace eos {

	class Math final {
		public:
			template <typename T>
			inline static T min(T a, T b);

			template <typename T>
			inline static T max(T a, T b);

			inline static uint8_t loByte(uint16_t b);
			inline static uint8_t hiByte(uint16_t b);

			template <typename T>
			inline static void swap(T &a, T &b);

			template <typename T>
			inline static T abs(T v);

			template <typename T>
			inline static T sqrt(T v);

			static constexpr uint32_t maxU32 = 0xFFFFFFFF;
			static constexpr uint32_t maxU16 = 0xFFFF;
			static constexpr uint32_t maxU8  = 0xFF;
			static constexpr uint32_t minU32 = 0x00000000;
			static constexpr uint32_t minU16 = 0x0000;
			static constexpr uint32_t minU8  = 0x00;
	};
}



template <typename T>
inline T eos::Math::min(
	T a,
	T b) {

	return a < b ? a : b;
}


template <typename T>
inline T eos::Math::max(
	T a,
	T b) {

	return a > b ? a : b;
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
/// \brief    Intervancia dos valors.
/// \param    a: El primer valor.
/// \param    b: El segon valor.
///
template <typename T>
inline void eos::Math::swap(
	T &a,
	T &b) {

	auto x{a};
	a = b;
	b = x;
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
