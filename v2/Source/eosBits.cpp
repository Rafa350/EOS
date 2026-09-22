module;


export module Eos.Bits;


import Eos.Concepts;
import Eos.Types;


namespace eos {

	export class Bits final: private StaticClass<Bits> {
		public:
			template<IsUInt T_>
			static void set(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static void set(T_ &var, T_ mask);

			template<IsUInt T_>
			static void clear(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static void clear(T_ &var, T_ mask);

			template<IsUInt T_>
			static void toggle(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static void toggle(T_ &var, T_ mask);

			template<IsUInt T_>
			static void modify(volatile T_ &var, T_ clearMask, T_ setMask);

			template<IsUInt T_>
			static void modify(T_ &var, T_ clearMask, T_ setMask);

			template<IsUInt T_>
			static bool isSet(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static bool isSet(T_ &var, T_ b);

			template<IsUInt T_>
			static bool isAnySet(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static bool isAnySet(T_ &var, T_ b);

			template<IsUInt T_>
			static bool isClear(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static bool isClear(T_ &var, T_ b);

			template<IsUInt T_>
			static bool isAnyClear(T_ &var, T_ b);
	};
}


/// ----------------------------------------------------------------------
/// \brief    Activa els bits especificats en la mascara.
/// \param    var: La variable.
/// \param    mask: La mascara.
///
template<eos::IsUInt T_>
inline void eos::Bits::set(
	volatile T_ &var,
	T_ mask) {

	var |= mask;
}


/// ----------------------------------------------------------------------
/// \brief    Activa els bits especificats en la mascara.
/// \param    var: La variable.
/// \param    mask: La mascara.
///
template<eos::IsUInt T_>
inline void eos::Bits::set(
	T_ &var,
	T_ mask) {

	var |= mask;
}


template<eos::IsUInt T_>
inline void eos::Bits::clear(
	volatile T_ &var,
	T_ mask) {

	var &= ~mask;
}


template<eos::IsUInt T_>
inline void eos::Bits::clear(
	T_ &var,
	T_ mask) {

	var &= ~mask;
}


template<eos::IsUInt T_>
inline void eos::Bits::toggle(
	volatile T_ &var,
	T_ mask) {

	var ^= mask;
}


template<eos::IsUInt T_>
inline void eos::Bits::toggle(
	T_ &var,
	T_ mask) {

	var ^= mask;
}


template<eos::IsUInt T_>
inline void eos::Bits::modify(
	volatile T_ &var,
	T_ clearMask,
	T_ setMask) {

	T_ v = var;
	v &= ~clearMask;
	v |= setMask;
	var = v;
}


template<eos::IsUInt T_>
inline void eos::Bits::modify(
	T_ &var,
	T_ clearMask,
	T_ setMask) {

	var &= ~clearMask;
	var |= setMask;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isSet(
	volatile T_ &var,
	T_ b) {

	return (var & b) == b;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isSet(
	T_ &var,
	T_ b) {

	return (var & b) == b;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isAnySet(
	volatile T_ &var,
	T_ b) {

	return (var & b) != 0;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isAnySet(
	T_ &var,
	T_ b) {

	return (var & b) != 0;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isClear(
	volatile T_ &var,
	T_ b) {

	return (var & b) == 0;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isClear(
	T_ &var,
	T_ b) {

	return (var & b) == 0;
}


template<eos::IsUInt T_>
inline bool eos::Bits::isAnyClear(
	T_ &var,
	T_ b) {

	return (var & b) != b;
}
