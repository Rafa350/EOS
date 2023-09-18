#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"


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

		enum class ClkPolarity {
			low,
			high
		};

		enum class ClkPhase {
			edge1,
			edge2
		};

		enum class WordSize {
			_8,
			_16
		};

		enum class FirstBit {
			lsb,
			msb
		};

		enum class ClockDivider {
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
				inline void activate() {
					activateImpl();
				}
				inline void deactivate() {
					activateImpl();
				}
			protected:
				SPIDevice(SPI_TypeDef *spi);
				void interruptService();
				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;
			public:
				void initialize(SPIMode mode, ClkPolarity clkPolarity, ClkPhase clkPhase, WordSize size, FirstBit firstBit, ClockDivider clkDivider);
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
				uint16_t transmit(const uint8_t *buffer, uint16_t size);
				uint16_t receive(uint8_t *buffer, uint16_t size);
		};

		typedef SPIDevice * SPIDeviceHandler;


		namespace internal {

			template <DeviceID>
			struct HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct SPIPinFunctionID;
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
				static SPIDeviceX _instance;
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
			public:
				static constexpr SPIDeviceX * getHandler() {
					return &_device;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				template <typename pin_>
				void initSCKPin() {
					gpio::PinFunctionID pinFunctionID = internal::SPIPinFunctionID<deviceID_, PinFunction::sck, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initMOSIPin() {
					gpio::PinFunctionID pinFunctionID = internal::SPIPinFunctionID<deviceID_, PinFunction::mosi, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initMISOPin() {
					gpio::PinFunctionID pinFunctionID = internal::SPIPinFunctionID<deviceID_, PinFunction::miso, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
		};

		template <DeviceID deviceID_>
		SPIDeviceX<deviceID_> SPIDeviceX<deviceID_>::_instance;

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


		namespace internal {

			#ifdef HTL_SPI1_EXIST
			template<>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t spiAddr = SPI1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_SPI1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
				#endif
			};
				#endif

			#ifdef HTL_SPI2_EXIST
			template<>
			struct HardwareInfo<DeviceID::_2> {
				static constexpr uint32_t spiAddr = SPI2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI3_EXIST
			template<>
			struct HardwareInfo<DeviceID::_3> {
				static constexpr uint32_t spiAddr = SPI3_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI4_EXIST
			template<>
			struct HardwareInfo<DeviceID::_4> {
				static constexpr uint32_t spiAddr = SPI4_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI5_EXIST
			template<>
			struct HardwareInfo<DeviceID::_5> {
				static constexpr uint32_t spiAddr = SPI5_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI6_EXIST
			template<>
			struct HardwareInfo<DeviceID::_6> {
				static constexpr uint32_t spiAddr = SPI6_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI6EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI6EN_Pos;
				#endif
			};
			#endif
		}
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlSPI_AF_G030.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlSPI_AF_G031.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/htlSPI_AF_F030.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlSPI_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlSPI_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlSPI__
