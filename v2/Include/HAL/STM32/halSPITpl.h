#ifndef __STM32_halSPITpl__
#define __STM32_halSPITpl__


#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class SpiMode: SPIOptions {
		mode0 = HAL_SPI_MODE_0,
		mode1 = HAL_SPI_MODE_1,
		mode2 = HAL_SPI_MODE_2,
		mode3 = HAL_SPI_MODE_3,
	};

	enum class SpiSize: SPIOptions {
		size8 = HAL_SPI_SIZE_8,
		size16 = HAL_SPI_SIZE_16
	};

	template <SPIChannel channel>
	class SpiAdapter {
		private:
		    SPIData _spiData;
			SPIHandler _spiHandler;

		public:
			inline void initMaster(SpiMode mode, SpiSize size) {
				SPIOptions options =
					HAL_SPI_MS_MASTER |
					SPIOptions(size) |
					SPIOptions(mode);
				initialize(options);
			}

			inline void initSlave(SpiMode mode, SpiSize size) {
				SPIOptions options =
					HAL_SPI_MS_SLAVE |
					SPIOptions(size) |
					SPIOptions(mode);
				initialize(options);
			}

			inline void initialize(SPIOptions options) {
				SPISettings settings;
				settings.channel = channel;
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_spiHandler = halSPIInitialize(&_spiData, &settings);
			}

			inline void send(const uint8_t* data, int length) {
				halSPISendBuffer(_spiHandler, data, length);
			}
	};

	template <GPIOPort port, GPIOPin pin, SPIChannel channel>
	struct SpiGPIOAlt {
		private:
			constexpr static GPIOAlt getSCK() {
				if constexpr (channel == HAL_SPI_CHANNEL_1)
					return GpioFunction<port, pin>::spi1_SCK;
				if constexpr (channel == HAL_SPI_CHANNEL_2)
					return GpioFunction<port, pin>::spi2_SCK;
				if constexpr (channel == HAL_SPI_CHANNEL_3)
					return GpioFunction<port, pin>::spi3_SCK;
				if constexpr (channel == HAL_SPI_CHANNEL_4)
					return GpioFunction<port, pin>::spi4_SCK;
				if constexpr (channel == HAL_SPI_CHANNEL_5)
					return GpioFunction<port, pin>::spi5_SCK;
				return HAL_GPIO_AF_NONE;
			}

			constexpr static GPIOAlt getMOSI() {
				if constexpr (channel == HAL_SPI_CHANNEL_1)
					return GpioFunction<port, pin>::spi1_MOSI;
				if constexpr (channel == HAL_SPI_CHANNEL_2)
					return GpioFunction<port, pin>::spi2_MOSI;
				if constexpr (channel == HAL_SPI_CHANNEL_3)
					return GpioFunction<port, pin>::spi3_MOSI;
				if constexpr (channel == HAL_SPI_CHANNEL_4)
					return GpioFunction<port, pin>::spi4_MOSI;
				if constexpr (channel == HAL_SPI_CHANNEL_5)
					return GpioFunction<port, pin>::spi5_MOSI;
				return HAL_GPIO_AF_NONE;
			}

		public:
			constexpr static const GPIOAlt sckAlt = getSCK();
			constexpr static const GPIOAlt mosiAlt = getMOSI();
	};
}


#endif // __STM32_halSPITpl__
