module;


#include "hardware.h"


export module Eos.Hardware.SPI._Templates;


import Eos.Hardware.GPIO;
import Eos.Hardware.Regs;
import Eos.Hardware.SPI._Classes;
import Eos.Hardware.SPI._Types;
import Eos.Hardware.SPI._PlatformTraits;
import Eos.Hardware.SPI._DeviceTraits;
import Eos.Hardware.SPI._PinTraits;
import Eos.Types;


export namespace eos::hardware::spi {

    template <SPIDeviceID deviceId_>
    class SPIDeviceX final: public SPIDevice {
        private:
            using Traits = internal::SPITraits<deviceId_>;
			using ActivateFlag = Reg32Flag<Traits::activateAddr, Traits::activatePos>;

            static constexpr auto _spiAddr = Traits::spiAddr;
            static SPIDeviceX _instance;

        public:
            static constexpr auto deviceID = deviceId_;
            static constexpr SPIDeviceX *pInst = &_instance;
            static constexpr SPIDeviceX &rInst = _instance;

        private:
            SPIDeviceX();

        protected:
            void activateImpl() const override;
            void deactivateImpl() const override;

        public:
            static void interruptHandler();

            template <typename pin_> void initPinSCK();
            template <typename pin_> void initPinMOSI();
            template <typename pin_> void initPinMISO();
    };

    template <SPIDeviceID deviceId_>
    SPIDeviceX<deviceId_> SPIDeviceX<deviceId_>::_instance;
}


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;
using namespace eos::hardware::spi::internal;


/// ---------------------------------------------------------------------------
/// @brief    Crida a DSB desde aquest modul C++20
///
void DSB() {

	__DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <SPIDeviceID deviceId_>
SPIDeviceX<deviceId_>::SPIDeviceX() :

    SPIDevice(reinterpret_cast<SPI_TypeDef *>(_spiAddr)) {
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <SPIDeviceID deviceId_>
void SPIDeviceX<deviceId_>::activateImpl() const {

    ActivateFlag::set();
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <SPIDeviceID deviceId_>
void SPIDeviceX<deviceId_>::deactivateImpl() const {

    ActivateFlag::clear();
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin SCK.
/// @tparam   deviceId_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceId_>
template <typename pin_>
void SPIDeviceX<deviceId_>::initPinSCK() {

    auto v = PinTraits<deviceId_, PinFunction::sck, pin_::portID, pin_::pinID>::value;

    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        OutputType::pushPull, PullUpDown::none, Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin MOSI.
/// @tparam   deviceId_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceId_>
template <typename pin_>
void SPIDeviceX<deviceId_>::initPinMOSI() {

    auto v = PinTraits<deviceId_, PinFunction::mosi, pin_::portID, pin_::pinID>::value;

    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        OutputType::pushPull, PullUpDown::none, Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin MISO.
/// @tparam   deviceId_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceId_>
template <typename pin_>
void SPIDeviceX<deviceId_>::initPinMISO() {

    auto v = PinTraits<deviceId_, PinFunction::miso, pin_::portID, pin_::pinID>::value;

    GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        OutputType::pushPull, PullUpDown::none, Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interruipcio.
/// @tparam   deviceId_: Identificador del dispositiu.
///
template <SPIDeviceID deviceId_>
void SPIDeviceX<deviceId_>::interruptHandler() {

    _instance.interruptService();
}
