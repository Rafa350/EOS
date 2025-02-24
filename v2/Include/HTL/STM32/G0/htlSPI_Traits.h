#pragma once
#ifndef __STM32G0_htlSPI_Traits__
#define __STM32G0_htlSPI_traits__


// HAL includes
//
#include "HTL/STM32/htl.h"


namespace htl {

	namespace spi {

		namespace internal {

			#ifdef HTL_SPI1_EXIST
			template<>
			struct SPITraits<DeviceID::spi1> {
				static constexpr uint32_t spiAddr = SPI1_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_SPI1EN_Pos;
			};
			#endif

			#ifdef HTL_SPI2_EXIST
			template<>
			struct SPITraits<DeviceID::spi2> {
				static constexpr uint32_t spiAddr = SPI2_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI2EN_Pos;
			};
			#endif

			#ifdef HTL_SPI3_EXIST
			template<>
			struct SPITraits<DeviceID::spi3> {
				static constexpr uint32_t spiAddr = SPI3_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI3EN_Pos;
			};
			#endif
		}
	}
}

#endif // __STM32G0_htlSPI_Traits__
