#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


#include "HTL/htl.h"


#ifdef HTL_SPIx_EXIST


// HTL main includes
//
#include "HTL/htlDevice.h"
#include "HTL/htlBits.h"
#include "HTL/STM32/htl.h"


// Default options
//
#ifndef HTL_SPI_OPTION_IRQ
    #define HTL_SPI_OPTION_IRQ HTL_SPI_DEFAULT_OPTION_IT
#endif

#ifndef HTL_SPI_OPTION_DMA
    #define HTL_SPI_OPTION_DMA HTL_SPI_DEFAULT_OPTION_DMA
#endif

#ifndef HTL_SPI_OPTION_DEACTIVATE
    #define HTL_SPI_OPTION_DEACTIVATE HTL_SPI_DEFAULT_OPTION_DEACTIVATE
#endif


// HTL includes
//
#include "HTL/STM32/htlGPIO.h"
#if HTL_SPI_OPTION_DMA == 1
#include "HTL/STM32/htlDMA.h"
#endif


namespace htl {

	namespace spi {

		enum class DeviceID {
#ifdef HTL_SPI1_EXIST
			spi1,
#endif
#ifdef HTL_SPI2_EXIST
			spi2,
#endif
#ifdef HTL_SPI3_EXIST
			spi3,
#endif
#ifdef HTL_SPI4_EXIST
			spi4,
#endif
#ifdef HTL_SPI5_EXIST
			spi5,
#endif
#ifdef HTL_SPI6_EXIST
			spi6
#endif
		};

		enum class Mode {
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
			ws8,
			ws16
		};

		enum class FirstBit {
			lsb,
			msb
		};

		enum class ClockDivider {
			div2,
			div4,
			div8,
			div16,
			div32,
			div64,
			div128,
			div256
		};

		enum class PinFunction {
			sck,
			miso,
			mosi
		};

		class SPIDevice: Device {
			public:
                enum class NotificationID {
        		    null,
        		    completed,
        		    error
        		};
                struct NotificationEventArgs {
                	NotificationID const id;
                    bool const irq;
                };
                using NotificationEventRaiser = eos::EventRaiser<SPIDevice, NotificationEventArgs>;
                using INotificationEvent = NotificationEventRaiser::IEvent;
                template <typename Instance_> using NotificationEvent = NotificationEventRaiser::Event<Instance_>;

                enum class State {
					reset,
					ready,
					transmiting
				};

			private:
				SPI_TypeDef * const _spi;
				State _state;
				NotificationEventRaiser _erNotification;

			private:
				void activate() const {
					activateImpl();
				}
#if HTL_SPI_OPTION_DEACTIVATE == 1
				void deactivate() const {
					deactivateImpl();
				}
#endif

			protected:
				SPIDevice(SPI_TypeDef *spi);

				eos::Result initialize(Mode mode, ClkPolarity clkPolarity,
				        ClkPhase clkPhase, WordSize size, FirstBit firstBit,
				        ClockDivider clkDivider);

				void interruptService();

				virtual void activateImpl() const = 0;
#if HTL_SPI_OPTION_DEACTIVATE == 1
				virtual void deactivateImpl() const = 0;
#endif

				void enable() const;
				void disable() const;

				void setClockDivider(ClockDivider clkDivider) const;
				void setMode(Mode mode) const;
				void setClkPolarity(ClkPolarity polarity) const;
				void setClkPhase(ClkPhase phase) const;
				void setWordSize(WordSize size) const;
				void setFirstBit(FirstBit firstBit) const;

				void write8(uint8_t data) const;
				void write16(uint16_t data) const;
				uint8_t read8() const;
				uint16_t read16() const;

				bool isTxEmpty() const;
				bool isRxNotEmpty() const;
				bool isSPIBusy() const;
				bool waitNotBusy(unsigned expireTime) const;
				bool waitRxNotEmpty(unsigned expireTime) const;
				bool waitTxEmpty(unsigned expireTime) const;
#if defined(EOS_PLATFORM_STM32G0) || defined(EOS_PLATFORM_STM32F7)
				bool waitRxFifoEmpty(unsigned expireTime) const;
				bool waitTxFifoEmpty(unsigned expireTime) const;
#endif

			public:
				virtual ~SPIDevice() = default;
				eos::Result initMaster(ClkPolarity clkPolarity,
                        ClkPhase clkPhase, WordSize size, FirstBit firstBit,
                        ClockDivider clkDivider) {
				    return initialize(Mode::master, clkPolarity, clkPhase,
				            size, firstBit, clkDivider);
				}
#if HTL_SPI_OPTION_DEACTIVATE == 1
				eos::Result deinitialize();
#endif

				void setNotificationEvent(INotificationEvent &event, bool enabled = true) {
					_erNotification.set(event, enabled);
				}
				void enableNotificationEvent() {
					_erNotification.enable();
				}
				void disableNotificationEvent() {
					_erNotification.disable();
				}

				eos::Result transmit(const uint8_t *txBuffer, uint8_t *rxBuffer,
				        unsigned bufferSize, unsigned timeout);
				eos::Result receive(uint8_t *rxBuffer, unsigned bufferSize,
				        unsigned timeout)  {
					return transmit(nullptr, rxBuffer, bufferSize, timeout);
				}
                eos::Result transmit(const uint8_t *txBuffer, unsigned bufferSize,
                        unsigned timeout) {
                    return transmit(txBuffer, nullptr, bufferSize, timeout);
                }

#if HTL_SPI_OPTION_DMA == 1
                eos::Result transmit_DMA(htl::dma::DMADevice *devTxDMA,
                        const uint8_t *txBuffer, unsigned bufferSize);
#endif
                State getState() const { return _state; }
				bool isReady() const { return _state == State::ready; }
				bool isBusy() const { return _state != State::ready; }
		};


		namespace internal {

			template <DeviceID>
			struct SPITraits;

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;
		}

		template <DeviceID deviceID_>
		class SPIDeviceX final: public SPIDevice {
			private:
				using SPITraits = internal::SPITraits<deviceID_>;
				template <PinFunction pinFunction_, gpio::PortID portID_, gpio::PinID pinID_> using SPIPins = internal::PinFunctionInfo<deviceID_, pinFunction_, portID_, pinID_>;

			private:
				static constexpr auto _spiAddr = SPITraits::spiAddr;
				static constexpr auto _activateAddr = SPITraits::activateAddr;
				static constexpr auto _activatePos = SPITraits::activatePos;
				static SPIDeviceX _instance;

			public:
				static constexpr auto deviceID = deviceID_;
				static constexpr SPIDeviceX *pInst = &_instance;
				static constexpr SPIDeviceX &rInst = _instance;

			private:
				SPIDeviceX() :
					SPIDevice(reinterpret_cast<SPI_TypeDef *>(_spiAddr)) {
				}

			protected:
				void activateImpl() const override {
					auto p = reinterpret_cast<uint32_t *>(_activateAddr);
					bits::set(*p, 1UL << _activatePos);
					__DSB();
				}
#if HTL_SPI_OPTION_DEACTIVATE == 1
				void deactivateImpl() const override {
					auto p = reinterpret_cast<uint32_t *>(_activateAddr);
					bits::clear(*p, 1UL << _activatePos);
				}
#endif

			public:
				static void interruptHandler() {
					_instance.interruptService();
				}

				template <typename pin_>
				void initPinSCK() {
				    auto af = SPIPins<PinFunction::sck, pin_::portID, pin_::pinID>::value;
				    gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void initPinMOSI() {
					auto af = SPIPins<PinFunction::mosi, pin_::portID, pin_::pinID>::value;
					gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void initPinMISO() {
					auto af = SPIPins<PinFunction::miso, pin_::portID, pin_::pinID>::value;
					gpio::GPIOPin<pin_::portID, pin_::pinID>::initAlternate(gpio::OutputType::pushPull, gpio::PullUpDown::none, gpio::Speed::fast, af);
				}
		};

		template <DeviceID deviceID_>
		SPIDeviceX<deviceID_> SPIDeviceX<deviceID_>::_instance;

#ifdef HTL_SPI1_EXIST
		typedef SPIDeviceX<DeviceID::spi1> SPIDevice1;
#endif
#ifdef HTL_SPI2_EXIST
		typedef SPIDeviceX<DeviceID::spi2> SPIDevice2;
#endif
#ifdef HTL_SPI3_EXIST
		typedef SPIDeviceX<DeviceID::spi3> SPIDevice3;
#endif
#ifdef HTL_SPI4_EXIST
		typedef SPIDeviceX<DeviceID::spi4> SPIDevice4;
#endif
#ifdef HTL_SPI5_EXIST
		typedef SPIDeviceX<DeviceID::spi5> SPIDevice5;
#endif
#ifdef HTL_SPI6_EXIST
		typedef SPIDeviceX<DeviceID::spi6> SPIDevice6;
	#endif

	}
}



#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/G030/htlSPI_Pins.h"
	#include "htl/STM32/G0/htlSPI_Traits.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/G031/htlSPI_Pins.h"
	#include "htl/STM32/G0/htlSPI_Traits.h"

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/G071/htlSPI_Pins.h"
	#include "htl/STM32/G0/htlSPI_Traits.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/G0B1/htlSPI_Pins.h"
	#include "htl/STM32/G0/htlSPI_Traits.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/F030/htlSPI_Pins.h"

#elif defined(EOS_PLATFORM_STM32F429)
    #include "htl/STM32/F4/F429/htlSPI_Pins.h"
	#include "htl/STM32/F4/htlSPI_Traits.h"

#elif defined(EOS_PLATFORM_STM32F746)
    #include "htl/STM32/F7/F746/htlSPI_Pins.h"
	#include "htl/STM32/F7/htlSPI_Traits.h"

#else
    #error "Unknown platform"
#endif


#endif // defined(HTL_SPIx_EXIST)


#endif // __STM32_htlSPI__
