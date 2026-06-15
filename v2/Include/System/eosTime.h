#pragma once
#ifndef __eosTime__
#define __eosTime__


#include "eos.h"


namespace eos {

	/// \brief Clase per valors de temps en milisegons
	//
	class Time final {
		private:
			uint32_t const _ms;

		private:
			inline Time(uint32_t miliseconds):
				_ms {miliseconds} {
			}

		public:
			inline static Time zero() {
				return Time(0);
			}

			inline static Time infinite() {
				return Time(0xFFFFFFFF);
			}

			inline static Time fromMiliseconds(uint32_t miliseconds) {
				return Time(miliseconds);
			}

			inline static Time fromSeconds(uint32_t seconds) {
				return Time(seconds * 1000);
			}

			inline uint32_t toMiliseconds() const {
				return _ms;
			}

			inline uint32_t toSeconds() const {
				return _ms / 1000;
			}

			inline bool isZero() const {
				return _ms == 0;
			}

			inline bool isInfinite() const {
				return _ms == 0xFFFFFFFF;
			}
	};
}


#endif // __eosTime__
