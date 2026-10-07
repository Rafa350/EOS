module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.UART.__TEMPLATES;


import Eos.Hardware.Clock;
import Eos.Hardware.Regs;
import Eos.Hardware.UART.__CLASSES;
import Eos.Hardware.UART.__DEVICE_TRAITS;
import Eos.Hardware.UART.__PLATFORM_TRAITS;
import Eos.Hardware.UART.__PIN_TRAITS;


namespace eos::hardware::uart {

	using UARTDeviceID = PlatformTraits::DeviceID;

	export template <UARTDeviceID deviceID_>
	class UARTDeviceX final: public UARTDevice {
		private:
			using Traits = internal::UARTTraits<deviceID_>;
			using ActivateFlag = Reg32Flag<Traits::activateAddr, Traits::activatePos>;

		private:
			static constexpr auto _usartAddr = Traits::usartAddr;
			static UARTDeviceX _instance;

		public:
			static constexpr auto deviceID = deviceID_;
			static constexpr UARTDeviceX *pInst = &_instance;
			static constexpr UARTDeviceX &rInst = _instance;

		private:
			UARTDeviceX();

		protected:
			void activateImpl() const override;
#if HTL_UART_OPTION_DEACTIVATE == 1
			void deactivateImpl() const override:
#endif
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			void setClockSourceImpl(ClockSource source) const override;
#endif
			eos::hardware::clock::Clock::ClockID getUARTClock() const override;

#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
			constexpr bool isFIFOAvailable() const override;
			bool isFIFOEnabled() const;
#endif
			bool isRTOAvailable() const override;

		public:
			static void interruptHandler();

			template <typename pin_> void initPinTX();
			template <typename pin_> void initPinRX();
			template <typename pin_> void initPinCTS();
			template <typename pin_> void initPinRTS();
	};

	template <UARTDeviceID deviceID_>
	UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_instance;
}


using namespace eos;
using namespace eos::hardware::uart;


/// ---------------------------------------------------------------------------
/// @brief    Crida a DSB desde aquest modul C++20
///
void DSB() {

	__DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @tparam   deviceID_ : Identicador del dispositiu.
///
template <UARTDeviceID deviceID_>
UARTDeviceX<deviceID_>::UARTDeviceX() :
	UARTDevice {_usartAddr} {

}


/// ---------------------------------------------------------------------------
/// @brief     Activa el dispositiu fisic.
/// @tparam    deviceID_: Identificador del dispositiu.
///
template<UARTDeviceID deviceID_>
void UARTDeviceX<deviceID_>::activateImpl() const {

	ActivateFlag::set();
	DSB();
}


#if HTL_UART_OPTION_DEACTIVATE == 1
/// ---------------------------------------------------------------------------
/// @brief     Desctiva el dispositiu fisic.
/// @tparam    deviceID_: Identificador del dispositiu.
///
template<UARTDeviceID deviceID_>
void UARTDeviceX<deviceID_>::deactivateImpl() const {

	ActivateFlag::clear();
	DSB();
}
#endif


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin TX.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceID_>
template <typename pin_>
void UARTDeviceX<deviceID_>::initPinTX() {

	namespace g = htl::gpio;
	namespace i = internal;

	auto value = i::PinTraits<deviceID_, i::PinFunction::tx, pin_::portID, pin_::pinID>::value;

	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		g::OutputType::pushPull,
		g::PullUpDown::none,
		g::Speed::fast,
	    value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin RX.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceID_>
template <typename pin_>
void UARTDeviceX<deviceID_>::initPinRX() {

	namespace g = htl::gpio;
	namespace i = internal;

	auto value = i::PinTraits<deviceID_, i::PinFunction::rx, pin_::portID, pin_::pinID>::value;

	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		g::OutputType::pushPull,
		g::PullUpDown::none,
		g::Speed::fast,
	    value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin CTS.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceID_>
template <typename pin_>
void UARTDeviceX<deviceID_>::initPinCTS() {

	namespace g = htl::gpio;
	namespace i = internal;

	auto value = i::PinTraits<deviceID_, i::PinFunction::cts, pin_::portID, pin_::pinID>::value;

	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		g::OutputType::pushPull,
		g::PullUpDown::none,
		g::Speed::fast,
		value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin RTS.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceID_>
template <typename pin_>
void UARTDeviceX<deviceID_>::initPinRTS() {

	namespace g = htl::gpio;
	namespace i = internal;

	auto value = i::PinTraits<deviceID_, i::PinFunction::rts, pin_::portID, pin_::pinID>::value;

	g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		g::OutputType::pushPull,
		g::PullUpDown::none,
		g::Speed::fast,
	    value);
}


/// ---------------------------------------------------------------------------
/// @brief    Handler de la interrupcio.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template<UARTDeviceID deviceID_>
void UARTDeviceX<deviceID_>::interruptHandler() {

	_instance.interruptService();
}


#if defined(EOS_PLATFORM_STM32F0)
template<DeviceID deviceID_>
clock::ClockID UARTDeviceX<deviceID_>::getUARTClock() const {

    auto addr = reinterpret_cast<uint32_t*>(Traits::clockSourceAddr);
    auto msk = Traits::clockSourceMsk;
    auto pos = Traits::clockSourcePos;

    switch ((*addr & msk) >> pos) {
        case RCC_CFGR3_USART1SW_PCLK:
            return clock::ClockID::pclk;

        case RCC_CFGR3_USART1SW_SYSCLK:
            return clock::ClockID::sysclk;

        case RCC_CFGR3_USART1SW_LSE:
            return clock::ClockID::lse;

        case RCC_CFGR3_USART1SW_HSI:
            return clock::ClockID::hsi;
    }
}

template<>
inline clock::ClockID UARTDeviceX<DeviceID::uart2>::getUARTClock() const {

    return clock::ClockID::pclk;

}

#elif defined(EOS_PLATFORM_STM32F4)

namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID htl::uart::UARTDeviceX<deviceID_>::getUARTClock() const {

		return Traits::pclkX;
	}
}

#elif defined(EOS_PLATFORM_STM32F7)

namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID htl::uart::UARTDeviceX<deviceID_>::getUARTClock() const {

		auto addr = reinterpret_cast<uint32_t*>(Traits::clockSourceAddr);
		auto msk = Traits::clockSourceMsk;
		auto pos = Traits::clockSourcePos;

		auto pclkX = Traits::pclkX;

		switch ((*addr & msk) >> pos) {
			default:
			case 0:
				return pclkX;

			case 1:
				return clock::ClockID::sysclk;

			case 2:
				return clock::ClockID::hsi;

			case 3:
				return clock::ClockID::lse;
		}
	}

}

#elif defined(EOS_PLATFORM_STM32G0)

template<UARTDeviceID deviceID_>
eos::hardware::clock::Clock::ClockID UARTDeviceX<deviceID_>::getUARTClock() const {

	auto addr = reinterpret_cast<uint32_t*>(Traits::clockSourceAddr);
	auto msk = Traits::clockSourceMsk;
	auto pos = Traits::clockSourcePos;

	switch ((*addr & msk) >> pos) {
		default:
		case 0:
			return eos::hardware::clock::Clock::ClockID::pclk;

		case 1:
			return eos::hardware::clock::Clock::ClockID::sysclk;

		case 2:
			return eos::hardware::clock::Clock::ClockID::hsi16;

		case 3:
			return eos::hardware::clock::Clock::ClockID::lse;
	}
}
#endif


#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
template<UARTDeviceID deviceID_>
void UARTDeviceX<deviceID_>::setClockSourceImpl(
	ClockSource source) const {

	constexpr auto clockSourceAddr = Traits::clockSourceAddr;
	constexpr auto clockSourceMsk = Traits::clockSourceMsk;
	constexpr auto clockSourcePos = Traits::clockSourcePos;

	//Reg32Field<clockSourceAddr, clockSourceMsk, clockSourcePos>::write(source);

	auto reg = reinterpret_cast<volatile uint32_t*>(clockSourceAddr);
	Bits::clear(*reg, clockSourceMsk);
	Bits::set(*reg, ((uint32_t) source << clockSourcePos) & clockSourceMsk);
}
#endif


template<UARTDeviceID deviceID_>
bool UARTDeviceX<deviceID_>::isRTOAvailable() const {

	return Traits::isRTOAvailable;
}
