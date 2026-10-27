export module Eos.Bits;

import Eos.Concepts;
import Eos.Types;


export namespace eos {

	class Bits final: private StaticClass<Bits> {
		public:
			template<IsUInt T_>
			static inline void set(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void set(T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void clear(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void clear(T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void toggle(volatile T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void toggle(T_ &var, T_ mask);

			template<IsUInt T_>
			static inline void modify(volatile T_ &var, T_ clearMask, T_ setMask);

			template<IsUInt T_>
			static inline void modify(T_ &var, T_ clearMask, T_ setMask);

			template<IsUInt T_>
			static inline bool isSet(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isSet(T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isAnySet(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isAnySet(T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isClear(volatile T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isClear(T_ &var, T_ b);

			template<IsUInt T_>
			static inline bool isAnyClear(T_ &var, T_ b);
	};
}


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Activa els bits especificats en la mascara.
/// \param    var: La variable.
/// \param    mask: La mascara.
///
template<IsUInt T_>
void Bits::set(
	volatile T_ &var,
	T_ mask) {

	var |= mask;
}


/// ----------------------------------------------------------------------
/// \brief    Activa els bits especificats en la mascara.
/// \param    var: La variable.
/// \param    mask: La mascara.
///
template<IsUInt T_>
void Bits::set(
	T_ &var,
	T_ mask) {

	var |= mask;
}


template<IsUInt T_>
void Bits::clear(
	volatile T_ &var,
	T_ mask) {

	var &= ~mask;
}


template<IsUInt T_>
void Bits::clear(
	T_ &var,
	T_ mask) {

	var &= ~mask;
}


template<IsUInt T_>
void Bits::toggle(
	volatile T_ &var,
	T_ mask) {

	var ^= mask;
}


template<IsUInt T_>
void Bits::toggle(
	T_ &var,
	T_ mask) {

	var ^= mask;
}


template<IsUInt T_>
void Bits::modify(
	volatile T_ &var,
	T_ clearMask,
	T_ setMask) {

	T_ v = var;
	v &= ~clearMask;
	v |= setMask;
	var = v;
}


template<IsUInt T_>
void Bits::modify(
	T_ &var,
	T_ clearMask,
	T_ setMask) {

	var &= ~clearMask;
	var |= setMask;
}


template<IsUInt T_>
bool Bits::isSet(
	volatile T_ &var,
	T_ b) {

	return (var & b) == b;
}


template<IsUInt T_>
bool Bits::isSet(
	T_ &var,
	T_ b) {

	return (var & b) == b;
}


template<IsUInt T_>
bool Bits::isAnySet(
	volatile T_ &var,
	T_ b) {

	return (var & b) != 0;
}


template<IsUInt T_>
bool Bits::isAnySet(
	T_ &var,
	T_ b) {

	return (var & b) != 0;
}


template<IsUInt T_>
bool Bits::isClear(
	volatile T_ &var,
	T_ b) {

	return (var & b) == 0;
}


template<IsUInt T_>
bool Bits::isClear(
	T_ &var,
	T_ b) {

	return (var & b) == 0;
}


template<IsUInt T_>
bool Bits::isAnyClear(
	T_ &var,
	T_ b) {

	return (var & b) != b;
}
