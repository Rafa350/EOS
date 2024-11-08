#pragma once
#ifndef __STM32F4_htlSPI_Traits__
#define __STM32F4_htlSPI_Traits__


namespace htl {
	namespace spi {
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			template<>
			struct SPITraits<DeviceID::_1> {
				static constexpr uint32_t spiAddr = SPI1_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
			};
			#endif

			#ifdef HTL_SPI2_EXIST
			template<>
			struct SPITraits<DeviceID::_2> {
				static constexpr uint32_t spiAddr = SPI2_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
			};
			#endif

			#ifdef HTL_SPI3_EXIST
			template<>
			struct SPITraits<DeviceID::_3> {
				static constexpr uint32_t spiAddr = SPI3_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
			};
			#endif

			#ifdef HTL_SPI4_EXIST
			template<>
			struct SPITraits<DeviceID::_4> {
				static constexpr uint32_t spiAddr = SPI4_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
			};
			#endif

			#ifdef HTL_SPI5_EXIST
			template<>
			struct SPITraits<DeviceID::_5> {
				static constexpr uint32_t spiAddr = SPI5_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
			};
			#endif

			#ifdef HTL_SPI6_EXIST
			template<>
			struct SPITraits<DeviceID::_6> {
				static constexpr uint32_t spiAddr = SPI6_BASE;
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI6EN_Pos;
			};
			#endif
		}
	}
}

#endif // __STM32F4_SPI_Traits__

