module;


#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.GPIO.__PORT_TRAITS;


import Eos.Types;
import Eos.Hardware.GPIO.__PLATFORM_TRAITS;
import Eos.Hardware.GPIO.__TYPES;


namespace eos::hardware::gpio::internal {

    namespace hidden {

        template <PortID portId_>
        struct Traits {
        };

        #ifdef GPIOA_BASE
        template <>
        struct Traits<PortID::portA> {
            static constexpr UInt32 gpioAddr     = GPIOA_BASE;
            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            static constexpr UInt32 activatePos  = RCC_IOPENR_GPIOAEN_Pos;
        };
        #endif

        #ifdef GPIOB_BASE
        template  <>
        struct Traits<PortID::portB> {
            static constexpr UInt32 gpioAddr     = GPIOB_BASE;
            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            static constexpr UInt32 activatePos  = RCC_IOPENR_GPIOBEN_Pos;
        };
        #endif

        #ifdef GPIOC_BASE
        template  <>
        struct Traits<PortID::portC> {
            static constexpr UInt32 gpioAddr     = GPIOC_BASE;
            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            static constexpr UInt32 activatePos  = RCC_IOPENR_GPIOCEN_Pos;
        };
        #endif

        #ifdef GPIOD_BASE
        template  <>
        struct Traits<PortID::portD> {
            static constexpr UInt32 gpioAddr     = GPIOD_BASE;
            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            static constexpr UInt32 activatePos  = RCC_IOPENR_GPIODEN_Pos;
        };
        #endif

        #ifdef GPIOE_BASE
        template  <>
        struct Traits<PortID::portE> {
            static constexpr UInt32 gpioAddr     = GPIOE_BASE;
        };
        #endif

        #ifdef GPIOF_BASE
        template  <>
        struct Traits<PortID::portF> {
            static constexpr UInt32 gpioAddr     = GPIOF_BASE;
            static constexpr UInt32 activateAddr = RCC_BASE + offsetof(RCC_TypeDef, IOPENR);
            static constexpr UInt32 activatePos  = RCC_IOPENR_GPIOFEN_Pos;
        };
        #endif

        #ifdef GPIOG_BASE
        template  <>
        struct Traits<PortID::portG> {
            static constexpr UInt32 gpioAddr = GPIOG_BASE;
        };
        #endif

        #ifdef GPIOH_BASE
        template  <>
        struct Traits<PortID::portH> {
            static constexpr UInt32 gpioAddr = GPIOH_BASE;
        };
        #endif

        #ifdef GPIOI_BASE
        template  <>
        struct Traits<PortID::portI> {
            static constexpr UInt32 gpioAddr = GPIOI_BASE;
        };
        #endif

        #ifdef GPIOJ_BASE
        template  <>
        struct Traits<PortID::portJ> {
            static constexpr UInt32 gpioAddr = GPIOJ_BASE;
        };
        #endif

        #ifdef GPIOK_BASE
        template  <>
        struct Traits<PortID::portK> {
            static constexpr UInt32 gpioAddr = GPIOK_BASE;
        };
        #endif
    }

    export template<PortID portId_> using PortTraits = hidden::Traits<portId_>;
}
