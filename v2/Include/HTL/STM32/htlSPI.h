#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


namespace htl {

	namespace spi {

		enum class DeviceID {
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

		enum class PinFunction {
			sck,
			miso,
			mosi
		};

		using SPIInterruptParam = void*;
		using SPIInterruptFunction = void (*)(SPIInterruptParam);


		class SPIDevice {
			private:
				SPI_TypeDef * const _spi;
			private:
				SPIDevice(const SPIDevice &) = delete;
				SPIDevice & operator = (const SPIDevice &) = delete;
			protected:
				SPIDevice(SPI_TypeDef *spi);
				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;
				virtual void resetImpl() = 0;
			public:
				inline void activate() {
					activateImpl();
				}
				inline void deactivate() {
					activateImpl();
				}
				inline void reset() {
					resetImpl();
				}
				void initialize(SPIMode mode, SPIClkPolarity clkPolarity, SPIClkPhase clkPhase, SPISize size, SPIFirstBit firstBit, SPIClockDivider clkDivider);
				void deinitialize();
				inline void enable() {
					_spi->CR1 |= SPI_CR1_SPE;
				}
				inline void disable() {
					_spi->CR1 &= ~SPI_CR1_SPE;
				}
				inline void write8(uint8_t data) {
					*((volatile uint8_t*)&_spi->DR) = data;
				}
				inline void write16(uint16_t data) {
					*((volatile uint16_t*)&_spi->DR) = data;
				}
				inline bool isTxEmpty() const {
					return (_spi->SR & SPI_SR_TXE) != 0;
				}
				inline bool isRxNotEmpty() const {
					return (_spi->SR & SPI_SR_RXNE) != 0;
				};
				inline bool isBusy() const {
					return (_spi->SR & SPI_SR_BSY) != 0;
				}
				void interruptService();
		};

		typedef SPIDevice* SPIDeviceHandler;


		namespace internal {

			template <DeviceID>
			struct HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct SPIAltFunction;
		}

		template <DeviceID deviceID_>
		class SPIDeviceX final: public SPIDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _spiAddr = HI::spiAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static constexpr uint32_t _rccResetAddr = HI::rccResetAddr;
				static constexpr uint32_t _rccResetPos = HI::rccResetPos;
				static SPIDeviceX _device;
			public:
				static constexpr DeviceID deviceID = deviceID_;
			private:
				SPIDeviceX() :
					SPIDevice(reinterpret_cast<SPI_TypeDef *>(_spiAddr)) {
				}
			protected:
				void activateImpl() {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivateImpl() {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
				void resetImpl() {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccResetAddr);
					*p |= 1 << _rccResetPos;
					*p &= ~(1 << _rccResetPos);
				}
			public:
				inline static SPIDeviceX * getHandler() {
					return &_device;
				}
				template <typename pin_>
				void initSCKPin() {
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::sck, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
				}
				template <typename pin_>
				void initMOSIPin() {
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::mosi, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
				}
				template <typename pin_>
				void initMISOPin() {
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::miso, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
				}
		};

		template <DeviceID deviceID_>
		SPIDeviceX<deviceID_> SPIDeviceX<deviceID_>::_device;

		#ifdef HTL_SPI1_EXIST
		typedef SPIDeviceX<DeviceID::_1> SPIDevice1;
		#endif
		#ifdef HTL_SPI2_EXIST
		typedef SPIDeviceX<DeviceID::_2> SPIDevice2;
		#endif
		#ifdef HTL_SPI3_EXIST
		typedef SPIDeviceX<DeviceID::_3> SPIDevice3;
		#endif
		#ifdef HTL_SPI4_EXIST
		typedef SPIDeviceX<DeviceID::_4> SPIDevice4;
		#endif
		#ifdef HTL_SPI5_EXIST
		typedef SPIDeviceX<DeviceID::_5> SPIDevice5;
		#endif
		#ifdef HTL_SPI6_EXIST
		typedef SPIDeviceX<DeviceID::_6> SPIDevice6;
		#endif
/*
		class SPIBase_x {
			protected:
				static void initialize(SPI_TypeDef *regs, SPIMode mode, SPIClkPolarity clkPolarity, SPIClkPhase clkPhase, SPISize size, SPIFirstBit fistBit, SPIClockDivider clkDivider);
				static void send(SPI_TypeDef *regs, const uint8_t *data, unsigned dataLength, unsigned timeout);
		};

		template <DeviceID deviceID_>
		class SPI_x final: SPIBase_x {
			private:
				using Trait = internal::HardwareInfo<deviceID_>;
				static constexpr uint32_t _spiAddr = Trait::spiAddr;
				static constexpr uint32_t _rccEnableAddr = Trait::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = Trait::rccEnablePos;
				static constexpr unsigned _defaultTimeout = 1000;

			private:
				static SPIInterruptFunction _isrFunction;
				static SPIInterruptParam _isrParam;

			public:
				constexpr static const DeviceID channel = deviceID_;

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

				template <typename pin_>
				static void initSCKPin() {
					gpio::PinHandler handler = pin_::getHandler();
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::sck, pin_>::alt;
					handler->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
				}

				template <typename pin_>
				static void initMOSIPin() {
					gpio::PinHandler handler = pin_::getHandler();
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::mosi, pin_>::alt;
					handler->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
				}

				template <typename pin_>
				static void initMISOPin() {
					gpio::PinHandler handler = pin_::getHandler();
					gpio::GPIOAlt alt = internal::SPIAltFunction<deviceID_, PinFunction::miso, pin_>::alt;
					handler->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, alt);
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

		template <DeviceID deviceID_> SPIInterruptFunction SPI_x<deviceID_>::_isrFunction;
		template <DeviceID deviceID_> SPIInterruptParam SPI_x<deviceID_>::_isrParam;

		#ifdef HTL_SPI1_EXIST
		using SPI_1 = SPI_x<DeviceID::_1>;
		#endif
		#ifdef HTL_SPI2_EXIST
		using SPI_2 = SPI_x<DeviceID::_2>;
		#endif
		#ifdef HTL_SPI3_EXIST
		using SPI_3 = SPI_x<DeviceID::_3>;
		#endif
		#ifdef HTL_SPI4_EXIST
		using SPI_4 = SPI_x<DeviceID::_4>;
		#endif
		#ifdef HTL_SPI5_EXIST
		using SPI_5 = SPI_x<DeviceID::_5>;
		#endif
		#ifdef HTL_SPI6_EXIST
		using SPI_6 = SPI_x<DeviceID::_6>;
		#endif
*/
		namespace internal {

			#ifdef HTL_SPI1_EXIST
			template<>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t spiAddr = SPI1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_SPI1EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR2);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR2_SPI1RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB2RSTR_SPI1RST_Pos;
				#endif
				static constexpr INTVector vector = INTVector::spi1;
			};
			#endif

			#ifdef HTL_SPI2_EXIST
			template<>
			struct HardwareInfo<DeviceID::_2> {
				static constexpr uint32_t spiAddr = SPI2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI2EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR1_SPI2RST_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_SPI2RST_Pos;
				#endif
				static constexpr INTVector vector = INTVector::spi2;
			};
			#endif

			#ifdef HTL_SPI3_EXIST
			template<>
			struct HardwareInfo<DeviceID::_3> {
				static constexpr uint32_t spiAddr = SPI3_BASE;
				static constexpr INTVector vector = INTVector::spi3;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB1RSTR_SPI3RST_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI4_EXIST
			template<>
			struct HardwareInfo<DeviceID::_4> {
				static constexpr uint32_t spiAddr = SPI4_BASE;
				static constexpr INTVector vector = INTVector::spi4;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB2RSTR_SPI4RST_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI5_EXIST
			template<>
			struct HardwareInfo<DeviceID::_5> {
				static constexpr uint32_t spiAddr = SPI5_BASE;
				static constexpr INTVector vector = INTVector::spi5;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR);
				static constexpr uint32_t rccResetPos = RCC_APB2RSTR_SPI5RST_Pos;
				#endif
			};
			#endif

		}
	}
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
