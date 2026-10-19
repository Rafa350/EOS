module;


#include "hardware.h"
#include <cstddef>


export module Eos.Hardware.GPIO.__PORT_TRAITS;


import Eos.Platform;
import Eos.Types;
import Eos.Hardware.GPIO.__PLATFORM_TRAITS;
import Eos.Hardware.GPIO.__TYPES;


static_assert(eos::platformCheck("STM32F4xxxx"));


namespace eos::hardware::gpio::internal {

    namespace hidden {

        template <PortID portId_>
        struct PortTraits {
        };

        #ifdef GPIOA_BASE
        template <>
        struct PortTraits<PortID::portA> {
            static constexpr UInt32 gpioAddr     = GPIOA_BASE;
    		static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOAEN_Pos;
        };
        #endif

        #ifdef GPIOB_BASE
        template <>
        struct PortTraits<PortID::portB> {
            static constexpr UInt32 gpioAddr     = GPIOB_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOBEN_Pos;
        };
        #endif

        #ifdef GPIOC_BASE
        template <>
        struct PortTraits<PortID::portC> {
            static constexpr UInt32 gpioAddr     = GPIOC_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOCEN_Pos;
        };
        #endif

        #ifdef GPIOD_BASE
        template <>
        struct PortTraits<PortID::portD> {
            static constexpr UInt32 gpioAddr     = GPIOD_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIODEN_Pos;
        };
        #endif

        #ifdef GPIOE_BASE
        template <>
        struct PortTraits<PortID::portE> {
            static constexpr UInt32 gpioAddr     = GPIOE_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOEEN_Pos;
        };
        #endif

        #ifdef GPIOF_BASE
        template <>
        struct PortTraits<PortID::portF> {
            static constexpr UInt32 gpioAddr     = GPIOF_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOFEN_Pos;
        };
        #endif

        #ifdef GPIOG_BASE
        template <>
        struct PortTraits<PortID::portG> {
            static constexpr UInt32 gpioAddr = GPIOG_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOGEN_Pos;
        };
        #endif

        #ifdef GPIOH_BASE
        template <>
        struct PortTraits<PortID::portH> {
            static constexpr UInt32 gpioAddr = GPIOH_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOHEN_Pos;
        };
        #endif

        #ifdef GPIOI_BASE
        template <>
        struct PortTraits<PortID::portI> {
            static constexpr UInt32 gpioAddr = GPIOI_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOIEN_Pos;
        };
        #endif

        #ifdef GPIOJ_BASE
        template <>
        struct PortTraits<PortID::portJ> {
            static constexpr UInt32 gpioAddr = GPIOJ_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOJEN_Pos;
        };
        #endif

        #ifdef GPIOK_BASE
        template <>
        struct PortTraits<PortID::portK> {
            static constexpr UInt32 gpioAddr = GPIOK_BASE;
			static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, AHB1ENR);
			static constexpr uint32_t activatePos = RCC_AHB1ENR_GPIOKEN_Pos;
        };
        #endif
    }

    export template<PortID portId_> using PortTraits = hidden::PortTraits<portId_>;
}
