#pragma once


#include "eos.h"


namespace rtos {

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

			uint32_t toTicks() const;

			inline bool isZero() const {
				return _ms == 0;
			}

			inline bool isInfinite() const {
				return _ms == 0xFFFFFFFF;
			}
	};
}
