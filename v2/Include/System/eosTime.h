#pragma once
#ifndef __eosTime__
#define __eosTime__


#include "eos.h"


namespace eos {

	/// \brief Clase que encapsula el temps en milisegons
	///
	class Time final {
		private:
			static constexpr uint32_t _factor = 1;

		private:
			uint32_t _value;

		private:
			inline constexpr Time(uint32_t value):
				_value {value} {
			}

		public:
			inline constexpr Time():
				_value{0} {
			}

			inline constexpr Time(const Time &other) :
				_value {other._value} {
			}

			~Time() = default;

			inline static constexpr Time fromMiliseconds(uint32_t miliseconds) {
				return Time(miliseconds * _factor);
			}

			inline static constexpr Time fromSeconds(uint32_t seconds) {
				return Time(seconds * 1000 * _factor);
			}

			inline uint32_t toMiliseconds() const {
				return _value / _factor;
			}

			inline uint32_t toSeconds() const {
				return _value / (1000 * _factor);
			}

			inline bool isZero() const {
				return _value == 0;
			}

			inline bool isInfinite() const {
				return _value == 0xFFFFFFFF;
			}

			/// Operador aritmetic +
			///
			inline Time operator + (Time other) {
				return Time(_value + other._value);
			}

			/// Operador aritmetic -
			///
			inline Time operator - (Time other) {
				return Time(_value - other._value);
			}

			/// Operador d'assignacio =
			///
			inline Time& operator = (Time other) {
				_value = other._value;
				return *this;
			}

			/// Operador d'assignacio +=
			///
			inline Time& operator += (Time other) {
				_value += other._value;
				return *this;
			}

			/// Operador d'assignacio -=
			///
			inline Time& operator -= (Time other) {
				_value -= other._value;
				return *this;
			}

			/// Operador de comparacio ==
			///
			inline friend bool operator == (Time a, Time b) {
				return a._value == b._value;
			}

			/// Operador de comparacio <
			///
			inline friend bool operator < (Time a, Time b) {
				return a._value < b._value;
			}

			/// Operador de comparacio >
			///
			inline friend bool operator > (Time a, Time b) {
				return a._value > b._value;
			}
	};

	/// \brief Constants de temps predefinides
	///
	struct Times {
		static constexpr Time zero = Time::fromMiliseconds(0);
		static constexpr Time infinite = Time::fromMiliseconds(0xFFFFFFFF);
		static constexpr Time second = Time::fromMiliseconds(1 * 1000);
		static constexpr Time minute = Time::fromMiliseconds(60 * 1000);
		static constexpr Time hour = Time::fromMiliseconds(60 * 60 * 1000);
		static constexpr Time day = Time::fromMiliseconds(24 * 60 * 60 * 1000);
	};
}


#endif // __eosTime__
