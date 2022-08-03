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

	enum class SPIEvent {
	};

	enum class SPIPin {
		pinSCK,
		pinMISO,
		pinMOSI
	};

	template <SPIChannel channel_, typename gpio_, SPIPin pin_>
	struct SPIPinTrait {
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

			/// \brief Activa el modul
			//
			static void activate() {

				if constexpr (channel == SPIChannel::channel1)
					RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
				if constexpr (channel == SPIChannel::channel2)
					RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
				if constexpr (channel == SPIChannel::channel3)
					RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
				if constexpr (channel == SPIChannel::channel4)
					RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
				if constexpr (channel == SPIChannel::channel5)
					RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
				if constexpr (channel == SPIChannel::channel6)
					RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
			}

			/// \brief Descativa el modul
			///
			static void deactivate() {

				if constexpr (channel == SPIChannel::channel1)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
				if constexpr (channel == SPIChannel::channel2)
					RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
				if constexpr (channel == SPIChannel::channel3)
					RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN;
				if constexpr (channel == SPIChannel::channel4)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI4EN;
				if constexpr (channel == SPIChannel::channel5)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI5EN;
				if constexpr (channel == SPIChannel::channel6)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI5EN;
			}

		public:
			static void initMaster(
				SPIMode mode,
				SPISize size = _defaultSize,
				SPIFirstBit firstBit = _defaultFirstBit) {

				halSPIOptions options =
					HAL_SPI_MS_MASTER |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				init(options);
			}

			static void initSlave(
				SPIMode mode,
				SPISize size = _defaultSize,
				SPIFirstBit firstBit = _defaultFirstBit) {

				halSPIOptions options =
					HAL_SPI_MS_SLAVE |
					halSPIOptions(size) |
					halSPIOptions(firstBit) |
					halSPIOptions(mode);
				init(options);
			}

			static void init(halSPIOptions options) {

				halSPISettings settings;
				settings.channel = halSPIChannel(channel_);
				settings.options = options;
				settings.isrFunction = nullptr;
				settings.isrParams = nullptr;
				_handler = halSPIInitialize(&_data, &settings);
			}

			inline static void init(
				const halSPISettings &settings) {

				_handler = halSPIInitialize(&_data, &settings);
			}
            
            inline static void deInit() {

            	deactivate();
            }

			inline static void setClock(
				SPIClockDivider clkdiv) {

			}

			inline static void setInterruptFunction(
				halSPIInterruptFunction function,
				void *params) {

				halSPISetInterruptFunction(_handler, function, params);
			}

			inline static void enableInterrupts(
				uint32_t events) {

				halSPIEnableInterrupts(_handler, events);
			}

			inline static uint32_t disableInterrupts(
				uint32_t events) {

				return halSPIDisableInterrupts(_handler, events);
			}

			template <typename gpio_>
			inline static void initSCKPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::pinSCK>::alt);
			}

			template <typename gpio_>
			inline static void initMOSIPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::pinMOSI>::alt);
			}

			template <typename gpio_>
			inline static void initMISOPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::pinMISO>::alt);
			}

			inline static void send(
				const uint8_t data,
				unsigned blockTime = _defaultBlockTime) {

				halSPISend(_handler, &data, sizeof(data), blockTime);
			}

			inline static void send(
				const void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				halSPISend(_handler, data, size, blockTime);
			}
	};

	template <SPIChannel channel_> halSPIData SPI_x<channel_>::_data;
	template <SPIChannel channel_> halSPIHandler SPI_x<channel_>::_handler;

	#ifdef SPI1
		using SPI_1 = SPI_x<SPIChannel::channel1>;
	#endif
	#ifdef SPI2
		using SPI_2 = SPI_x<SPIChannel::channel2>;
	#endif
	#ifdef SPI3
		using SPI_3 = SPI_x<SPIChannel::channel3>;
	#endif
	#ifdef SPI4
		using SPI_4 = SPI_x<SPIChannel::channel4>;
	#endif
	#ifdef SPI5
		using SPI_5 = SPI_x<SPIChannel::channel5>;
	#endif
	#ifdef SPI6
		using SPI_6 = SPI_x<SPIChannel::channel6>;
	#endif

	#ifdef SPI1
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_A5, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_A6, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_A7, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_B3, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_B4, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel1, GPIO_B5, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
	#endif

	#ifdef SPI2
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_B10, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_B13, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_B14, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_B15, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_C2, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_C3, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_D3, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_I1, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_I2, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel2, GPIO_I3, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
	#endif

	#ifdef SPI3
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_B3, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_B4, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_B5, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_C10, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_C11, SPIPin::pinMISO> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_C12, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt6;
		};
		template <>
		struct SPIPinTrait<SPIChannel::channel3, GPIO_D6, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
	#endif
}


#endif // __STM32_htlSPI__
