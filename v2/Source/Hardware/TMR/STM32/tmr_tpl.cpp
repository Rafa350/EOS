module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.TMR.Templates;


import Eos.Types;
import Eos.Hardware.Regs;
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
			using Traits = i::TMRTraits<deviceID_>;
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
			void activate() override;
			void deactivate() override;

		public:
			static void interruptHandler();

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

	Reg32Flag<_activateAddr, _activatePos>::set();
	DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceID_: Identificador del didpositiu.
///
template <TMRDeviceID deviceID_>
void TMRDeviceX<deviceID_>::deactivate() {

	Reg32Flag<_activateAddr, _activatePos>::clear();
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
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch1, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
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
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch2, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternatet(type, pupd, speed, af);
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
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch3, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
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
	g::OutputType type,
	g::PullUpDown pupd,
	g::Speed speed) {

	auto af = i::PinTraits<deviceID_, i::PinUse::ch4, pin_::portID, pin_::pinID>::value;
	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(type, pupd, speed, af);
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interrupcio.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <TMRDeviceID deviceID_>
void TMRDeviceX<deviceID_>::interruptHandler() {

	_instance.interruptService();
}
