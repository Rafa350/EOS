module;


#include "HTL/htl.h"


export module Eos.Hardware.TMR.Traits;


import Eos.Hardware.TMR.Identifiers;


export namespace eos::hardware::tmr {

    namespace internal {

        template <TMRDeviceID>
        struct TMRTraits;

#ifdef HTL_TMR1_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr1> {
            static constexpr uint32_t timAddr = TIM1_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
            static constexpr uint32_t activatePos = RCC_APBENR2_TIM1EN_Pos;
        };
#endif

#ifdef HTL_TMR2_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr2> {
            static constexpr uint32_t timAddr = TIM2_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
            static constexpr uint32_t activatePos = RCC_APBENR1_TIM2EN_Pos;
        };
#endif

#ifdef HTL_TMR3_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr3> {
            static constexpr uint32_t timAddr = TIM3_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
            static constexpr uint32_t activatePos = RCC_APBENR1_TIM3EN_Pos;
        };
#endif

#ifdef HTL_TMR4_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr4> {
            static constexpr uint32_t timAddr = TIM4_BASE;
        };
        #endif

#ifdef HTL_TMR5_EXIST
        template <>
        struct TMRTraits<DeviceID::tmr5> {
            static constexpr uint32_t timAddr = TIM5_BASE;
        };
#endif

#ifdef HTL_TMR6_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr6> {
            static constexpr uint32_t timAddr = TIM6_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
            static constexpr uint32_t activatePos = RCC_APBENR1_TIM6EN_Pos;
        };
#endif

#ifdef HTL_TMR7_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr7> {
            static constexpr uint32_t timAddr = TIM7_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
            static constexpr uint32_t activatePos = RCC_APBENR1_TIM7EN_Pos;
        };
#endif

#ifdef HTL_TMR8_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr8> {
            static constexpr uint32_t timAddr = TIM8_BASE;
        };
#endif

#ifdef HTL_TMR9_EXIST
        template <>
        struct TMRTraitsTMRDeviceID::tmr9> {
            static constexpr uint32_t timAddr = TIM9_BASE;
        };
#endif

#ifdef HTL_TMR10_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::_10> {
            static constexpr uint32_t timAddr = TIM10_BASE;
        };
#endif

#ifdef HTL_TMR11_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::_11> {
            static constexpr uint32_t timAddr = TIM11_BASE;
        };
#endif

#ifdef HTL_TMR12_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::_12> {
            static constexpr uint32_t timAddr = TIM12_BASE;
        };
#endif

#ifdef HTL_TMR13_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::_13> {
            static constexpr uint32_t timAddr = TIM13_BASE;
        };
#endif

#ifdef HTL_TMR14_EXIST
        template <>
        struct TMRTraits<TMRDeviceID::tmr14> {
            static constexpr uint32_t timAddr = TIM14_BASE;

            static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
            static constexpr uint32_t activatePos = RCC_APBENR2_TIM14EN_Pos;
        };
#endif

    }
}
