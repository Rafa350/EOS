module;


#include "HTL/htlGPIO.h"


export module Eos.Hardware.CAN.__TEMPLATES;


import Eos.Hardware.CAN.__CLASSES;
import Eos.Hardware.CAN.__DEVICE_TRAITS;
import Eos.Hardware.CAN.__PIN_TRAITS;
import Eos.Hardware.CAN.__PLATFORM_TRAITS;


//import Eos.Bits;
import Eos.Types;


export namespace eos::hardware::can {

    template <CANDeviceID deviceId_>
    class CANDeviceX final: public CANDevice {
        private:
            static CANDeviceX _instance;

        private:
            using DeviceTraits = internal::DeviceTraits<deviceId_>;

        public:
            static constexpr auto deviceId = deviceId_;
            static constexpr CANDeviceX *pInst = &_instance;
            static constexpr CANDeviceX &rInst = _instance;

        private:
            CANDeviceX();

        protected:
            void activateImpl() override;
            void deactivateImpl() override;

        public:
            template <typename pin_> void initPinTX();
            template <typename pin_> void initPinRX();

            void initClockSource(ClockSource clockSource);

            static void interruptHandler();
	};

    using CANDevice1 = CANDeviceX<CANDeviceID::can1>;
	using CANDevice2 = CANDeviceX<CANDeviceID::can2>;
}


using namespace eos;
using namespace eos::hardware::can;


/// ---------------------------------------------------------------------------
/// @brief    Camp estatic de la instancia.
/// @tparam   deviceId_: Identificador del disposiu
///
template <CANDeviceID deviceId_>
CANDeviceX<deviceId_> CANDeviceX<deviceId_>::_instance;


/// ---------------------------------------------------------------------------
/// @brief    Crida a __DSB() desde d'ins del modul.
///
void DSB() {

    __DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
CANDeviceX<deviceId_>::CANDeviceX() :
    CANDevice {DeviceTraits::canAddr, DeviceTraits::ramAddr} {
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::activateImpl() {

    constexpr auto activateAddr = DeviceTraits::activateAddr;
    constexpr auto activatePos = DeviceTraits::activatePos;

    Bits::set(*reinterpret_cast<UInt32*>(activateAddr), 1UL << activatePos);
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::deactivateImpl() {

    constexpr auto activateAddr = DeviceTraits::activateAddr;
    constexpr auto activatePos = DeviceTraits::activatePos;

    Bits::clear(*reinterpret_cast<UInt32*>(activateAddr), 1UL << activatePos);
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
template <typename pin_>
void CANDeviceX<deviceId_>::initPinTX() {

    namespace g = htl::gpio;
    namespace i = internal;

    auto value = i::PinTraits<deviceId_, i::PinFunction::tx, pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull,
        g::PullUpDown::none,
        g::Speed::fast,
        value);
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
template <typename pin_>
void CANDeviceX<deviceId_>::initPinRX() {

    namespace g = htl::gpio;
    namespace i = internal;

    auto value = i::PinTraits<deviceId_, i::PinFunction::rx, pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull,
        g::PullUpDown::none,
        g::Speed::fast,
     value);
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
/// @param clockSource
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::initClockSource(ClockSource clockSource) {

    using DeviceTraits = internal::DeviceTraits<deviceId_>;

    auto p = reinterpret_cast<UInt32*>(DeviceTraits::clockSourceAddr);

    *p &= ~DeviceTraits::clockSourceMsk;
    *p |= ((uint32_t)clockSource << DeviceTraits::clockSourcePos) & DeviceTraits::clockSourceMsk;
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::interruptHandler() {

    _instance.interruptService();
}
