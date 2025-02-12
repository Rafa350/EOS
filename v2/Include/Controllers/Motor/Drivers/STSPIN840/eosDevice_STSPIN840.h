#pragma once
#ifndef __eosDevice_STSPIN840__
#define __eosDevice_STSPIN840__


#include "eos.h"
#include "htl/htlGPIO.h"
#include "htl/htlTMR.h"


namespace eos {

	class STSPIN840_Device {
		public:
			using Pin = htl::gpio::PinDevice;
			using TmrDev = htl::tmr::TMRDevice;
			using TmrChannel = htl::tmr::Channel;
			enum class Direction {
				forward,
				backward
			};

		private:
			static constexpr unsigned _prescaler = 1;
			unsigned _reload;
			TmrDev * const _tmr;
			TmrChannel _channel;
			Pin * const _pinSTBY;
			Pin * const _pinPH;
			Pin * const _pinEF;

		public:
			STSPIN840_Device(TmrDev *tmr, TmrChannel channel, Pin *pinSTBY, Pin *pinPH, Pin *pinEF);

			void initialize(unsigned frequency);
			void deinitialize();

			void enable();
			void disable();

			void setDirection(Direction dir);
			void pwmStart(unsigned duty);
			void pwmStop();
	};

}


#endif // __eosDevice_STSPIN840__
