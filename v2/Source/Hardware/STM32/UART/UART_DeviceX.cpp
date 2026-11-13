module;

#include "hardware.h"


export module Eos.Hardware.UART._DeviceX;

import Eos.Bits;
import Eos.Hardware.Clock;
import Eos.Hardware.GPIO;
import Eos.Hardware.Regs;
import Eos.Hardware.UART._Device;
import Eos.Hardware.UART._DeviceTraits;
import Eos.Hardware.UART._PlatformTraits;
import Eos.Hardware.UART._PinTraits;
import Eos.Hardware.UART._Types;


using namespace eos::hardware::clock;


export namespace eos::hardware::uart {

	template <UARTDeviceID deviceId_>
	class UARTDeviceX final: public UARTDevice {
		private:
			using UARTTraits = internal::UARTTraits<deviceId_>;
			using ActivateFlag = Reg32Flag<UARTTraits::activateAddr, UARTTraits::activatePos>;

		private:
			static UARTDeviceX _instance;

		public:
			static constexpr auto deviceId = deviceId_;
			static constexpr auto interruptVectorId = UARTTraits::interruptVector;
			static constexpr UARTDeviceX *pInst = &_instance;
			static constexpr UARTDeviceX &rInst = _instance;

		private:
			UARTDeviceX();

		protected:
			void activateImpl() const override;
			void deactivateImpl() const override;
#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			void setClockSourceImpl(ClockSource source) const override;
#endif
			Clock::ClockID getUARTClock() const override;

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

#ifdef USART1_BASE
	using UARTDevice1 = UARTDeviceX<UARTDeviceID::uart1>;
#endif
#ifdef USART2_BASE
	using UARTDevice2 = UARTDeviceX<UARTDeviceID::uart2>;
#endif
#ifdef USART3_BASE
	using UARTDevice3 = UARTDeviceX<UARTDeviceID::uart3>;
#endif
#if defined(USART4_BASE) || defined(UART4_BASE)
	using UARTDevice4 = UARTDeviceX<UARTDeviceID::uart4>;
#endif
#if defined(USART5_BASE) || defined(UART5_BASE)
	using UARTDevice5 = UARTDeviceX<UARTDeviceID::uart5>;
#endif
#ifdef USART6_BASE
	using UARTDevice6 = UARTDeviceX<UARTDeviceID::uart6>;
#endif
#if defined(USART7_BASE) || defined(UART8_BASE)
	using UARTDevice7 = UARTDeviceX<UARTDeviceID::uart7>;
#endif
#if defined(USART8_BASE) || defined(UART8_BASE)
	using UARTDevice8 = UARTDeviceX<UARTDeviceID::uart8>;
#endif
}


using namespace eos;
using namespace eos::hardware::clock;
using namespace eos::hardware::gpio;
using namespace eos::hardware::uart;


template <UARTDeviceID deviceId_>
UARTDeviceX<deviceId_> UARTDeviceX<deviceId_>::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Crida a DSB desde aquest modul C++20
///
void DSB() {

	__DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor
/// @tparam   deviceId_ : Identicador del dispositiu.
///
template <UARTDeviceID deviceId_>
UARTDeviceX<deviceId_>::UARTDeviceX() :
	UARTDevice {UARTTraits::usartAddr} {

}


/// ---------------------------------------------------------------------------
/// @brief     Activa el dispositiu fisic.
/// @tparam    deviceId_: Identificador del dispositiu.
///
template<UARTDeviceID deviceId_>
void UARTDeviceX<deviceId_>::activateImpl() const {

	ActivateFlag::set();
	DSB();
}


/// ---------------------------------------------------------------------------
/// @brief     Desctiva el dispositiu fisic.
/// @tparam    deviceId_: Identificador del dispositiu.
///
template<UARTDeviceID deviceId_>
void UARTDeviceX<deviceId_>::deactivateImpl() const {

	ActivateFlag::clear();
	DSB();
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin TX.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceId_>
template <typename pin_>
void UARTDeviceX<deviceId_>::initPinTX() {

	namespace i = internal;

	auto value = i::PinTraits<deviceId_, i::PinFunction::tx, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		gpio::OutputType::pushPull,
		gpio::PullUpDown::none,
		gpio::Speed::fast,
	    value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin RX.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceId_>
template <typename pin_>
void UARTDeviceX<deviceId_>::initPinRX() {

	namespace i = internal;

	auto value = i::PinTraits<deviceId_, i::PinFunction::rx, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		gpio::OutputType::pushPull,
		gpio::PullUpDown::none,
		gpio::Speed::fast,
	    value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin CTS.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceId_>
template <typename pin_>
void UARTDeviceX<deviceId_>::initPinCTS() {

	namespace i = internal;

	auto value = i::PinTraits<deviceId_, i::PinFunction::cts, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		gpio::OutputType::pushPull,
		gpio::PullUpDown::none,
		gpio::Speed::fast,
		value);
}


/// --------------------------------------------------------------------------------
/// @brief    Configura el pin RTS.
/// @tparam   pin_: El pin.
///
template<UARTDeviceID deviceId_>
template <typename pin_>
void UARTDeviceX<deviceId_>::initPinRTS() {

	namespace i = internal;

	auto value = i::PinTraits<deviceId_, i::PinFunction::rts, pin_::portID, pin_::pinID>::value;

	gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
		gpio::OutputType::pushPull,
		gpio::PullUpDown::none,
		gpio::Speed::fast,
	    value);
}


/// ---------------------------------------------------------------------------
/// @brief    Handler de la interrupcio.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template<UARTDeviceID deviceId_>
void UARTDeviceX<deviceId_>::interruptHandler() {

	_instance.interruptService();
}


#if defined(EOS_PLATFORM_STM32F0)
template<DeviceID deviceId_>
clock::ClockID UARTDeviceX<deviceId_>::getUARTClock() const {

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

template<UARTDeviceID deviceId_>
Clock::ClockID UARTDeviceX<deviceId_>::getUARTClock() const {

	return UARTTraits::pclkX;
}

#elif defined(EOS_PLATFORM_STM32F7)

namespace htl::uart {

	template<UARTDeviceID deviceId_>
	clock::ClockID htl::uart::UARTDeviceX<deviceId_>::getUARTClock() const {

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

template<UARTDeviceID deviceId_>
Clock::ClockID UARTDeviceX<deviceId_>::getUARTClock() const {

	auto addr = reinterpret_cast<uint32_t*>(UARTTraits::clockSourceAddr);
	auto msk = UARTTraits::clockSourceMsk;
	auto pos = UARTTraits::clockSourcePos;

	switch ((*addr & msk) >> pos) {
		default:
		case 0:
			return Clock::ClockID::pclk;

		case 1:
			return Clock::ClockID::sysclk;

		case 2:
			return Clock::ClockID::hsi16;

		case 3:
			return Clock::ClockID::lse;
	}
}
#endif


#if defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
template<UARTDeviceID deviceId_>
void UARTDeviceX<deviceId_>::setClockSourceImpl(
	ClockSource source) const {

	constexpr auto clockSourceAddr = UARTTraits::clockSourceAddr;
	constexpr auto clockSourceMsk = UARTTraits::clockSourceMsk;
	constexpr auto clockSourcePos = UARTTraits::clockSourcePos;

	//Reg32Field<clockSourceAddr, clockSourceMsk, clockSourcePos>::write(source);

	auto reg = reinterpret_cast<volatile uint32_t*>(clockSourceAddr);
	Bits::clear(*reg, clockSourceMsk);
	Bits::set(*reg, ((uint32_t) source << clockSourcePos) & clockSourceMsk);
}
#endif


template<UARTDeviceID deviceId_>
bool UARTDeviceX<deviceId_>::isRTOAvailable() const {

	return UARTTraits::isRTOAvailable;
}
