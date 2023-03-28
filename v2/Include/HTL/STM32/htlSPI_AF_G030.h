#pragma once
#ifndef __STM32_htlSPI_AF_G030__
#define __STM32_htlSPI_AF_G030__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


namespace htl {

	#ifdef HTL_SPI1_EXIST

	#if defined(EOS_PLATFORM_STM32F0)
		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A5, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A6, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A7, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};
	#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A5, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A6, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_A7, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_B3, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_B4, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_1, GPIO_B5, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};
	#endif
#endif

#ifdef HTL_SPI2_EXIST
	template<>
	struct SPITrait<SPIChannel::_2> {
		static constexpr uint32_t addr = SPI2_BASE;
		static constexpr INTVector vector = INTVector::spi2;
	};

	#if defined(EOS_PLATFORM_STM32F0)
		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B10, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B14, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B15, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_0;
		};
	#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B10, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B13, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B14, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_B15, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_C2, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_C3, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_D3, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_I1, SPIPin::SCK> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_I2, SPIPin::MISO> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::_2, GPIO_I3, SPIPin::MOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::_5;
		};
	#endif
#endif

#ifdef HTL_SPI3_EXIST
	template<>
	struct SPITrait<SPIChannel::_3> {
		static constexpr uint32_t addr = SPI3_BASE;
		static constexpr INTVector vector = INTVector::spi3;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_B3, SPIPin::SCK> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_B4, SPIPin::MISO> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_B5, SPIPin::MOSI> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_C10, SPIPin::SCK> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_C11, SPIPin::MISO> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_C12, SPIPin::MOSI> {
		static constexpr GPIOAlt alt = GPIOAlt::_6;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_3, GPIO_D6, SPIPin::MOSI> {
		static constexpr GPIOAlt alt = GPIOAlt::_5;
	};
#endif

#ifdef HTL_SPI4_EXIST
	template<>
	struct SPITrait<SPIChannel::_4> {
		static constexpr uint32_t addr = SPI4_BASE;
		static constexpr INTVector vector = INTVector::spi4;
	};
#endif

#ifdef HTL_SPI5_EXIST
	template<>
	struct SPITrait<SPIChannel::_5> {
		static constexpr uint32_t addr = SPI5_BASE;
		static constexpr INTVector vector = INTVector::spi5;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_5, GPIO_F7, SPIPin::SCK> {
		static constexpr GPIOAlt alt = GPIOAlt::_5;
	};

	template <>
	struct SPIPinTrait<SPIChannel::_5, GPIO_F9, SPIPin::MOSI> {
		static constexpr GPIOAlt alt = GPIOAlt::_5;
	};
#endif

}


#endif // __STM32_htlSPI_AF_G030__
