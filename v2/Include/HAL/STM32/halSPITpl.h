#ifndef __STM32_halSPITpl__
#define __STM32_halSPITpl__


#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class SpiChannel: SPIChannel {
		channel1 = HAL_SPI_CHANNEL_1,
		channel2 = HAL_SPI_CHANNEL_2,
		channel3 = HAL_SPI_CHANNEL_3,
		channel4 = HAL_SPI_CHANNEL_4,
		channel5 = HAL_SPI_CHANNEL_5,
		channel6 = HAL_SPI_CHANNEL_6
	};

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

	template <SpiChannel channel>
	class SpiAdapter {
		private:
		    SPIData _data;
			SPIHandler _handler;

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
				settings.channel = SPIChannel(channel);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			template <GpioPort port, GpioPin pin>
			inline static void setSCKPin(GpioPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SpiChannel::channel2)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi2_SCK);

				if constexpr (channel == SpiChannel::channel5)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi5_SCK);
			}

			template <GpioPort port, GpioPin pin>
			inline static void setMOSIPin(GpioPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SpiChannel::channel2)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi2_MOSI);

				if constexpr (channel == SpiChannel::channel5)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi5_MOSI);
			}

			template <GpioPort port, GpioPin pin>
			inline static void setMISOPin(GpioPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SpiChannel::channel2)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi2_MISO);

				if constexpr (channel == SpiChannel::channel5)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::pushPull,
						GpioPinAdapter<port, pin>::GpioAlt::spi5_MISO);
			}

			inline void send(const uint8_t* data, int length) {
				halSPISendBuffer(_handler, data, length);
			}
	};

}


#endif // __STM32_halSPITpl__
