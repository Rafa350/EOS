#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "eos.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class SPIChannel {
		channel1,
		channel2,
		channel3,
		channel4,
		channel5,
		channel6
	};

	enum class SPIMode {
		mode0,
		mode1,
		mode2,
		mode3,
	};

	enum class SPISize {
		size8,
		size16
	};

	enum class SPIFirstBit {
		lsb,
		msb
	};

	enum class SPIClockDivider {
		clkdiv_2,
		clkdiv_4,
		clkdiv_8,
		clkdiv_16,
		clkdiv_32,
		clkdiv_64,
		clkdiv_128,
		clkdiv_256
	};

	enum class SPIEvent {
	};

	enum class SPIPin {
		pinSCK,
		pinMISO,
		pinMOSI
	};

	using SPIInterruptParam = void*;
	using SPIInterruptFunction = void (*)(SPIEvent, SPIInterruptParam);

	void SPI_initMaster(SPI_TypeDef*, SPIMode, SPISize, SPIFirstBit, SPIClockDivider);
	void SPI_send(SPI_TypeDef*, const void*, int, unsigned);

	template <SPIChannel channel_>
	struct SPITrait {
	};

	template <SPIChannel channel_, typename gpio_, SPIPin pin_>
	struct SPIPinTrait {
	};

	template <SPIChannel channel_>
	class SPI_x {
		private:
			using Trait = SPITrait<channel_>;
            static constexpr uint32_t _addr = Trait::addr;
			static constexpr unsigned _defaultBlockTime = 1000;

		private:
			static SPIInterruptFunction _isrFunction;
			static SPIInterruptParam _isrParam;

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

			/// \brief Desactiva el modul
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
				SPISize size,
				SPIFirstBit firstBit,
				SPIClockDivider clkDivider) {

				activate();
				disable();

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				SPI_initMaster(regs, mode, size, firstBit, clkDivider);

				enable();
			}
            
			/// \brief Desinicialitza el modul.
			///
            static void deInit() {

            	disable();
            	deactivate();
            }

            /// \brief Habilita el modul
            //
            inline static void enable() {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
            	regs->CR1 |= SPI_CR1_SPE;
            }

            /// \brief Desabilita el modul.
            ///
            inline static void disable() {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
            	regs->CR1 &= ~SPI_CR1_SPE;
            }

			static void setInterruptFunction(
				SPIInterruptFunction function,
				SPIInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
			}

			static void enableInterrupt(
				SPIEvent events) {

			}

			static bool disableInterrupt(
				SPIEvent events) {

				return true;
			}

			static void InterruptHandler(
				SPIEvent event) {

				if (_isrFunction != nullptr)
					_isrFunction(event, _isrParam);
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

				send(&data, sizeof(data), blockTime);
			}

			inline static void send(
				const void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				SPI_send(regs, data, size, blockTime);
			}
	};

	template <SPIChannel channel_> SPIInterruptFunction SPI_x<channel_>::_isrFunction;
	template <SPIChannel channel_> SPIInterruptParam SPI_x<channel_>::_isrParam;

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
		template<>
		struct SPITrait<SPIChannel::channel1> {
			static constexpr uint32_t addr = SPI1_BASE;
		};

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
		template<>
		struct SPITrait<SPIChannel::channel2> {
			static constexpr uint32_t addr = SPI2_BASE;
		};

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
		template<>
		struct SPITrait<SPIChannel::channel3> {
			static constexpr uint32_t addr = SPI3_BASE;
		};

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

	#ifdef SPI4
		template<>
		struct SPITrait<SPIChannel::channel4> {
			static constexpr uint32_t addr = SPI4_BASE;
		};
	#endif

	#ifdef SPI5
		template<>
		struct SPITrait<SPIChannel::channel5> {
			static constexpr uint32_t addr = SPI5_BASE;
		};

		template <>
		struct SPIPinTrait<SPIChannel::channel5, GPIO_F7, SPIPin::pinSCK> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};

		template <>
		struct SPIPinTrait<SPIChannel::channel5, GPIO_F9, SPIPin::pinMOSI> {
			static constexpr GPIOAlt alt = GPIOAlt::alt5;
		};
	#endif
}


#endif // __STM32_htlSPI__
