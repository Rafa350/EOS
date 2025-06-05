#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


/// \file      htlUART.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     UART device manager.


// HTL main include (Include options)
//
#include "HTL/htlBits.h"
#include "HTL/STM32/htl.h"
#include "HTL/STM32/htlClock.h"


// Default options
//
#ifndef HTL_UART_OPTION_IRQ
	#define HTL_UART_OPTION_IRQ HTL_UART_DEFAULT_OPTION_IRQ
#endif

#ifndef HTL_UART_OPTION_DMA
	#define HTL_UART_OPTION_DMA HTL_UART_DEFAULT_OPTION_DMA
#endif

#ifndef HTL_UART_OPTION_FIFO
	#define HTL_UART_OPTION_FIFO HTL_UART_DEFAULT_OPTION_FIFO
#endif

// HTL aditional includes
//
#include "HTL/STM32/htlGPIO.h"
#if HTL_UART_OPTION_DMA == 1
	#include "HTL/STM32/htlDMA.h"
#endif


namespace htl {
	namespace uart {

        class UARTDevice;

        /// Identificador del dispositiu.
        ///
		enum class DeviceID {
#ifdef HTL_UART1_EXIST
			uart1,
#endif
#ifdef HTL_UART2_EXIST
			uart2,
#endif
#ifdef HTL_UART3_EXIST
			uart3,
#endif
#ifdef HTL_UART4_EXIST
			uart4,
#endif
#ifdef HTL_UART5_EXIST
			uart5,
#endif
#ifdef HTL_UART6_EXIST
			uart6,
#endif
#ifdef HTL_UART7_EXIST
			uart7,
#endif
#ifdef HTL_UART8_EXIST
			uart8,
#endif
		};

        /// Primer bit a transmetre.
        ///
		enum class FirstBit {
			lsb, ///< Primer transmet el bit menys significatiu.
			msb  ///< Primer transmet el bit mes significatiu.
		};

        /// Paritat.
        ///
		enum class Parity {
			none, ///< Sense paritat.
			even, ///< Parell
			odd   ///< Senas
		};

        /// Nombre de bits de paraula.
        ///
		enum class WordBits {
#if defined(EOS_PLATFORM_STM32G0)
			wb7,
#endif
			wb8,
			wb9
		};

        /// Nombre de bits de parada.
        ///
		enum class StopBits {
			sb0p5,
			sb1,
			sb1p5,
			sb2
		};

        /// Velocitat de transmissio.
        ///
		enum class BaudMode {
			b1200,    ///< 1200 baud.
			b2400,    ///< 2400 baud.
			b4800,    ///< 4800 baud.
			b9600,    ///< 9600 baud.
			b19200,   ///< 19200 baud.
			b38400,   ///< 38600 baud.
			b57600,   ///< 57600 baud.
			b115200,  ///< 115200 baud.
			div,      ///< Utilitza el divisor per calcular la velocitat.
			rate,     ///< Utilitza la velocitat especificada.
			automatic ///< Deteccio automatica.
		};

        /// Protocol de comunicacio
        ///
		enum class Handsake {
			none,  ///< Cap protocol.
			ctsrts ///< Protocol CTS/RTS
		};

		enum class ClockSource {
			pclk,
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			sysclk,
#endif
#if defined(EOS_PLATFORM_STM32G0)
			hsi16,
#elif defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			hsi,
#endif
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
			lse
#endif
		};

		enum class OverSampling {
			os8,
			os16
		};

		enum class PinFunction {
			tx,
			rx,
			cts,
			rts,
			de
		};

		/// Identificador de la notificacio
		///
		enum class NotifyID {
			null,
			rxCompleted, ///< Recepcio complerta.
			txCompleted, ///< Transmissio complerta.
			error        ///< Error de comunicacio.
		};

		/// Parametres de la notificacio.
		///
		struct NotifyEventArgs {
			bool irq;                      ///< Indica si es notifica desde una interrupcio.
			union {
				struct {
					const uint8_t *buffer; ///< Dades transmeses.
					unsigned length;       ///< Nombre de bytes transmessos.
				} txCompleted;             ///< Parametres de 'TxComplete'
				struct {
					const uint8_t *buffer; ///< Dades rebudes.
					unsigned length;       ///< Nombre de bytes rebuts.
				} rxCompleted;             ///< Parametres de 'RxComplete'
			};
		};

		using NotifyEventRaiser = eos::NotifyEventRaiser<NotifyID, NotifyEventArgs>;
		using INotifyEvent = NotifyEventRaiser::IEvent;
		template <typename Instance_> using NotifyEvent = NotifyEventRaiser::Event<Instance_>;

		namespace internal {

			template <DeviceID>
			struct UARTTraits;

			template <DeviceID, PinFunction, gpio::PortID, gpio::PinID>
			struct PinFunctionInfo;

		}

        /// Clase que implementa el dispositiu de comunicacio UART.
        ///
		class UARTDevice {
			public:
#if HTL_UART_OPTION_DMA == 1
                using DevDMA = htl::dma::DMADevice;
#endif

                /// Estats en que es troba el dispositiu.
                ///
				enum class State {
					invalid,     ///< Objecte no valid.
					reset,       ///< Creat, pero sense inicialitzar.
					ready,       ///< Inicialitzat i preparat per operar.
					transmiting, ///< Transmeten dades.
					receiving    ///< Rebent dades.
				};

			private:
#if HTL_UART_OPTION_DMA == 1
				using DMANotifyEvent = htl::dma::NotifyEvent<UARTDevice>;
				using DMANotifyEventArgs = htl::dma::NotifyEventArgs;
#endif

			private:
				USART_TypeDef * const _usart;   ///< Instancia del dispositiu.
				State _state;                   ///< Estat actual.
				uint8_t *_rxBuffer;             ///< Buffer de recepcio.
				unsigned _rxCount;              ///< Contador de bytes rebuts.
				unsigned _rxMaxCount;           ///< Maxim del contador de bytes rebuts.
				const uint8_t *_txBuffer;       ///< Buffer de transmissio.
				unsigned _txCount;              ///< Contador de bytes transmesos.
				unsigned _txMaxCount;           ///< Maxim del contador de bytes rebuts.
				NotifyEventRaiser _erNotify;    ///< Event de notificacio
#if HTL_UART_OPTION_DMA == 1
				DMANotifyEvent _dmaNotifyEvent; ///< Event de notificacio del DMA.
#endif

			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;

				void setWordBits(WordBits wordBits, bool useParity) const;
				void setStopBits(StopBits wordBits) const;
				void setParity(Parity parity) const;
				void setHandsake(Handsake handsake) const;

				void enable() const;
				void disable() const;

				void enableTransmission() const;
				void disableTransmission() const;
#if HTL_UART_OPTION_IRQ == 1
				void enableTransmissionIRQ() const;
#endif
#if HTL_UART_OPTION_DMA == 1
				void enableTransmissionDMA() const;
#endif

				void enableReception() const;
				void disableReception() const;
#if HTL_UART_OPTION_IRQ == 1
				void enableReceptionIRQ() const;
#endif
#if HTL_UART_OPTION_DMA == 1
				void enableReceptionDMA() const;
#endif

				void writeData(uint8_t data) const;
				uint8_t readData() const;
				bool waitTransmissionComplete(unsigned expireTime);
				bool waitTransmissionBufferEmpty(unsigned expireTime);
				bool waitReceptionBufferFull(unsigned expireTime);

#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
				virtual bool isFIFOAvailable() const = 0;
				bool isFIFOEnabled() const;
#endif
				virtual bool isRTOAvailable() const = 0;

				virtual clock::ClockID getUARTClock() const = 0;

				void notifyTxCompleted(const uint8_t *buffer, unsigned length, bool irq);
				void notifyRxCompleted(const uint8_t *buffer, unsigned length, bool irq);
#if HTL_UART_OPTION_DMA == 1
				void dmaNotifyEventHandler(DevDMA *devDMA, DMANotifyEventArgs &args);
#endif

			protected:
				UARTDevice(USART_TypeDef *usart);

				virtual void activate() const = 0;
				virtual void deactivate() const = 0;

#if HTL_UART_OPTION_IRQ == 1
				void interruptService();
				void txInterruptService();
				void rxInterruptService();
#endif
			public:
				eos::Result initialize();
				eos::Result deinitialize();

				eos::Result setProtocol(WordBits wordBits, Parity parity,
				        StopBits stopBits, Handsake handlsake) const;
				eos::Result setTimming(BaudMode baudMode, uint32_t rate, OverSampling oversampling) const;
				eos::Result setClockSource(ClockSource clockSource) const;
#if defined(EOS_PLATFORM_STM32F0) || defined(EOS_PLATFORM_STM32F7) || defined(EOS_PLATFORM_STM32G0)
				eos::Result setRxTimeout(unsigned timeout) const;
#endif

				inline void setNotifyEvent(INotifyEvent &event, bool enabled = true) {
					_erNotify.set(event, enabled);
				}
				inline void enableNotifyEvent() {
					_erNotify.enable();
				}
				inline void disableNotifyEvent() {
					_erNotify.disable();
				}

				eos::Result transmit(const uint8_t *buffer, unsigned length, unsigned timeout);
				eos::Result receive(uint8_t *buffer, unsigned bufferSize, unsigned timeout);

#if HTL_UART_OPTION_IRQ == 1
				eos::Result transmit_IRQ(const uint8_t *buffer, unsigned length);
				eos::Result receive_IRQ(uint8_t *buffer, unsigned bufferSize);
#endif
#if HTL_UART_OPTION_DMA == 1
				eos::Result transmit_DMA(dma::DMADevice *devDMA, const uint8_t *buffer, unsigned length);
				eos::Result receive_DMA(dma::DMADevice *devDMA, uint8_t *buffer, unsigned bufferSize);
#endif
				eos::Result abortTransmission();
				eos::Result abortReception();

				inline State getState() const { return _state; }
                inline bool isValid() const { return _state != State::invalid; }
				inline bool isReady() const { return _state == State::ready; }
				inline bool isBusy() const { return _state != State::ready; }
		};


		template <DeviceID deviceID_>
		class UARTDeviceX final: public UARTDevice {
			private:
				using UARTTraits = internal::UARTTraits<deviceID_>;
				template <PinFunction pinFunction_, gpio::PortID portID_, gpio::PinID pinID_> using UARTPins = internal::PinFunctionInfo<deviceID_, pinFunction_, portID_, pinID_>;

			private:
				static constexpr auto _usartAddr = UARTTraits::usartAddr;
				static constexpr auto _activateAddr = UARTTraits::activateAddr;
				static constexpr auto _activatePos = UARTTraits::activatePos;
				static UARTDeviceX _instance;

			public:
				static constexpr auto deviceID = deviceID_;
				static constexpr UARTDeviceX *pInst = &_instance;
				static constexpr UARTDeviceX &rInst = _instance;

			private:
				UARTDeviceX() :
					UARTDevice {reinterpret_cast<USART_TypeDef*>(_usartAddr)} {
				}

			protected:
				void activate() const override {
					bits::set(*reinterpret_cast<uint32_t *>(_activateAddr), 1UL << _activatePos);
					__DSB();
				}
				void deactivate() const override {
					bits::clear(*reinterpret_cast<uint32_t *>(_activateAddr),  1UL << _activatePos);
				}

				clock::ClockID getUARTClock() const override;

#if (HTL_USART_OPTION_FIFO == 1) && defined(EOS_PLATFORM_STM32G0)
				bool isFIFOAvailable() const override;
				bool isFIFOEnabled() const;
#endif
				bool isRTOAvailable() const override;

			public:
#if HTL_UART_OPTION_IRQ == 1
				inline static void interruptHandler() {
					_instance.interruptService();
				}
#endif

				template <typename pin_>
				void initPinTX() {
					auto af = UARTPins<PinFunction::tx, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternateOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				void initPinRX() {
					auto af = UARTPins<PinFunction::rx, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternateOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				void initPinCTS() {
					auto af = UARTPins<PinFunction::cts, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternateOutput(gpio::OutputMode::pushPull, gpio::Speed::fast, af);
				}

				template <typename pin_>
				void initPinRTS() {
					auto af = UARTPins<PinFunction::rts, pin_::portID, pin_::pinID>::value;
					pin_::pInst->initAlternateInput(gpio::InputMode::floating, af);
				}
		};

		template <DeviceID deviceID_>
		UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_instance;


#ifdef HTL_UART1_EXIST
		using UARTDevice1 = UARTDeviceX<DeviceID::uart1>;
#endif
#ifdef HTL_UART2_EXIST
		using UARTDevice2 = UARTDeviceX<DeviceID::uart2>;
#endif
#ifdef HTL_UART3_EXIST
		using UARTDevice3 = UARTDeviceX<DeviceID::uart3>;
#endif
#ifdef HTL_UART4_EXIST
		using UARTDevice4 = UARTDeviceX<DeviceID::uart4>;
#endif
#ifdef HTL_UART5_EXIST
		using UARTDevice5 = UARTDeviceX<DeviceID::uart5>;
#endif
#ifdef HTL_UART6_EXIST
		using UARTDevice6 = UARTDeviceX<DeviceID::uart6>;
#endif
#ifdef HTL_UART7_EXIST
		using UARTDevice7 = UARTDeviceX<DeviceID::uart7>;
#endif
#ifdef HTL_UART8_EXIST
		using UARTDevice8 = UARTDeviceX<DeviceID::uart8>;
#endif
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G031/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G051)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G051/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G071)
	#include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G071/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32G0B1)
    #include "htl/STM32/G0/htlUART_Traits.h"
    #include "htl/STM32/G0/G0B1/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F030)
	#include "htl/STM32/F0/htlUART_Traits.h"
    #include "htl/STM32/F0/F030/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F429)
	#include "htl/STM32/F4/htlUART_Traits.h"
    #include "htl/STM32/F4/F429/htlUART_Pins.h"

#elif defined(EOS_PLATFORM_STM32F746)
	#include "htl/STM32/F7/htlUART_Traits.h"
    #include "htl/STM32/F7/F746/htlUART_Pins.h"

#else
    #error "Unknown platform"
#endif


#if defined(EOS_PLATFORM_STM32F0)
namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID UARTDeviceX<deviceID_>::getUARTClock() const {

		auto addr = reinterpret_cast<uint32_t*>(UARTTraits::clockSourceAddr);
		auto msk = UARTTraits::clockSourceMsk;
		auto pos = UARTTraits::clockSourcePos;

		switch ((*addr & msk) >> pos) {
			case RCC_CFGR3_USART1SW_PCLK:
				return clock::ClockID::pclk;

			case RCC_CFGR3_USART1SW_SYSCLK:
				return clock::ClockID::sysclk;

			case RCC_CFGR3_USART1SW_LSE:
				return clock::ClockID::lse;

			case RCC_CFGR3_USART1SW_HSI:
				return clock::ClockID::hsi;
		}
	}

	template<>
	inline clock::ClockID UARTDeviceX<DeviceID::uart2>::getUARTClock() const {

		return clock::ClockID::pclk;
	}
}

#elif defined(EOS_PLATFORM_STM32F4)

namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID htl::uart::UARTDeviceX<deviceID_>::getUARTClock() const {

		return UARTTraits::pclkX;
	}
}

#elif defined(EOS_PLATFORM_STM32F7)

namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID htl::uart::UARTDeviceX<deviceID_>::getUARTClock() const {

		auto addr = reinterpret_cast<uint32_t*>(UARTTraits::clockSourceAddr);
		auto msk = UARTTraits::clockSourceMsk;
		auto pos = UARTTraits::clockSourcePos;

		auto pclkX = UARTTraits::pclkX;

		switch ((*addr & msk) >> pos) {
			case 0:
				return pclkX;

			case 1:
				return clock::ClockID::sysclk;

			case 2:
				return clock::ClockID::hsi;

			case 3:
				return clock::ClockID::lse;
		}
	}

}

#elif defined(EOS_PLATFORM_STM32G0)

namespace htl::uart {

	template<DeviceID deviceID_>
	clock::ClockID htl::uart::UARTDeviceX<deviceID_>::getUARTClock() const {

		auto addr = reinterpret_cast<uint32_t*>(UARTTraits::clockSourceAddr);
		auto msk = UARTTraits::clockSourceMsk;
		auto pos = UARTTraits::clockSourcePos;

		switch ((*addr & msk) >> pos) {
			case 0:
				return clock::ClockID::pclk;

			case 1:
				return clock::ClockID::sysclk;

			case 2:
				return clock::ClockID::hsi16;

			case 3:
				return clock::ClockID::lse;
		}
	}
}

#endif

namespace htl::uart {

	template<DeviceID deviceID_>
	bool UARTDeviceX<deviceID_>::isRTOAvailable() const {

		return UARTTraits::isRTOAvailable;
	}
}


#endif // __STM32_htlUART__
