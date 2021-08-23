#ifndef __STM32_halSPITpl__
#define __STM32_halSPITpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class SPIChannel: halSPIChannel {
		channel1 = HAL_SPI_CHANNEL_1,
		channel2 = HAL_SPI_CHANNEL_2,
		channel3 = HAL_SPI_CHANNEL_3,
		channel4 = HAL_SPI_CHANNEL_4,
		channel5 = HAL_SPI_CHANNEL_5,
		channel6 = HAL_SPI_CHANNEL_6
	};

	enum class SPIMode: halSPIOptions {
		mode0 = HAL_SPI_MODE_0,
		mode1 = HAL_SPI_MODE_1,
		mode2 = HAL_SPI_MODE_2,
		mode3 = HAL_SPI_MODE_3,
	};

	enum class SPISize: halSPIOptions {
		size8 = HAL_SPI_SIZE_8,
		size16 = HAL_SPI_SIZE_16
	};

	enum class SPIFirstBit: halSPIOptions {
		lsb = HAL_SPI_FIRSTBIT_LSB,
		msb = HAL_SPI_FIRSTBIT_MSB
	};

	enum class SPIClockDivider: halSPIOptions {
		clkdiv_2 = HAL_SPI_CLOCKDIV_2,
		clkdiv_4 = HAL_SPI_CLOCKDIV_4,
		clkdiv_8 = HAL_SPI_CLOCKDIV_8,
		clkdiv_16 = HAL_SPI_CLOCKDIV_16,
		clkdiv_32 = HAL_SPI_CLOCKDIV_32,
		clkdiv_64 = HAL_SPI_CLOCKDIV_64,
		clkdiv_128 = HAL_SPI_CLOCKDIV_128,
		clkdiv_256 = HAL_SPI_CLOCKDIV_256
	};

	template <SPIChannel channel>
	class SPIAdapter {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;
			constexpr static const SPISize _defaultSize = SPISize::size8;
			constexpr static const SPIFirstBit _defaultFirstBit = SPIFirstBit::lsb;

		private:
		    halSPIData _data;
			halSPIHandler _handler;

		public:
			inline void initMaster(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_MASTER |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline void initSlave(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_SLAVE |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				initialize(options);
			}

			inline void initialize(halSPIOptions options) {
				halSPISettings settings;
				settings.channel = halSPIChannel(channel);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline void initialize(const halSPISettings& settings) {
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline void setClock(SPIClockDivider clkdiv) {

			}

			inline void setInterruptFunction(halSPIInterruptFunction function, void* params) {
				halSPISetInterruptFunction(_handler, function, params);
			}

			inline void enableInterrupts(uint32_t events) {
				halSPIEnableInterrupts(_handler, events);
			}

			inline uint32_t disableInterrupts(uint32_t events) {
				return halSPIDisableInterrupts(_handler, events);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setSCKPin(GPIOPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SPIChannel::channel1)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi1_SCK);

				if constexpr (channel == SPIChannel::channel2)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi2_SCK);

				if constexpr (channel == SPIChannel::channel3)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi3_SCK);

				if constexpr (channel == SPIChannel::channel4)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi4_SCK);

				if constexpr (channel == SPIChannel::channel5)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi5_SCK);

				if constexpr (channel == SPIChannel::channel6)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi6_SCK);
			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setMOSIPin(GPIOPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SPIChannel::channel1)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi1_MOSI);

				if constexpr (channel == SPIChannel::channel2)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi2_MOSI);

				if constexpr (channel == SPIChannel::channel3)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi3_MOSI);

				if constexpr (channel == SPIChannel::channel4)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi4_MOSI);

				if constexpr (channel == SPIChannel::channel5)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi5_MOSI);

				if constexpr (channel == SPIChannel::channel6)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi6_MOSI);

			}

			template <GPIOPort port, GPIOPin pin>
			inline static void setMISOPin(GPIOPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == SPIChannel::channel1)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi1_MISO);

				if constexpr (channel == SPIChannel::channel2)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi2_MISO);

				if constexpr (channel == SPIChannel::channel2)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi2_MISO);

				if constexpr (channel == SPIChannel::channel3)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi3_MISO);

				if constexpr (channel == SPIChannel::channel5)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi5_MISO);

				if constexpr (channel == SPIChannel::channel6)
					pinAdapter.initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						GPIOPinAdapter<port, pin>::GPIOAlt::spi6_MISO);

			}

			inline void send(const uint8_t* data, int length, unsigned blockTime = _defaultBlockTime) {
				halSPISendBuffer(_handler, data, length, blockTime);
			}
	};


	typedef SPIAdapter<SPIChannel::channel1> SPI_1;
	typedef SPIAdapter<SPIChannel::channel2> SPI_2;
	typedef SPIAdapter<SPIChannel::channel3> SPI_3;
	typedef SPIAdapter<SPIChannel::channel4> SPI_4;
	typedef SPIAdapter<SPIChannel::channel5> SPI_5;
	typedef SPIAdapter<SPIChannel::channel6> SPI_6;

}


#endif // __STM32_halSPITpl__
