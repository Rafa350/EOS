#ifndef __STM32_halSPITpl__
#define __STM32_halSPITpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halSPI.h"
#include "HAL/STM32/halGPIO_ex.h"


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

	template <SPIChannel channel_>
	class SPIModule {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;
			constexpr static const SPISize _defaultSize = SPISize::size8;
			constexpr static const SPIFirstBit _defaultFirstBit = SPIFirstBit::lsb;

		private:
		    halSPIData _data;
			halSPIHandler _handler;

		public:
			constexpr static const SPIChannel channel = channel_;

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
				settings.channel = halSPIChannel(channel_);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline void initialize(const halSPISettings &settings) {
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline void setClock(SPIClockDivider clkdiv) {

			}

			inline void setInterruptFunction(halSPIInterruptFunction function, void *params) {
				halSPISetInterruptFunction(_handler, function, params);
			}

			inline void enableInterrupts(uint32_t events) {
				halSPIEnableInterrupts(_handler, events);
			}

			inline uint32_t disableInterrupts(uint32_t events) {
				return halSPIDisableInterrupts(_handler, events);
			}

			template <typename pinAdapter_>
			inline static void initSCKPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi1_SCK);

				if constexpr (channel_ == SPIChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi2_SCK);

				if constexpr (channel_ == SPIChannel::channel3)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi3_SCK);

				if constexpr (channel_ == SPIChannel::channel4)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi4_SCK);

				if constexpr (channel_ == SPIChannel::channel5)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi5_SCK);

				if constexpr (channel_ == SPIChannel::channel6)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi6_SCK);
			}

			template <typename pinAdapter_>
			inline static void initMOSIPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi1_MOSI);

				if constexpr (channel_ == SPIChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi2_MOSI);

				if constexpr (channel_ == SPIChannel::channel3)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi3_MOSI);

				if constexpr (channel_ == SPIChannel::channel4)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi4_MOSI);

				if constexpr (channel_ == SPIChannel::channel5)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi5_MOSI);

				if constexpr (channel_ == SPIChannel::channel6)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi6_MOSI);

			}

			template <typename pinAdapter_>
			inline static void initMISOPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi1_MISO);

				if constexpr (channel_ == SPIChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi2_MISO);

				if constexpr (channel_ == SPIChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi2_MISO);

				if constexpr (channel_ == SPIChannel::channel3)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi3_MISO);

				if constexpr (channel_ == SPIChannel::channel5)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi5_MISO);

				if constexpr (channel_ == SPIChannel::channel6)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						pinAdapter_::GPIOAlt::spi6_MISO);
			}

			inline void send(const uint8_t data, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, &data, sizeof(data), blockTime);
			}

			inline void send(const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, data, size, blockTime);
			}
	};


	typedef SPIModule<SPIChannel::channel1> SPI_1;
	typedef SPIModule<SPIChannel::channel2> SPI_2;
	typedef SPIModule<SPIChannel::channel3> SPI_3;
	typedef SPIModule<SPIChannel::channel4> SPI_4;
	typedef SPIModule<SPIChannel::channel5> SPI_5;
	typedef SPIModule<SPIChannel::channel6> SPI_6;

}


#endif // __STM32_halSPITpl__
