module;


#include "HTL/htl.h"


export module Eos.Hardware.DMA.__TEMPLATES;


import Eos.Hardware.Regs;
import Eos.Hardware.DMA.__CLASSES;
import Eos.Hardware.DMA.__DEVICE_TRAITS;
import Eos.Hardware.DMA.__PLATFORM_TRAITS;


namespace eos::hardware::dma {

    export template <DMADeviceID deviceID_>
    class DMADeviceX final: public DMADevice {
        private:
            using DMATraits = internal::DMATraits<deviceID_>;

        private:
            static DMADeviceX _instance;

        private:
            DMADeviceX();

        protected:
            void activateImpl() const override;
            void deactivateImpl() const override;

        public:
            static constexpr auto deviceID = deviceID_;
            static constexpr DMADeviceX *pInst = &_instance;
            static constexpr DMADeviceX &rInst = _instance;

        public:
            static void interruptHandler();
    };

    export template <DMADeviceID deviceID_>
    DMADeviceX<deviceID_> DMADeviceX<deviceID_>::_instance;
}


using namespace eos;
using namespace eos::hardware::dma;
using namespace eos::hardware::dma::internal;


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
template <DMADeviceID deviceID_>
DMADeviceX<deviceID_>::DMADeviceX() :
    DMADevice {DMATraits::dmaAddr, DMATraits::dmaChannelAddr,
        DMATraits::muxChannelStatusAddr, DMATraits::muxChannelAddr} {

}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::activateImpl() const {

    Reg32Flag<DMATraits::activateAddr, DMATraits::activatePos>::set();
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::deactivateImpl() const {

    Reg32Flag<DMATraits::activateAddr, DMATraits::activatePos>::clear();
    DSB();
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interrupcio.
/// @tparam   deviceID_: El identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::interruptHandler() {

    _instance.interruptService();
}
