module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.TMR.Templates;


import Eos.Hardware.TMR.Classes;
import Eos.Hardware.TMR.Identifiers;
import Eos.Hardware.TMR.Pins;
import Eos.Hardware.TMR.Traits;


namespace g = htl::gpio;
namespace i = eos::hardware::tmr::internal;


export namespace eos::hardware::tmr {

	template <TMRDeviceID deviceID_>
	class TMRDeviceX: public TMRDevice {
		private:
			using Traits = internal::TMRTraits<deviceID_>;
			static constexpr uint32_t _timAddr = Traits::timAddr;
			static constexpr uint32_t _activateAddr = Traits::activateAddr;
			static constexpr uint32_t _activatePos = Traits::activatePos;
			static TMRDeviceX _instance;

		public:
			static constexpr TMRDeviceID deviceID = deviceID_;
			static constexpr TMRDeviceX *pInst = &_instance;
			static constexpr TMRDeviceX &rInst = _instance;

		private:
			TMRDeviceX();

		protected:
			void activate() override {
				uint32_t *p = reinterpret_cast<uint32_t*>(_activateAddr);
				*p |= 1 << _activatePos;
				__DSB();
			}
			void deactivate() override {
				uint32_t *p = reinterpret_cast<uint32_t*>(_activateAddr);
				*p &= ~(1 << _activatePos);
			}

		public:
			inline static void interruptHandler() {
				_instance.interruptService();
			}

			template <typename pin_>
			void initPinCH1(g::OutputType type, g::PullUpDown pupd, g::Speed speed);

			template <typename pin_>
			void initPinCH2(g::OutputType type, g::PullUpDown pupd, g::Speed speed);

			template <typename pin_>
			void initPinCH3(g::OutputType type, g::PullUpDown pupd, g::Speed speed);

			template <typename pin_>
			void initPinCH4(g::OutputType type, g::PullUpDown pupd, g::Speed speed);
	};

	template <TMRDeviceID deviceID_>
	TMRDeviceX<deviceID_> TMRDeviceX<deviceID_>::_instance;
}


using namespace eos::hardware;
using namespace eos::hardware::tmr;



template <TMRDeviceID deviceID_>
TMRDeviceX<deviceID_>::TMRDeviceX() :
	TMRDevice(reinterpret_cast<TIM_TypeDef*>(_timAddr)) {
}


template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH1(
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch1, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH2(
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch2, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternatet(type, pupd, speed, af);
}


template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH3(
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch3, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH4(
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch4, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}
