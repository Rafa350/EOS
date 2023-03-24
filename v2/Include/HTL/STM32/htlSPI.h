#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


#if defined(EOS_PLATFORM_STM32G0)
	namespace htl {
		#ifdef HTL_SPI1_EXIST
			inline void SPI1ClockEnable() {
				RCC->APBENR2 |= RCC_APBENR2_SPI1EN;
			}
			inline void SPI1ClockDisable() {
				RCC->APBENR2 &= ~RCC_APBENR2_SPI1EN;
			}
			inline void SPI1Reset() {
			}
		#endif
		#ifdef HTL_SPI2_EXIST
			inline void SPI2ClockEnable() {
				RCC->APBENR1 |= RCC_APBENR1_SPI2EN;
			}
			inline void SPI2ClockDisable() {
				RCC->APBENR1 &= ~RCC_APBENR1_SPI2EN;
			}
			inline void SPI2Reset() {
			}
		#endif
		#ifdef HTL_SPI3_EXIST
			inline void SPI3ClockEnable() {
				RCC->APBENR1 |= RCC_APBENR1_SPI3EN;
			}
			inline void SPI3ClockDisable() {
				RCC->APBENR1 &= ~RCC_APBENR1_SPI3EN;
			}
			inline void SPI3Reset() {
			}
		#endif
		#ifdef HTL_SPI4_EXIST
			inline void SPI4ClockEnable() {
				RCC->APBENR1 |= RCC_APBENR1_SPI4EN;
			}
			inline void SPI4ClockDisable() {
				RCC->APBENR1 &= ~RCC_APBENR1_SPI4EN;
			}
			inline void SPI4Reset() {
			}
		#endif
	}
    
#elif defined(EOS_PLATFORM_STM32F0)
	namespace htl {
		#ifdef HTL_SPI1_EXIST
			inline void SPI1ClockEnable() {
				RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
			}
			inline void SPI1ClockDisable() {
				RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
			}
			inline void SPI1Reset() {
			}
		#endif
		#ifdef HTL_SPI2_EXIST
			inline void SPI2ClockEnable() {
				RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
			}
			inline void SPI2ClockDisable() {
				RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
			}
			inline void SPI2Reset() {
			}
		#endif
	}

#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#ifdef HTL_SPI1_EXIST
		inline void SPI1ClockEnable() {
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		}
		inline void SPI1ClockDisable() {
			RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
		}
		inline void SPI1Reset() {
		}
	#endif
	#ifdef HTL_SPI2_EXIST
		inline void SPI2ClockEnable() {
			RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		}
		inline void SPI2ClockDisable() {
			RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
		}
		inline void SPI2Reset() {
		}
	#endif
	#ifdef HTL_SPI3_EXIST
		inline void SPI3ClockEnable() {
			RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
		}
		inline void SPI3ClockDisable() {
			RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN;
		}
		inline void SPI3Reset() {
		}
	#endif
	#ifdef HTL_SPI4_EXIST
		inline void SPI4ClockEnable() {
			RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
		}
		inline void SPI4ClockDisable() {
			RCC->APB2ENR &= ~RCC_APB2ENR_SPI4EN;
		}
		inline void SPI4Reset() {
		}
	#endif
	#ifdef HTL_SPI5_EXIST
		inline void SPI5ClockEnable() {
			RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
		}
		inline void SPI5ClockDisable() {
			RCC->APB2ENR &= ~RCC_APB2ENR_SPI5EN;
		}
		inline void SPI5Reset() {
		}
	#endif
	#ifdef HTL_SPI6_EXIST
		inline void SPI6ClockEnable() {
			RCC->APB2ENR |= RCC_APB2ENR_SPI6EN;
		}
		inline void SPI6ClockDisable() {
			RCC->APB2ENR &= ~RCC_APB2ENR_SPI6EN;
		}
		inline void SPI6Reset() {
		}
	#endif
    
#else
	#error "Unknown platform"
#endif


namespace htl {

	enum class SPIChannel {
		#ifdef HTL_SPI1_EXIST
			_1,
		#endif
		#ifdef HTL_SPI2_EXIST
			_2,
	    #endif
		#ifdef HTL_SPI3_EXIST
			_3,
		#endif
		#ifdef HTL_SPI4_EXIST
			_4,
		#endif
		#ifdef HTL_SPI5_EXIST
			_5,
		#endif
		#ifdef HTL_SPI6_EXIST
			_6
		#endif
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

	enum class SPIInterrupt {
		txEmpty,
		rxNotEmpty,
		error
	};

	enum class SPIFlag {
		txEmpty,
		rxNotEmpty,
		busy,
		fault,
		crc,
		overrun
	};

	enum class SPIPin {
		SCK,
		MISO,
		MOSI
	};

	using SPIInterruptParam = void*;
	using SPIInterruptFunction = void (*)(SPIInterruptParam);

	template <SPIChannel>
	struct SPITrait {
	};

	template <SPIChannel, typename, SPIPin>
	struct SPIPinTrait {
	};

	class SPIBase_x {
		protected:
			static void initialize(SPI_TypeDef *regs, SPIMode mode, SPIClkPolarity clkPolarity, SPIClkPhase clkPhase, SPISize size, SPIFirstBit fistBit, SPIClockDivider clkDivider);
			static void send(SPI_TypeDef *regs, const uint8_t *data, unsigned dataLength, unsigned timeout);
	};

	template <SPIChannel channel_>
	class SPI_x final: SPIBase_x {
		private:
			using Trait = SPITrait<channel_>;
            static constexpr uint32_t _addr = Trait::addr;
			static constexpr unsigned _defaultTimeout = 1000;

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

				#ifdef HTL_SPI1_EXIST
					if constexpr (channel == SPIChannel::_1)
						SPI1ClockEnable();
				#endif
				#ifdef HTL_SPI2_EXIST
					if constexpr (channel == SPIChannel::_2)
						SPI2ClockEnable();
				#endif
				#ifdef HTL_SPI3_EXIST
					if constexpr (channel == SPIChannel::_3)
						SPI3ClockEnable();
				#endif
				#ifdef HTL_SPI4_EXIST
					if constexpr (channel == SPIChannel::_4)
						SPI4ClockEnable();
				#endif
				#ifdef HTL_SPI5_EXIST
					if constexpr (channel == SPIChannel::_5)
						SPI5ClockEnable();
				#endif
				#ifdef HTL_SPI6_EXIST
					if constexpr (channel == SPIChannel::_6)
						SPI6ClockEnable();
				#endif
			}

			/// \brief Desactiva el modul
			///
			static void deactivate() {

				#ifdef HTL_SPI1_EXIST
					if constexpr (channel == SPIChannel::_1)
						SPI1ClockDisable();
				#endif
				#ifdef HTL_SPI2_EXIST
					if constexpr (channel == SPIChannel::_2)
						SPI2ClockDisable();
				#endif
				#ifdef HTL_SPI3_EXIST
					if constexpr (channel == SPIChannel::_3)
						SPI3ClockDisable();
				#endif
				#ifdef HTL_SPI4_EXIST
					if constexpr (channel == SPIChannel::_4)
						SPI4ClockDisable();
				#endif
				#ifdef HTL_SPI5_EXIST
					if constexpr (channel == SPIChannel::_5)
						SPI5ClockDisable();
				#endif
				#ifdef HTL_SPI6_EXIST
					if constexpr (channel == SPIChannel::_6)
						SPI6ClockDisable();
				#endif
			}

		public:
			static void initialize(
				SPIMode mode,
				SPIClkPolarity clkPolarity,
				SPIClkPhase clkPhase,
				SPISize size,
				SPIFirstBit firstBit,
				SPIClockDivider clkDivider) {

				_isrFunction = nullptr;
				_isrParam = nullptr;

				activate();
				disable();

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				SPIBase_x::initialize(regs, mode, clkPolarity, clkPhase, size, firstBit, clkDivider);

				enable();
			}
            
			/// \brief Desinicialitza el modul.
			///
            static void deinitialize() {

            	disable();
            	deactivate();
            }

            /// \brief Reseteja el modul
            ///
            static void reset() {

				_isrFunction = nullptr;
				_isrParam = nullptr;
            }

            /// \brief Habilita el modul
            //
            static void enable() {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
            	regs->CR1 |= SPI_CR1_SPE;
            }

            /// \brief Desabilita el modul.
            ///
            static void disable() {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
            	while ((regs->SR & SPI_SR_BSY) != 0)
            		continue;
            	regs->CR1 &= ~SPI_CR1_SPE;
            }

            /// \brief Asigna la funcio d'interrupcio.
            /// \param function: La funcio.
            /// \param param: El parametre.
            ///
			static void setInterruptFunction(
				SPIInterruptFunction function,
				SPIInterruptParam param) {

				_isrFunction = function;
				_isrParam = param;
			}

			/// \brief Habilita la generacio d'interrupcions.
			/// \param interrupt: La interrupcio a habilitar.
			///
			static void enableInterrupt(
				SPIInterrupt interrupt) {

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				switch (interrupt) {
					case SPIInterrupt::txEmpty:
						regs->CR2 |= SPI_CR2_TXEIE;
						break;

					case SPIInterrupt::rxNotEmpty:
						regs->CR2 |= SPI_CR2_RXNEIE;
						break;

					case SPIInterrupt::error:
						regs->CR2 |= SPI_CR2_ERRIE;
						break;
				}
			}

			/// \brief Desabilita la generacio d'interrupcions.
			/// \param interrupt: La interrupcio a deshabilitar.
			///
			static bool disableInterrupt(
				SPIInterrupt interrupt) {

				bool state = false;

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				switch (interrupt) {
					case SPIInterrupt::txEmpty:
						state = (regs->CR2 & SPI_CR2_TXEIE) != 0;
						regs->CR2 |= SPI_CR2_TXEIE;
						break;

					case SPIInterrupt::rxNotEmpty:
						state = (regs->CR2 & SPI_CR2_RXNEIE) != 0;
						regs->CR2 |= SPI_CR2_RXNEIE;
						break;

					case SPIInterrupt::error:
						state = (regs->CR2 & SPI_CR2_ERRIE) != 0;
						regs->CR2 |= SPI_CR2_ERRIE;
						break;
				}

				return state;
			}

			/// \brief Obte el valor d'un flag.
			/// \param flag: El flag.
			/// \return El valor del flag.
			///
			static bool getFlag(
				SPIFlag flag) {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				switch (flag) {
					case SPIFlag::txEmpty:
						return (regs->SR & SPI_SR_TXE) != 0;

					case SPIFlag::rxNotEmpty:
						return (regs->SR & SPI_SR_RXNE) != 0;

					case SPIFlag::busy:
						return (regs->SR & SPI_SR_BSY) != 0;

					default:
						return false;
				}
			}

			static bool isTxEmpty() {

				return getFlag(SPIFlag::txEmpty);
			}

			static bool isRxNotEmpty() {

				return getFlag(SPIFlag::rxNotEmpty);
			}

			static bool isBusy() {

				return getFlag(SPIFlag::busy);
			}

			static void clearFlag(
				SPIFlag flag) {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				switch (flag) {
				}
			}

			static void interruptHandler() {

				if (_isrFunction != nullptr)
					_isrFunction(_isrParam);
			}

			template <typename gpio_>
			static void initSCKPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::SCK>::alt);
			}

			template <typename gpio_>
			static void initMOSIPin() {
				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::MOSI>::alt);
			}

			template <typename gpio_>
			static void initMISOPin() {

				gpio_::initAlt(
					GPIODriver::pushPull,
					GPIOSpeed::fast,
					SPIPinTrait<channel_, gpio_, SPIPin::MISO>::alt);
			}

			static void write8(
				uint8_t data) {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
	           	*((volatile uint8_t*)&regs->DR) = data;
			}

			static void write16(
				uint16_t data) {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
	           	*((volatile uint16_t*)&regs->DR) = data;
			}

			static uint8_t read8() {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
	           	return *((volatile uint8_t*)&regs->DR);
			}

			static uint16_t read16() {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
	           	return *((volatile uint16_t*)&regs->DR);
			}

			static void send(
				const uint8_t data,
				unsigned timeout = _defaultTimeout) {

				send(&data, sizeof(data), timeout);
			}

			static void send(
				const uint8_t *data,
				unsigned dataLength,
				unsigned timeout = _defaultTimeout) {

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_addr);
				SPIBase_x::send(regs, data, dataLength, timeout);
			}
	};

	template <SPIChannel channel_> SPIInterruptFunction SPI_x<channel_>::_isrFunction;
	template <SPIChannel channel_> SPIInterruptParam SPI_x<channel_>::_isrParam;

	#ifdef HTL_SPI1_EXIST
		using SPI_1 = SPI_x<SPIChannel::_1>;
	#endif
	#ifdef HTL_SPI2_EXIST
		using SPI_2 = SPI_x<SPIChannel::_2>;
	#endif
	#ifdef HTL_SPI3_EXIST
		using SPI_3 = SPI_x<SPIChannel::_3>;
	#endif
	#ifdef HTL_SPI4_EXIST
		using SPI_4 = SPI_x<SPIChannel::_4>;
	#endif
	#ifdef HTL_SPI5_EXIST
		using SPI_5 = SPI_x<SPIChannel::_5>;
	#endif
	#ifdef HTL_SPI6_EXIST
		using SPI_6 = SPI_x<SPIChannel::_6>;
	#endif

	#ifdef HTL_SPI1_EXIST
		template<>
		struct SPITrait<SPIChannel::_1> {
			static constexpr uint32_t addr = SPI1_BASE;
			static constexpr INTVector vector = INTVector::spi1;
		};

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


#endif // __STM32_htlSPI__
