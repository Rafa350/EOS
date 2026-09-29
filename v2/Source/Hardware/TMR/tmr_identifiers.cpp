module;


export module Eos.Hardware.TMR.Identifiers;


import Eos.Configuration.Platform;


namespace eos {
    namespace hardware::tmr {
        namespace internal {

            template<PlatformID platformID_>
            struct PlatformTraits;

            template<>
            struct PlatformTraits<PlatformID::STM32_G031_K8> {
                enum class DeviceID { };
            };

            template<>
            struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
                enum class DeviceID { tmr1, tmr2, tmr3, tmr4, tmr6, tmr7, tmr14, tmr15, tmr16, tmr17 };
            };
        }

        export using TMRDeviceID = internal::PlatformTraits<Platform::id>::DeviceID;
    }

}


#if 0
enum class TMRDeviceID {
#ifdef HTL_TMR1_EXIST
        tmr1,
#endif
#ifdef HTL_TMR2_EXIST
        tmr2,
#endif
#ifdef HTL_TMR3_EXIST
        tmr3,
#endif
#ifdef HTL_TMR4_EXIST
        tmr4,
#endif
#ifdef HTL_TMR5_EXIST
        tmr5,
#endif
#ifdef HTL_TMR6_EXIST
        tmr6,
#endif
#ifdef HTL_TMR7_EXIST
        tmr7,
#endif
#ifdef HTL_TMR8_EXIST
        tmr8,
#endif
#ifdef HTL_TMR9_EXIST
        tmr9,
#endif
#ifdef HTL_TMR10_EXIST
        tmr10,
#endif
#ifdef HTL_TMR11_EXIST
        tmr11,
#endif
#ifdef HTL_TMR12_EXIST
        tmr12,
#endif
#ifdef HTL_TMR13_EXIST
        tmr13,
#endif
#ifdef HTL_TMR14_EXIST
        tmr14,
#endif
#ifdef HTL_TMR15_EXIST
        tmr15,
#endif
#ifdef HTL_TMR16_EXIST
        tmr16,
#endif
#ifdef HTL_TMR17_EXIST
        tmr17,
#endif
};
#endif
