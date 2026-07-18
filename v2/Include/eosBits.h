#pragma once
#ifndef __eosBits__
#define __eosBits__


#include <type_traits>


namespace eos {

	class Bits {
		public:
			template<typename T_>
			inline static void set(volatile T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var |= mask;
			}

			template<typename T_>
			inline static void set(T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var |= mask;
			}

			template<typename T_>
			inline static void clear(volatile T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var &= ~mask;
			}

			template<typename T_>
			inline static void clear(T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var &= ~mask;
			}

			template<typename T_>
			inline static void toggle(volatile T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var ^= mask;
			}

			template<typename T_>
			inline static void toggle(T_ &var, T_ mask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var ^= mask;
			}

			template<typename T_>
			inline static void modify(volatile T_ &var, T_ clearMask, T_ setMask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				T_ v = var;
				v &= ~clearMask;
				v |= setMask;
				var = v;
			}

			template<typename T_>
			inline static void modify(T_ &var, T_ clearMask, T_ setMask) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				var &= ~clearMask;
				var |= setMask;
			}

			template<typename T_>
			inline static bool isSet(volatile T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) == b;
			}

			template<typename T_>
			inline static bool isSet(T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) == b;
			}

			template<typename T_>
			inline static bool isAnySet(volatile T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) != 0;
			}

			template<typename T_>
			inline static bool isAnySet(T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) != 0;
			}

			template<typename T_>
			inline static bool isClear(volatile T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) == 0;
			}

			template<typename T_>
			inline static bool isClear(T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) == 0;
			}

			template<typename T_>
			inline static bool isAnyClear(T_ &var, T_ b) {
				static_assert(std::is_integral<T_>::value && !std::is_same<T_, bool>::value);
				return (var & b) != b;
			}
	};

} // namespace htl


#endif // __eosBits__
