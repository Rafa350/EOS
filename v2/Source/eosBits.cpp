module;

#include <type_traits>


export module Eos.Bits;


export namespace eos {

	class Bits {
		public:
			template<typename T_>
			static void set(volatile T_ &var, T_ mask);

			template<typename T_>
			static void set(T_ &var, T_ mask);

			template<typename T_>
			static void clear(volatile T_ &var, T_ mask);

			template<typename T_>
			static void clear(T_ &var, T_ mask);

			template<typename T_>
			static void toggle(volatile T_ &var, T_ mask);

			template<typename T_>
			static void toggle(T_ &var, T_ mask);

			template<typename T_>
			static void modify(volatile T_ &var, T_ clearMask, T_ setMask);

			template<typename T_>
			static void modify(T_ &var, T_ clearMask, T_ setMask);

			template<typename T_>
			static bool isSet(volatile T_ &var, T_ b);

			template<typename T_>
			static bool isSet(T_ &var, T_ b);

			template<typename T_>
			static bool isAnySet(volatile T_ &var, T_ b);

			template<typename T_>
			static bool isAnySet(T_ &var, T_ b);

			template<typename T_>
			static bool isClear(volatile T_ &var, T_ b);

			template<typename T_>
			static bool isClear(T_ &var, T_ b);

			template<typename T_>
			static bool isAnyClear(T_ &var, T_ b);
	};
}


template<typename T_>
inline void eos::Bits::set(
	volatile T_ &var,
	T_ mask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var |= mask;
}


template<typename T_>
inline void eos::Bits::set(
	T_ &var,
	T_ mask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var |= mask;
}


template<typename T_>
inline void eos::Bits::clear(volatile T_ &var, T_ mask) {
	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
	var &= ~mask;
}


template<typename T_>
inline void eos::Bits::clear(
	T_ &var,
	T_ mask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var &= ~mask;
}


template<typename T_>
inline void eos::Bits::toggle(
	volatile T_ &var,
	T_ mask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var ^= mask;
}


template<typename T_>
inline void eos::Bits::toggle(
	T_ &var,
	T_ mask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var ^= mask;
}


template<typename T_>
inline void eos::Bits::modify(
	volatile T_ &var,
	T_ clearMask,
	T_ setMask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	T_ v = var;
	v &= ~clearMask;
	v |= setMask;
	var = v;
}


template<typename T_>
inline void eos::Bits::modify(
	T_ &var,
	T_ clearMask,
	T_ setMask) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	var &= ~clearMask;
	var |= setMask;
}


template<typename T_>
inline bool eos::Bits::isSet(
	volatile T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) == b;
}


template<typename T_>
inline bool eos::Bits::isSet(
	T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) == b;
}


template<typename T_>
inline bool eos::Bits::isAnySet(
	volatile T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) != 0;
}


template<typename T_>
inline bool eos::Bits::isAnySet(
	T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) != 0;
}


template<typename T_>
inline bool eos::Bits::isClear(
	volatile T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) == 0;
}


template<typename T_>
inline bool eos::Bits::isClear(
	T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) == 0;
}


template<typename T_>
inline bool eos::Bits::isAnyClear(
	T_ &var,
	T_ b) {

	static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);

	return (var & b) != b;
}
