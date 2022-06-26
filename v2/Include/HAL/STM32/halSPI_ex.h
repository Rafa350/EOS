#ifndef __STM32_halSPI_ex__
#define __STM32_halSPI_ex__


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

	template <SPIChannel channel_, typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
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

		private:
			SPIModule() = default;
			SPIModule(const SPIModule &) = delete;
			SPIModule(const SPIModule &&) = delete;
			SPIModule & operator = (const SPIModule &) = delete;
			SPIModule & operator = (const SPIModule &&) = delete;

		public:
			inline static auto & instance() {
				static SPIModule module;
				return module;
			}

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

			inline static void initSCKPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi1_SCK);

				if constexpr (channel_ == SPIChannel::channel2)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi2_SCK);

				if constexpr (channel_ == SPIChannel::channel3)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi3_SCK);

				if constexpr (channel_ == SPIChannel::channel4)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi4_SCK);

				if constexpr (channel_ == SPIChannel::channel5)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi5_SCK);

				if constexpr (channel_ == SPIChannel::channel6)
					sckPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						sckPin_::GPIOAlt::spi6_SCK);
			}

			inline static void initMOSIPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi1_MOSI);

				if constexpr (channel_ == SPIChannel::channel2)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi2_MOSI);

				if constexpr (channel_ == SPIChannel::channel3)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi3_MOSI);

				if constexpr (channel_ == SPIChannel::channel4)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi4_MOSI);

				if constexpr (channel_ == SPIChannel::channel5)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi5_MOSI);

				if constexpr (channel_ == SPIChannel::channel6)
					mosiPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						mosiPin_::GPIOAlt::spi6_MOSI);

			}

			inline static void initMISOPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi1_MISO);

				if constexpr (channel_ == SPIChannel::channel2)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi2_MISO);

				if constexpr (channel_ == SPIChannel::channel3)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi3_MISO);

				if constexpr (channel_ == SPIChannel::channel4)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi4_MISO);

				if constexpr (channel_ == SPIChannel::channel5)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi5_MISO);

				if constexpr (channel_ == SPIChannel::channel6)
					misoPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::pushPull,
						misoPin_::GPIOAlt::spi6_MISO);
			}

			inline void send(const uint8_t data, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, &data, sizeof(data), blockTime);
			}

			inline void send(const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, data, size, blockTime);
			}
	};


	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_1 = SPIModule<SPIChannel::channel1, sckPin_, mosiPin_, misoPin_, initPins_>;

	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_2 = SPIModule<SPIChannel::channel2, sckPin_, mosiPin_, misoPin_, initPins_>;

	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_3 = SPIModule<SPIChannel::channel3, sckPin_, mosiPin_, misoPin_, initPins_>;

	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_4 = SPIModule<SPIChannel::channel4, sckPin_, mosiPin_, misoPin_, initPins_>;

	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_5 = SPIModule<SPIChannel::channel5, sckPin_, mosiPin_, misoPin_, initPins_>;

	template <typename sckPin_, typename mosiPin_, typename misoPin_, bool initPins_ = true>
	using SPI_6 = SPIModule<SPIChannel::channel6, sckPin_, mosiPin_, misoPin_, initPins_>;

}


#endif // __STM32_halSPI_ex__
