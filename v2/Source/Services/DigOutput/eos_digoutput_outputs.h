#pragma once
#ifndef __eos_digoutput_outputs__
#define __eos_digoutput_outputs__


// EOS includes
//
#include "eos.h"
#include "Services/DigOutput/eosDigOutputService.h"


namespace eos {

	class PinDriver;

	class Output final: public DigOutput {
		public:
			enum class State {
				idle,
				pulse,
				delayedSet,
				delayedClear,
				delayedToggle,
				delayedPulse,
			};

		private:
			PinDriver * const _drv;
			bool _value;
			State _state;
			unsigned _delayEndTime;
			unsigned _pulseEndTime;

		private:
			static bool hasExpired(unsigned time, unsigned endTime);

		public:
			Output(PinDriver *drv, unsigned tag);

			bool getValue() const;
			void set();
			void clear();
			void toggle();
			void pulse(unsigned time, unsigned pulse);
			void delayedSet(unsigned time, unsigned delay);
			void delayedClear(unsigned time, unsigned delay);
			void delayedToggle(unsigned time, unsigned delay);
			void delayedPulse(unsigned time, unsigned delay, unsigned pulse);
			void write(bool value);
			void tick(unsigned time);
	};

}


#endif // __eos_digoputput_outputs__
