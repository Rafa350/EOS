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
			Time _delayEndTime;
			Time _pulseEndTime;

		private:
			static bool hasExpired(Time time, Time endTime);

		public:
			Output(PinDriver *drv, unsigned tag);

			bool getValue() const;
			void set();
			void clear();
			void toggle();
			void pulse(Time time, Time pulse);
			void delayedSet(Time time, Time delay);
			void delayedClear(Time time, Time delay);
			void delayedToggle(Time time, Time delay);
			void delayedPulse(Time time, Time delay, Time pulse);
			void write(bool value);
			void tick(Time time);
	};

}


#endif // __eos_digoputput_outputs__
