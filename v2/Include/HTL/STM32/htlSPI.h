#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halSPI.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

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
	class SPI_x {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;
			constexpr static const SPISize _defaultSize = SPISize::size8;
			constexpr static const SPIFirstBit _defaultFirstBit = SPIFirstBit::lsb;

		private:
		    static halSPIData _data;
			static halSPIHandler _handler;

		public:
			constexpr static const SPIChannel channel = channel_;

		private:
			SPI_x() = delete;
			SPI_x(const SPI_x &) = delete;
			SPI_x(const SPI_x &&) = delete;
            ~SPI_x() = delete;
            
			SPI_x & operator = (const SPI_x &) = delete;
			SPI_x & operator = (const SPI_x &&) = delete;

		public:
			inline static void initMaster(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_MASTER |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				init(options);
			}

			inline static void initSlave(SPIMode mode, SPISize size = _defaultSize, SPIFirstBit firstBit = _defaultFirstBit) {
				halSPIOptions options =
					HAL_SPI_MS_SLAVE |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				init(options);
			}

			inline static void init(halSPIOptions options) {
				halSPISettings settings;
				settings.channel = halSPIChannel(channel_);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline static void init(const halSPISettings &settings) {
				_handler = halSPIInitialize(&_data, &settings);
			}
            
            inline static void deInit() {
            }

			inline static void setClock(SPIClockDivider clkdiv) {

			}

			inline static void setInterruptFunction(halSPIInterruptFunction function, void *params) {
				halSPISetInterruptFunction(_handler, function, params);
			}

			inline static void enableInterrupts(uint32_t events) {
				halSPIEnableInterrupts(_handler, events);
			}

			inline static uint32_t disableInterrupts(uint32_t events) {
				return halSPIDisableInterrupts(_handler, events);
			}

			template <typename gpio_>
			inline static void initSCKPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi1_SCK);

				if constexpr (channel_ == SPIChannel::channel2)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi2_SCK);

				if constexpr (channel_ == SPIChannel::channel3)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi3_SCK);

				if constexpr (channel_ == SPIChannel::channel4)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi4_SCK);

				if constexpr (channel_ == SPIChannel::channel5)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi5_SCK);

				if constexpr (channel_ == SPIChannel::channel6)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi6_SCK);
			}

			template <typename gpio_>
			inline static void initMOSIPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi1_MOSI);

				if constexpr (channel_ == SPIChannel::channel2)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi2_MOSI);

				if constexpr (channel_ == SPIChannel::channel3)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi3_MOSI);

				if constexpr (channel_ == SPIChannel::channel4)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi4_MOSI);

				if constexpr (channel_ == SPIChannel::channel5)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi5_MOSI);

				if constexpr (channel_ == SPIChannel::channel6)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi6_MOSI);

			}

			template <typename gpio_>
			inline static void initMISOPin() {
				if constexpr (channel_ == SPIChannel::channel1)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi1_MISO);

				if constexpr (channel_ == SPIChannel::channel2)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi2_MISO);

				if constexpr (channel_ == SPIChannel::channel3)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi3_MISO);

				if constexpr (channel_ == SPIChannel::channel4)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi4_MISO);

				if constexpr (channel_ == SPIChannel::channel5)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi5_MISO);

				if constexpr (channel_ == SPIChannel::channel6)
					gpio_::initAlt(
						GPIODriver::pushPull,
						GPIOSpeed::fast,
						gpio_::GPIOAlt::spi6_MISO);
			}

			inline static void send(const uint8_t data, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, &data, sizeof(data), blockTime);
			}

			inline static void send(const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				halSPISend(_handler, data, size, blockTime);
			}
	};

	template <SPIChannel channel_> halSPIData SPI_x<channel_>::_data;
	template <SPIChannel channel_> halSPIHandler SPI_x<channel_>::_handler;

	using SPI_1 = SPI_x<SPIChannel::channel1>;
	using SPI_2 = SPI_x<SPIChannel::channel2>;
	using SPI_3 = SPI_x<SPIChannel::channel3>;
	using SPI_4 = SPI_x<SPIChannel::channel4>;
	using SPI_5 = SPI_x<SPIChannel::channel5>;
	using SPI_6 = SPI_x<SPIChannel::channel6>;
}


#endif // __STM32_htlSPI__
