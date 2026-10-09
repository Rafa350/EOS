module;


#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


export module Eos.Hardware.SPI.Templates;


import Eos.Hardware.Regs;
import Eos.Hardware.SPI.Classes;
import Eos.Hardware.SPI.Identifiers;
import Eos.Hardware.SPI.__DEVICE_TRAITS;
import Eos.Hardware.SPI.__PIN_TRAITS;
import Eos.Types;


export namespace eos::hardware::spi {

    template <SPIDeviceID deviceID_>
    class SPIDeviceX final: public SPIDevice {
        private:
            using Traits = internal::SPITraits<deviceID_>;
			using ActivateFlag = Reg32Flag<Traits::activateAddr, Traits::activatePos>;

            static constexpr auto _spiAddr = Traits::spiAddr;
            static SPIDeviceX _instance;

        public:
            static constexpr auto deviceID = deviceID_;
            static constexpr SPIDeviceX *pInst = &_instance;
            static constexpr SPIDeviceX &rInst = _instance;

        private:
            SPIDeviceX();

        protected:
            void activateImpl() const override;
#if HTL_SPI_OPTION_DEACTIVATE == 1
            void deactivateImpl() const override;
#endif

        public:
            static void interruptHandler();

            template <typename pin_> void initPinSCK();
            template <typename pin_> void initPinMOSI();
            template <typename pin_> void initPinMISO();
    };

    template <SPIDeviceID deviceID_>
    SPIDeviceX<deviceID_> SPIDeviceX<deviceID_>::_instance;
}


using namespace eos;
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
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <SPIDeviceID deviceID_>
SPIDeviceX<deviceID_>::SPIDeviceX() :

    SPIDevice(reinterpret_cast<SPI_TypeDef *>(_spiAddr)) {
}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <SPIDeviceID deviceID_>
void SPIDeviceX<deviceID_>::activateImpl() const {

    ActivateFlag::set();
    DSB();
}


#if HTL_SPI_OPTION_DEACTIVATE == 1
/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <SPIDeviceID deviceID_>
void SPIDeviceX<deviceID_>::deactivateImpl() const {

    ActivateFlag::clear();
    DSB();
}
#endif


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin SCK.
/// @tparam   deviceID_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceID_>
template <typename pin_>
void SPIDeviceX<deviceID_>::initPinSCK() {

    namespace g = htl::gpio;

    auto v = PinTraits<deviceID_, PinFunction::sck, pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull, g::PullUpDown::none, g::Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin MOSI.
/// @tparam   deviceID_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceID_>
template <typename pin_>
void SPIDeviceX<deviceID_>::initPinMOSI() {

    namespace g = htl::gpio;

    auto v = PinTraits<deviceID_, PinFunction::mosi, pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull, g::PullUpDown::none, g::Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitza el pin MISO.
/// @tparam   deviceID_: Identificador del dispositiu.
/// @tparam   pin_: Identificador del pin.
///
template <SPIDeviceID deviceID_>
template <typename pin_>
void SPIDeviceX<deviceID_>::initPinMISO() {

    namespace g = htl::gpio;

    auto v = PinTraits<deviceID_, PinFunction::miso, pin_::portID, pin_::pinID>::value;

    g::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(
        g::OutputType::pushPull, g::PullUpDown::none, g::Speed::fast, v);
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interruipcio.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <SPIDeviceID deviceID_>
void SPIDeviceX<deviceID_>::interruptHandler() {

    _instance.interruptService();
}
