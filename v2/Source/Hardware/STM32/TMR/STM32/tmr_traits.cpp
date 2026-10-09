module;


#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.TMR.Traits;


import Eos.Hardware.TMR.Identifiers;


export namespace eos::hardware::tmr::internal {

    template <TMRDeviceID>
    struct TMRTraits;

#ifdef TIM1_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr1> {
        static constexpr uint32_t timAddr = TIM1_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr uint32_t activatePos = RCC_APBENR2_TIM1EN_Pos;
    };
#endif

#ifdef TIM2_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr2> {
        static constexpr uint32_t timAddr = TIM2_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr uint32_t activatePos = RCC_APBENR1_TIM2EN_Pos;
    };
#endif

#ifdef TIM3_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr3> {
        static constexpr uint32_t timAddr = TIM3_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr uint32_t activatePos = RCC_APBENR1_TIM3EN_Pos;
    };
#endif

#ifdef TIM4_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr4> {
        static constexpr uint32_t timAddr = TIM4_BASE;
    };
    #endif

#ifdef TIM5_BASE
    template <>
    struct TMRTraits<DeviceID::tmr5> {
        static constexpr uint32_t timAddr = TIM5_BASE;
    };
#endif

#ifdef TIM6_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr6> {
        static constexpr uint32_t timAddr = TIM6_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr uint32_t activatePos = RCC_APBENR1_TIM6EN_Pos;
    };
#endif

#ifdef TIM7_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr7> {
        static constexpr uint32_t timAddr = TIM7_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
        static constexpr uint32_t activatePos = RCC_APBENR1_TIM7EN_Pos;
    };
#endif

#ifdef TIM8_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr8> {
        static constexpr uint32_t timAddr = TIM8_BASE;
    };
#endif

#ifdef TIM9_BASE
    template <>
    struct TMRTraitsTMRDeviceID::tmr9> {
        static constexpr uint32_t timAddr = TIM9_BASE;
    };
#endif

#ifdef TIM10_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_10> {
        static constexpr uint32_t timAddr = TIM10_BASE;
    };
#endif

#ifdef TIM11_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_11> {
        static constexpr uint32_t timAddr = TIM11_BASE;
    };
#endif

#ifdef TIM12_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_12> {
        static constexpr uint32_t timAddr = TIM12_BASE;
    };
#endif

#ifdef TIM13_BASE
    template <>
    struct TMRTraits<TMRDeviceID::_13> {
        static constexpr uint32_t timAddr = TIM13_BASE;
    };
#endif

#ifdef TIM14_BASE
    template <>
    struct TMRTraits<TMRDeviceID::tmr14> {
        static constexpr uint32_t timAddr = TIM14_BASE;

        static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
        static constexpr uint32_t activatePos = RCC_APBENR2_TIM14EN_Pos;
    };
#endif

}
