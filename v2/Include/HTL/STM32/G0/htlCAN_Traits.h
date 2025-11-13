#pragma once
#ifndef __STM32G0_htlCAN_Traits__
#define __STM32G0_htlCAN_traits__


// HAL includes
//
#include "HTL/STM32/htl.h"


#define SRAMCAN_SIZE 848      // Tamany de la ram en bytes


namespace htl {
	namespace can {
		namespace internal {

#ifdef HTL_CAN1_EXIST
			template <>
			struct CANTraits<DeviceID::can1> {
				static constexpr uint32_t canAddr = FDCAN1_BASE;
				static constexpr uint32_t ramAddr = SRAMCAN_BASE;

				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_FDCANEN_Pos;

				static constexpr uint32_t clockSourceAddr = RCC_BASE + offsetof(RCC_TypeDef, CCIPR2);
				static constexpr uint32_t clockSourcePos = RCC_CCIPR2_FDCANSEL_Pos;
				static constexpr uint32_t clockSourceMsk = RCC_CCIPR2_FDCANSEL_Msk;
			};
#endif

#ifdef HTL_CAN2_EXIST
			template <>
			struct CANTraits<DeviceID::can2> {
				static constexpr uint32_t canAddr = FDCAN2_BASE;
				static constexpr uint32_t ramAddr = SRAMCAN_BASE + SRAMCAN_SIZE;

				static constexpr uint32_t activateAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t activatePos = RCC_APBENR1_FDCANEN_Pos;
			};
#endif
		}
	}
}


#endif // __STM32G0_htlUART_Traits__
