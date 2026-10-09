module;


#include "HTL/htlGPIO.h"


export module Eos.Hardware.FDCAN.__TEMPLATES;


import Eos.Hardware.FDCAN.__CLASSES;
import Eos.Hardware.FDCAN.__DEVICE_TRAITS;
import Eos.Hardware.FDCAN.__PIN_TRAITS;
import Eos.Hardware.FDCAN.__PLATFORM_TRAITS;


//import Eos.Bits;
import Eos.Types;


export namespace eos::hardware::fdcan {

    template <CANDeviceID deviceId_>
    class CANDeviceX final: public CANDevice {
        private:
            static CANDeviceX _instance;

        private:
            using CANTraits = internal::CANTraits<deviceId_>;
			template <htl::gpio::PortID portID_, htl::gpio::PinID pinID_>
                using TxPinTraits = internal::PinTraits<deviceId_, internal::PinFunction::tx, portID_, pinID_>;
			template <htl::gpio::PortID portID_, htl::gpio::PinID pinID_>
                using RxPinTraits = internal::PinTraits<deviceId_, internal::PinFunction::rx, portID_, pinID_>;

        public:
            static constexpr auto deviceId = deviceId_;
            static constexpr CANDeviceX *pInst = &_instance;
            static constexpr CANDeviceX &rInst = _instance;
            static constexpr auto interruptVectorId_IT0 = CANTraits::interruptVectorId_IT0;
            static constexpr auto interruptVectorId_IT1 = CANTraits::interruptVectorId_IT1;

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
using namespace eos::hardware::fdcan;


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
    CANDevice {CANTraits::canAddr, CANTraits::ramAddr} {
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::activateImpl() {

    constexpr auto activateAddr = CANTraits::activateAddr;
    constexpr auto activatePos = CANTraits::activatePos;

    Bits::set(*reinterpret_cast<UInt32*>(activateAddr), 1UL << activatePos);
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Descativa el dispositiu.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::deactivateImpl() {

    constexpr auto activateAddr = CANTraits::activateAddr;
    constexpr auto activatePos = CANTraits::activatePos;

    Bits::clear(*reinterpret_cast<UInt32*>(activateAddr), 1UL << activatePos);
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin TX.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
template <typename pin_>
void CANDeviceX<deviceId_>::initPinTX() {

    namespace g = htl::gpio;

    auto value = TxPinTraits<pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull,
        g::PullUpDown::none,
        g::Speed::fast,
        value);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin RX.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
template <typename pin_>
void CANDeviceX<deviceId_>::initPinRX() {

    namespace g = htl::gpio;

    auto value = RxPinTraits<pin_::portID, pin_::pinID>::value;

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

    auto p = reinterpret_cast<UInt32*>(CANTraits::clockSourceAddr);

    *p &= ~CANTraits::clockSourceMsk;
    *p |= ((uint32_t)clockSource << CANTraits::clockSourcePos) & CANTraits::clockSourceMsk;
}


/// ---------------------------------------------------------------------------
/// @brief
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <CANDeviceID deviceId_>
void CANDeviceX<deviceId_>::interruptHandler() {

    _instance.interruptService();
}
