#pragma once
#ifndef __HTL_htlFlags__
#define __HTL_htlFlags__


#include "HTL/htl.h"


#include <type_traits>


namespace htl::flags {

	template <typename TEnum_>
	class Flags {

		static_assert(std::is_enum<TEnum_>::value);

		private:
			using Type = std::underlying_type<TEnum_>::type;

		private:
			Type _value;

		public:
			constexpr Flags();
			constexpr Flags & operator |= (const Flags &other);
			constexpr Flags & operator += (Type value);
			constexpr Flags & operator &= (const Flags &other);
			constexpr Flags & operator -= (Type value);
	};

	template <typename TEnum_>
	constexpr Flags<TEnum_>::Flags():
		_value {} {
	}

	template <typename TEnum_>
	constexpr Flags<TEnum_>& Flags<TEnum_>::operator |= (const Flags<TEnum_> &other) {
		_value |= (Type)other._value;
		return *this;
	}

	template <typename TEnum_>
	constexpr Flags<TEnum_>& Flags<TEnum_>::operator += (Flags<TEnum_>::Type value) {
		_value |= (1 << value);
		return *this;
	}

	template <typename TEnum_>
	constexpr Flags<TEnum_>& Flags<TEnum_>::operator &= (const Flags<TEnum_> &other) {
		_value &= (Type)other._value;
		return *this;
	}

	template <typename TEnum_>
	constexpr Flags<TEnum_>& Flags<TEnum_>::operator -= (const Flags<TEnum_>::Type value) {
		_value &= ~(1 << value);
		return *this;
	}
}


#endif // __HTL_htlFlags__
