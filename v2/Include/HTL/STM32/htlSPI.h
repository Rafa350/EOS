#pragma once
#ifndef __STM32_htlSPI__
#define __STM32_htlSPI__


// EOS includes
//
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlDMA.h"
#include "System/eosResults.h"


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

		enum class PinFunction {
			sck,
			miso,
			mosi
		};
        
        
        struct NotifyEventArgs {
            bool irq;
        };

		class SPIDevice;
        using INotifyEvent = eos::ICallbackP2<SPIDevice*, NotifyEventArgs&>;
        template <typename Instance_> using NotifyEvent =
                eos::CallbackP2<Instance_, SPIDevice*, NotifyEventArgs&>;


		enum class Results {
		    success,
		    busy,
		    timeout,
		    error
		};
		using Result = eos::SimpleResult<Results>;


		class SPIDevice {
			public:
				enum class State {
					reset,
					ready,
					transmiting
				};
                
			private:
				SPI_TypeDef * const _spi;
				State _state;
                INotifyEvent *_notifyEvent;
                bool _notifyEventEnabled;
                
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
				Result initialize(Mode mode, ClkPolarity clkPolarity,
				        ClkPhase clkPhase, WordSize size, FirstBit firstBit,
				        ClockDivider clkDivider);
				inline Result initMaster(ClkPolarity clkPolarity,
                        ClkPhase clkPhase, WordSize size, FirstBit firstBit,
                        ClockDivider clkDivider) {
				    return initialize(Mode::master, clkPolarity, clkPhase,
				            size, firstBit, clkDivider);
				}
				Result deinitialize();
                
				void setNotifyEvent(INotifyEvent &event, bool enabled = true);
				inline void enableNotifyEvent() {
					_notifyEventEnabled = _notifyEvent != nullptr;
				}
				inline void disableNotifyEvent() {
					_notifyEventEnabled = false;
				}
                               
				Result transmit(const uint8_t *txBuffer, uint8_t *rxBuffer,
				        unsigned bufferSize, Tick timeout = Tick(-1));
				inline Result receive(uint8_t *rxBuffer, unsigned bufferSize,
				        Tick timeout)  {
					return transmit(nullptr, rxBuffer, bufferSize, timeout);
				}
                inline Result transmit(const uint8_t *txBuffer, unsigned bufferSize,
                        Tick timeout) {
                    return transmit(txBuffer, nullptr, bufferSize, timeout);
                }
                
                Result transmitDMA(htl::dma::DMADevice *devTxDMA,
                        const uint8_t *txBuffer, unsigned bufferSize, Tick timeout);
                Result transmitDMA_IRQ(htl::dma::DMADevice *devTxDMA,
                        const uint8_t *txBuffer, unsigned bufferSize);
				
                inline State getState() const {
				    return _state;
				}
		};


		namespace internal {

			template <DeviceID>
			struct SPITraits;

			template <DeviceID, PinFunction, typename>
			struct PinFunctionInfo;
		}

		template <DeviceID deviceID_>
		class SPIDeviceX final: public SPIDevice {
			private:
				using SPITraits = internal::SPITraits<deviceID_>;
                
			private:
				static constexpr auto _spiAddr = SPITraits::spiAddr;
				static constexpr auto _rccEnableAddr = SPITraits::rccEnableAddr;
				static constexpr auto _rccEnablePos = SPITraits::rccEnablePos;
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
				void activateImpl() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivateImpl() override {
					auto p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
                
			public:
				inline static void interruptHandler() {
					_instance.interruptService();
				}
                
				template <typename pin_>
				void initPinSCK() {
				    auto af = internal::PinFunctionInfo<deviceID_, PinFunction::sck, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void initPinMOSI() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::mosi, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
				}
				template <typename pin_>
				void initPinMISO() {
					auto af = internal::PinFunctionInfo<deviceID_, PinFunction::miso, pin_>::alt;
                    pin_::initAlternate(gpio::AlternateMode::pushPull, gpio::Speed::fast, af);
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
			struct SPITraits<DeviceID::_1> {
				static constexpr uint32_t spiAddr = SPI1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_SPI1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI1EN_Pos;
				#endif
			};
				#endif

			#ifdef HTL_SPI2_EXIST
			template<>
			struct SPITraits<DeviceID::_2> {
				static constexpr uint32_t spiAddr = SPI2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_SPI2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI2EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI3_EXIST
			template<>
			struct SPITraits<DeviceID::_3> {
				static constexpr uint32_t spiAddr = SPI3_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB1ENR_SPI3EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI4_EXIST
			template<>
			struct SPITraits<DeviceID::_4> {
				static constexpr uint32_t spiAddr = SPI4_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI4EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI5_EXIST
			template<>
			struct SPITraits<DeviceID::_5> {
				static constexpr uint32_t spiAddr = SPI5_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI5EN_Pos;
				#endif
			};
			#endif

			#ifdef HTL_SPI6_EXIST
			template<>
			struct SPITraits<DeviceID::_6> {
				static constexpr uint32_t spiAddr = SPI6_BASE;
				#if defined(EOS_PLATFORM_STM32F4)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
				static constexpr uint32_t rccEnablePos = RCC_APB2ENR_SPI6EN_Pos;
				#elif defined(EOS_PLATFORM_STM32F7)
				static constexpr uint32_t rccEnableAddr =
				        RCC_BASE + offsetof(RCC_TypeDef, APB2ENR);
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

#elif defined(EOS_PLATFORM_STM32G071)
    #include "htl/STM32/G0/htlSPI_AF_G071.h"

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
