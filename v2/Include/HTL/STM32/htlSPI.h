#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class SPIChannel {
		_1,
		_2,
		_3,
		_4,
		_5,
		_6
	};

	enum class SPIMode {
		master,
		slave
	};

	enum class SPIClkPolarity {
		low,
		high
	};

	enum class SPIClkPhase {
		edge1,
		edge2
	};

	enum class SPISize {
		_8,
		_16
	};

	enum class SPIFirstBit {
		lsb,
		msb
	};

	enum class SPIClockDivider {
		_2,
		_4,
		_8,
		_16,
		_32,
		_64,
		_128,
		_256
	};

	enum class SPIEvent {
	};

	enum class SPIPin {
		SCK,
		MISO,
		MOSI
	};

	using SPIInterruptParam = void*;
	using SPIInterruptFunction = void (*)(SPIEvent, SPIInterruptParam);

	void SPI_init(SPI_TypeDef*, SPIMode, SPIClkPolarity, SPIClkPhase, SPISize, SPIFirstBit, SPIClockDivider);
	void SPI_send(SPI_TypeDef*, const void*, int, unsigned);

	template <SPIChannel>
	struct SPITrait {
	};

	template <SPIChannel, typename, SPIPin>
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

				if constexpr (channel == SPIChannel::_1)
					RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
				if constexpr (channel == SPIChannel::_2)
					RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
				if constexpr (channel == SPIChannel::_3)
					RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
				if constexpr (channel == SPIChannel::_4)
					RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
				if constexpr (channel == SPIChannel::_5)
					RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
				if constexpr (channel == SPIChannel::_6)
					RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
			}

			/// \brief Desactiva el modul
			///
			static void deactivate() {

				if constexpr (channel == SPIChannel::_1)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
				if constexpr (channel == SPIChannel::_2)
					RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
				if constexpr (channel == SPIChannel::_3)
					RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN;
				if constexpr (channel == SPIChannel::_4)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI4EN;
				if constexpr (channel == SPIChannel::_5)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI5EN;
				if constexpr (channel == SPIChannel::_6)
					RCC->APB2ENR &= ~RCC_APB2ENR_SPI5EN;
			}

		public:
			static void init(
				SPIMode mode,
				SPIClkPolarity clkPolarity,
				SPIClkPhase clkPhase,
				SPISize size,
				SPIFirstBit firstBit,
				SPIClockDivider clkDivider) {

				activate();
				disable();

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				SPI_init(regs, mode, clkPolarity, clkPhase, size, firstBit, clkDivider);

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
					SPIPinTrait<channel_, gpio_, SPIPin::SCK>::alt);
			}

			template <typename gpio_>
			inline static void initMOSIPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::MOSI>::alt);
			}

			template <typename gpio_>
			inline static void initMISOPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::MISO>::alt);
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

			inline static void receive(
				void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
			}
	};

	template <SPIChannel channel_> SPIInterruptFunction SPI_x<channel_>::_isrFunction;
	template <SPIChannel channel_> SPIInterruptParam SPI_x<channel_>::_isrParam;

	#ifdef SPI1
		using SPI_1 = SPI_x<SPIChannel::_1>;
	#endif
	#ifdef SPI2
		using SPI_2 = SPI_x<SPIChannel::_2>;
	#endif
	#ifdef SPI3
		using SPI_3 = SPI_x<SPIChannel::_3>;
	#endif
	#ifdef SPI4
		using SPI_4 = SPI_x<SPIChannel::_4>;
	#endif
	#ifdef SPI5
		using SPI_5 = SPI_x<SPIChannel::_5>;
	#endif
	#ifdef SPI6
		using SPI_6 = SPI_x<SPIChannel::_6>;
	#endif

	#ifdef SPI1
		template<>
		struct SPITrait<SPIChannel::_1> {
			static constexpr uint32_t addr = SPI1_BASE;
		};

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

	#ifdef SPI2
		template<>
		struct SPITrait<SPIChannel::_2> {
			static constexpr uint32_t addr = SPI2_BASE;
		};

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

	#ifdef SPI3
		template<>
		struct SPITrait<SPIChannel::_3> {
			static constexpr uint32_t addr = SPI3_BASE;
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

	#ifdef SPI4
		template<>
		struct SPITrait<SPIChannel::_4> {
			static constexpr uint32_t addr = SPI4_BASE;
		};
	#endif

	#ifdef SPI5
		template<>
		struct SPITrait<SPIChannel::_5> {
			static constexpr uint32_t addr = SPI5_BASE;
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


#endif // __STM32_htlSPI__
