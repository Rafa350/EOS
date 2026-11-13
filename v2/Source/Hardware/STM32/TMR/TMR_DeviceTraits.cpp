module;

#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.TMR._DeviceTraits;

import Eos.Hardware.Interrupts;
import Eos.Hardware.TMR._Types;
import Eos.Types;


using namespace eos::hardware::interrupts;


export namespace eos::hardware::tmr::internal {

    template <TMRDeviceID>
    struct TMRTraits;

#ifdef TIM1_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr1> {
        static constexpr UInt32 timAddr = TIM1_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr UInt32 activatePos = RCC_APBENR2_TIM1EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr1_BRK_UP_TRG_COM;
    };
#endif

#ifdef TIM2_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr2> {
        static constexpr UInt32 timAddr = TIM2_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_TIM2EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr2;
    };
#endif

#ifdef TIM3_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr3> {
        static constexpr UInt32 timAddr = TIM3_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_TIM3EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr3;
    };
#endif

#ifdef TIM4_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr4> {
        static constexpr UInt32 timAddr = TIM4_BASE;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr4;
    };
    #endif

#ifdef TIM5_BASE
    template <>
    struct TMRTraits<DeviceID::tmr5> {
        static constexpr UInt32 timAddr = TIM5_BASE;
    };
#endif

#ifdef TIM6_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr6> {
        static constexpr UInt32 timAddr = TIM6_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_TIM6EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr6;
    };
#endif

#ifdef TIM7_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr7> {
        static constexpr UInt32 timAddr = TIM7_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr UInt32 activatePos = RCC_APBENR1_TIM7EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr7;
    };
#endif

#ifdef TIM8_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr8> {
        static constexpr UInt32 timAddr = TIM8_BASE;
    };
#endif

#ifdef TIM9_BASE
    template <>
    struct TMRTraitsTMRDeviceID::tmr9> {
        static constexpr UInt32 timAddr = TIM9_BASE;
    };
#endif

#ifdef TIM10_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_10> {
        static constexpr UInt32 timAddr = TIM10_BASE;
    };
#endif

#ifdef TIM11_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_11> {
        static constexpr UInt32 timAddr = TIM11_BASE;
    };
#endif

#ifdef TIM12_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_12> {
        static constexpr UInt32 timAddr = TIM12_BASE;
    };
#endif

#ifdef TIM13_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_13> {
        static constexpr UInt32 timAddr = TIM13_BASE;
    };
#endif

#ifdef TIM14_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr14> {
        static constexpr UInt32 timAddr = TIM14_BASE;

        static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr UInt32 activatePos = RCC_APBENR2_TIM14EN_Pos;

        static constexpr auto interruptVectorId = Irq::VectorID::tmr14;
    };
#endif

}
