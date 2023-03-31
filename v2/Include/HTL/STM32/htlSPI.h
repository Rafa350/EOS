#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


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
            static constexpr uint32_t _spiAddr = Trait::spiAddr;
            static constexpr uint32_t _rccEnableAddr = Trait::rccEnableAddr;
            static constexpr uint32_t _rccEnablePos = Trait::rccEnablePos;
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

				uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*p |= 1 << _rccEnablePos;
			}

			/// \brief Desactiva el modul
			///
			static void deactivate() {

				uint32_t *p = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*p &= ~(1 << _rccEnablePos);
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

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
            	regs->CR1 |= SPI_CR1_SPE;
            }

            /// \brief Desabilita el modul.
            ///
            static void disable() {

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

            	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
	           	*((volatile uint8_t*)&regs->DR) = data;
			}

			static void write16(
				uint16_t data) {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
	           	*((volatile uint16_t*)&regs->DR) = data;
			}

			static uint8_t read8() {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
	           	return *((volatile uint8_t*)&regs->DR);
			}

			static uint16_t read16() {

	           	SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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

				SPI_TypeDef *regs = reinterpret_cast<SPI_TypeDef*>(_spiAddr);
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
		static constexpr uint32_t spiAddr = SPI1_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
		static constexpr uint32_t rccEnablePos = RCC_APBENR2_SPI1EN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
		#endif
		static constexpr INTVector vector = INTVector::spi1;
	};
	#endif

	#ifdef HTL_SPI2_EXIST
	template<>
	struct SPITrait<SPIChannel::_2> {
		static constexpr uint32_t spiAddr = SPI2_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
		static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI2EN_Pos;
		#elif defined(EOS_PLATFORM_STM32F4)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
		#endif
		static constexpr INTVector vector = INTVector::spi2;
	};
	#endif

	#ifdef HTL_SPI3_EXIST
	template<>
	struct SPITrait<SPIChannel::_3> {
		static constexpr uint32_t spiAddr = SPI3_BASE;
		static constexpr INTVector vector = INTVector::spi3;
		#if defined(EOS_PLATFORM_STM32F4)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
		#endif
	};
	#endif

	#ifdef HTL_SPI4_EXIST
	template<>
	struct SPITrait<SPIChannel::_4> {
		static constexpr uint32_t spiAddr = SPI4_BASE;
		static constexpr INTVector vector = INTVector::spi4;
		#if defined(EOS_PLATFORM_STM32F4)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
		#endif
	};
	#endif

	#ifdef HTL_SPI5_EXIST
	template<>
	struct SPITrait<SPIChannel::_5> {
		static constexpr uint32_t spiAddr = SPI5_BASE;
		static constexpr INTVector vector = INTVector::spi5;
		#if defined(EOS_PLATFORM_STM32F4)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
		#endif
	};
	#endif
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/htlSPI_AF_G030.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/htlSPI_AF_G031.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/htlSPI_AF_F030.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlSPI_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlSPI_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlSPI__
