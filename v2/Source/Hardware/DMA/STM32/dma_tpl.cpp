module;


#include "HTL/htl.h"


export module Eos.Hardware.DMA.Templates;


import Eos.Hardware.Regs;
import Eos.Hardware.DMA.Identifiers;
import Eos.Hardware.DMA.Classes;
import Eos.Hardware.DMA.Traits;


namespace eos::hardware::dma {

    export template <DMADeviceID deviceID_>
    class DMADeviceX final: public DMADevice {
        private:
            using Traits = internal::DMATraits<deviceID_>;

        private:
            static constexpr auto _dmaAddr = Traits::dmaAddr;
            static constexpr auto _dmaChannelAddr = Traits::dmaChannelAddr;
            static constexpr auto _muxChannelStatusAddr = Traits::muxChannelStatusAddr;
            static constexpr auto _muxChannelAddr = Traits::muxChannelAddr;
            static constexpr auto _activateAddr = Traits::activateAddr;
            static constexpr auto _activatePos = Traits::activatePos;
            static DMADeviceX _instance;

        private:
            DMADeviceX();

        protected:
            void activateImpl() const override;
#if HTL_DMA_OPTION_DEACTIVATE == 1
            void deactivateImpl() const override;
#endif

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


using namespace eos::hardware::dma;


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
    DMADevice {_dmaAddr, _dmaChannelAddr, _muxChannelStatusAddr, _muxChannelAddr} {

}


/// ---------------------------------------------------------------------------
/// @brief    Activa el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::activateImpl() const {

    Reg32Flag<_activateAddr, _activatePos>::set();
    DSB();
}


#if HTL_DMA_OPTION_DEACTIVATE == 1
/// ---------------------------------------------------------------------------
/// @brief    Desactiva el dispositiu.
/// @tparam   deviceID_: Identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::deactivateImpl() const {

    Reg32Flag<_activateAddr, _activatePos>::clear();
    DSB();
}
#endif


/// ---------------------------------------------------------------------------
/// @brief    Procesa la interrupcio.
/// @tparam   deviceID_: El identificador del dispositiu.
///
template <DMADeviceID deviceID_>
void DMADeviceX<deviceID_>::interruptHandler() {

    _instance.interruptService();
}
