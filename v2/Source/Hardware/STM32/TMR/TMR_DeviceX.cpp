module;

#include "hardware.h"


export module Eos.Hardware.TMR._DeviceX;

import Eos.Types;
import Eos.Hardware.GPIO;
import Eos.Hardware.Regs;
import Eos.Hardware.TMR._Device;
import Eos.Hardware.TMR._DeviceTraits;
import Eos.Hardware.TMR._PinTraits;
import Eos.Hardware.TMR._Types;


using namespace eos::hardware::gpio;


export namespace eos::hardware::tmr {

	template <TMRDeviceID deviceID_>
	class TMRDeviceX: public TMRDevice {
		private:
			using TMRTraits = internal::TMRTraits<deviceID_>;
			using ActivateFlag = Reg32Flag<TMRTraits::activateAddr, TMRTraits::activatePos>;

			static constexpr UInt32 _timAddr = TMRTraits::timAddr;
			static TMRDeviceX _instance;

		public:
			static constexpr TMRDeviceID deviceID = deviceID_;
			static constexpr TMRDeviceX *pInst = &_instance;
			static constexpr TMRDeviceX &rInst = _instance;
            static constexpr auto interruptVectorId = TMRTraits::interruptVectorId;

		private:
			TMRDeviceX();

		protected:
			void activate() override;
			void deactivate() override;

		public:
			static void interruptHandler();

			template <typename pin_>
			void initPinCH1(OutputType type, PullUpDown pupd, Speed speed);

			template <typename pin_>
			void initPinCH2(OutputType type, PullUpDown pupd, Speed speed);

			template <typename pin_>
			void initPinCH3(OutputType type, PullUpDown pupd, Speed speed);

			template <typename pin_>
			void initPinCH4(OutputType type, PullUpDown pupd, Speed speed);
	};

#ifdef TIM1_BASE
    using TMRDevice1 = TMRDeviceX<TMRDeviceID::tmr1>;
#endif
#ifdef TIM2_BASE
    using TMRDevice2 = TMRDeviceX<TMRDeviceID::tmr2>;
#endif
#ifdef TIM3_BASE
    using TMRDevice3 = TMRDeviceX<TMRDeviceID::tmr3>;
#endif
#ifdef TIM4_BASE
    using TMRDevice4 = TMRDeviceX<TMRDeviceID::tmr4>;
#endif
#ifdef TIM5_BASE
    using TMRDevice5 = TMRDeviceX<TMRDeviceID::tmr5>;
#endif
#ifdef TIM6_BASE
    using TMRDevice6 = TMRDeviceX<TMRDeviceID::tmr6>;
#endif
#ifdef TIM7_BASE
    using TMRDevice7 = TMRDeviceX<TMRDeviceID::tmr7>;
#endif
#ifdef TIM8_BASE
    using TMRDevice8 = TMRDeviceX<TMRDeviceID::tmr8>;
#endif
#ifdef TIM9_BASE
    using TMRDevice9 = TMRDeviceX<TMRDeviceID::tmr9>;
#endif
#ifdef TIM10_BASE
    using TMRDevice10 = TMRDeviceX<TMRDeviceID::tmr10>;
#endif
#ifdef TIM11_BASE
    using TMRDevice11 = TMRDeviceX<TMRDeviceID::tmr11>;
#endif
#ifdef TIM12_BASE
    using TMRDevice12 = TMRDeviceX<TMRDeviceID::tmr12>;
#endif
#ifdef TIM13_BASE
    using TMRDevice13 = TMRDeviceX<TMRDeviceID::tmr13>;
#endif
#ifdef TIM14_BASE
    using TMRDevice14 = TMRDeviceX<TMRDeviceID::tmr14>;
#endif
#ifdef TIM15_BASE
    using TMRDevice15 = TMRDeviceX<TMRDeviceID::tmr15>;
#endif
#ifdef TIM16_BASE
    using TMRDevice16 = TMRDeviceX<TMRDeviceID::tmr16>;
#endif
#ifdef TIM17_BASE
    using TMRDevice17 = TMRDeviceX<TMRDeviceID::tmr17>;
#endif
}


using namespace eos::hardware;
using namespace eos::hardware::gpio;
using namespace eos::hardware::tmr;


template <TMRDeviceID deviceID_>
TMRDeviceX<deviceID_> TMRDeviceX<deviceID_>::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Crida a DSB desde aquest modul C++20
///
void DSB() {

	__DSB();
}


/// ---------------------------------------------------------------------------
/// @brief     Constructor.
/// @tparam    deviceID_: Identificador del dispoaitiu.
///
template <TMRDeviceID deviceID_>
TMRDeviceX<deviceID_>::TMRDeviceX() :
	TMRDevice(reinterpret_cast<TIM_TypeDef*>(_timAddr)) {
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceID_: Identificador del disposiotiu.
///
template <TMRDeviceID deviceID_>
void TMRDeviceX<deviceID_>::activate() {

	ActivateFlag::set();
	DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceID_: Identificador del didpositiu.
///
template <TMRDeviceID deviceID_>
void TMRDeviceX<deviceID_>::deactivate() {

	ActivateFlag::clear();
	DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin CH1
/// @tparam   deviceID_: Idenfificador del dispositiu.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull up/down
/// @param    speed: Velocitat del pin.
///
template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH1(
	gpio::OutputType type,
	gpio::PullUpDown pupd,
	gpio::Speed speed) {

	namespace i = internal;

	auto af = i::PinTraits<deviceID_, i::PinFunction::ch1, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin CH2
/// @tparam   deviceID_: Idenfificador del dispositiu.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull up/down
/// @param    speed: Velocitat del pin.
///
template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH2(
	gpio::OutputType type,
	gpio::PullUpDown pupd,
	gpio::Speed speed) {

	namespace i = internal;

	auto af = i::PinTraits<deviceID_, i::PinFunction::ch2, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternatet(type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin CH3
/// @tparam   deviceID_: Idenfificador del dispositiu.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull up/down
/// @param    speed: Velocitat del pin.
///
template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH3(
	gpio::OutputType type,
	gpio::PullUpDown pupd,
	gpio::Speed speed) {

	namespace i = internal;

	auto af = i::PinTraits<deviceID_, i::PinFunction::ch3, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin CH4
/// @tparam   deviceID_: Idenfificador del dispositiu.
/// @param    type: Tipus de sortida.
/// @param    pupd: Resistencies pull up/down
/// @param    speed: Velocitat del pin.
///
template <TMRDeviceID deviceID_>
template <typename pin_>
void TMRDeviceX<deviceID_>::initPinCH4(
	gpio::OutputType type,
	gpio::PullUpDown pupd,
	gpio::Speed speed) {

	namespace i = internal;

	auto af = i::PinTraits<deviceID_, i::PinFunction::ch4, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interrupcio.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <TMRDeviceID deviceID_>
void TMRDeviceX<deviceID_>::interruptHandler() {

	_instance.interruptService();
}
