#pragma once
#ifndef __STM32_htlUART__
#define __STM32_htlUART__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"
#include "HTL/STM32/htlINT.h"


// Detecta les opcions suportades
//
#if defined(EOS_PLATFORM_STM32F0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
	#define HTL_UART_7BIT_SUPPORT 1
	#define HTL_UART_LINMODE_SUPPORT 1
	#define HTL_UART_SMARTCARD_SUPPORT 1
#elif defined(EOS_PLATFORM_STM32G0)
	#define HTL_UART_7BIT_SUPPORT 0
	#define HTL_UART_LINMODE_SUPPORT 0
	#define HTL_UART_SMARTCARD_SUPPORT 0
#else
	#error "Unknown platform"
#endif


namespace htl {

	namespace uart {

		enum class DeviceID {
			#ifdef HTL_UART1_EXIST
				_1,
			#endif
			#ifdef HTL_UART2_EXIST
				_2,
			#endif
			#ifdef HTL_UART3_EXIST
				_3,
			#endif
			#ifdef HTL_UART4_EXIST
				_4,
			#endif
			#ifdef HTL_UART5_EXIST
				_5,
			#endif
			#ifdef HTL_UART6_EXIST
				_6,
			#endif
			#ifdef HTL_UART7_EXIST
				_7,
			#endif
			#ifdef HTL_UART8_EXIST
				_8,
			#endif
		};

		enum class FirstBit {
			lsb,
			msb
		};

		enum class Parity {
			none,
			even,
			odd
		};

		enum class WordBits {
			#if HTL_UART_7BIT_SUPPORT == 1
				_7,
			#endif
			_8
		};

		enum class StopBits {
			_0p5,
			_1,
			_1p5,
			_2
		};

		enum class BaudMode {
			_1200,
			_2400,
			_4800,
			_9600,
			_19200,
			_38400,
			_57600,
			_115200,
			div,
			rate,
			automatic
		};

		enum class Handsake {
			none,
			ctsrts
		};

		enum class ClockSource {
			pclk,
			sysclk,
			hsi,
			lse,
			automatic
		};

		enum class OverSampling {
			_8,
			_16
		};

		enum class PinFunction {
			tx,
			rx,
			cts,
			rts,
			de
		};

		using ITxCompletedCallback = eos::ICallbackP2<const uint8_t*, uint16_t>;

		template <typename instance_>
		using TxCompletedCallback = eos::CallbackP2<instance_, const uint8_t*, uint16_t>;

		namespace internal {

			template <DeviceID>
			struct HardwareInfo;

			template <DeviceID, PinFunction, typename>
			struct UARTPinFunctionID;
		}

		class UARTDevice {
			private:
				USART_TypeDef * const _usart;
				uint8_t *_rxBuffer;
				uint16_t _rxSize;
				uint16_t _rxCount;
				const uint8_t *_txBuffer;
				uint16_t _txSize;
				uint16_t _txCount;
				ITxCompletedCallback *_txCompletedCallback;
			private:
				UARTDevice(const UARTDevice &) = delete;
				UARTDevice & operator = (const UARTDevice &) = delete;
			protected:
				UARTDevice(USART_TypeDef *usart);
				void interruptService();
				virtual void activateImpl() = 0;
				virtual void deactivateImpl() = 0;
				virtual void resetImpl() = 0;
			public:
				inline void activate() {
					activateImpl();
				}
				inline void deactivate() {
					deactivateImpl();
				}
				inline void reset() {
					resetImpl();
				}
				inline void enable() {
					_usart->CR1 |= USART_CR1_UE;
				}
				inline void disable() {
					_usart->CR1 &= ~USART_CR1_UE;
				}
				inline void enableTX() {
					ATOMIC_SET_BIT(_usart->CR1, USART_CR1_TE);
				}
				inline void enableRX() {
					ATOMIC_SET_BIT(_usart->CR1, USART_CR1_RE);
				}
				inline void disableTX() {
					ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_TE);
				}
				inline void disableRX() {
					ATOMIC_CLEAR_BIT(_usart->CR1, USART_CR1_RE);
				}
				void initialize();
				void deinitialize();
				void setProtocol(WordBits wordBits, Parity parity, StopBits stopBits, Handsake handlsake);
				void setTimming(BaudMode baudMode, ClockSource clockSource, uint32_t rate, OverSampling oversampling);
				void setRxTimeout(uint32_t lostBits);
				inline void enableTxCompletedCallback(ITxCompletedCallback &callback) {
					_txCompletedCallback = &callback;
				}
				inline void disableTxCompletedCallback() {
					_txCompletedCallback = nullptr;
				}
				uint16_t transmit(const uint8_t *buffer, uint16_t size);
				uint16_t receive(uint8_t *buffer, uint16_t size);
		};

		typedef UARTDevice *UARTDeviceHandler;


		template <DeviceID deviceID_>
		class UARTDeviceX final: public UARTDevice {
			private:
				using HI = internal::HardwareInfo<deviceID_>;
			private:
				static constexpr uint32_t _usartAddr = HI::usartAddr;
				static constexpr uint32_t _rccEnableAddr = HI::rccEnableAddr;
				static constexpr uint32_t _rccEnablePos = HI::rccEnablePos;
				static constexpr uint32_t _rccResetAddr = HI::rccResetAddr;
				static constexpr uint32_t _rccResetPos = HI::rccResetPos;
				static UARTDeviceX _device;
			public:
				static constexpr DeviceID deviceID = deviceID_;
				static constexpr INTVector irqVectorID = HI::vector;
			private:
				UARTDeviceX() :
					UARTDevice(reinterpret_cast<USART_TypeDef*>(_usartAddr)) {
				}
			protected:
				void activateImpl() override {
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p |= 1 << _rccEnablePos;
					__DSB();
				}
				void deactivateImpl() override{
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccEnableAddr);
					*p &= ~(1 << _rccEnablePos);
				}
				void resetImpl() override{
					uint32_t *p = reinterpret_cast<uint32_t *>(_rccResetAddr);
					*p |= 1 << _rccResetPos;
					*p &= ~(1 << _rccResetPos);
				}
			public:
				static constexpr UARTDeviceX * getHandler() {
					return &_device;
				}
				inline static void interruptHandler() {
					getHandler()->interruptService();
				}
				template <typename pin_>
				void initTXPin() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::tx, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initRXPin() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::rx, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initCTSPin() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::cts, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
				template <typename pin_>
				void initRTSPin() {
					gpio::PinFunctionID pinFunctionID = internal::UARTPinFunctionID<deviceID_, PinFunction::rts, pin_>::alt;
					pin_::getHandler()->initAlt(gpio::OutDriver::pushPull, gpio::Speed::fast, pinFunctionID);
				}
		};

		template <DeviceID deviceID_>
		UARTDeviceX<deviceID_> UARTDeviceX<deviceID_>::_device;

		/*	public:
				/// \bried Inicialitza el modul.
				///
				static void initialize() {

					activate();
					disable();
				}

				/// \bried Desinicialitza el modul.
				///
				static void deinitialize() {

					disable();
					deactivate();
				}

				/// \brief Reseteja el modul
				///
				static void reset() {

					#ifdef HTL_UART1_EXIST
						if constexpr (channel_ == UARTChannel::_1)
							UART1Reset();
					#endif
					#ifdef HTL_UART2_EXIST
						if constexpr (channel_ == UARTChannel::_2)
							UART2Reset();
					#endif
					#ifdef HTL_UART3_EXIST
						if constexpr (channel_ == UARTChannel::_3)
							UART3Reset();
					#endif
					#ifdef HTL_UART4_EXIST
						if constexpr (channel_ == UARTChannel::_4)
							UART4Reset();
					#endif
					#ifdef HTL_UART5_EXIST
						if constexpr (channel_ == UARTChannel::_5)
							UART5Reset();
					#endif
					#ifdef HTL_UART6_EXIST
						if constexpr (channel_ == UARTChannel::_6)
							UART6Reset();
					#endif
					#ifdef HTL_UART7_EXIST
						if constexpr (channel_ == UARTChannel::_7)
							UART7Reset();
					#endif
					#ifdef HTL_UART8_EXIST
						if constexpr (channel_ == UARTChannel::_8)
							UART8Reset();
					#endif
				}

				/// \brief Habilita el modul.
				///
				static void enable() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					regs->CR1 |= USART_CR1_UE;
				}

				/// \brief Habilita la transmisio
				///
				static void enableTX() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					ATOMIC_SET_BIT(regs->CR1, USART_CR1_TE);
				}

				/// \brief Habilita la recepcio.
				///
				static void enableRX() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					ATOMIC_SET_BIT(regs->CR1, USART_CR1_RE);
				}

				/// \brief Deshabilita el modul.
				///
				static void disable() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					regs->CR1 &= ~(USART_CR1_UE | USART_CR1_RE | USART_CR1_TE);
				}

				/// \brief Deshabilita la transmisio.
				///
				static void disableTX() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TE);
				}

				/// \brief Deshabilita la recepcio.
				///
				static void disableRX() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RE);
				}

				/// \brief Configuracio del timing.
				/// \param baudMode: Opcions de baud.
				/// \param clocCource: Opcions del clock.
				/// \param baud: El valor de velocitat.
				/// \param overSampling: Valor del sobre mostrejat
				///
				static void setTimming(
					UARTBaudMode baudMode = UARTBaudMode::_9600,
					UARTClockSource clockSource = UARTClockSource::automatic,
					uint32_t rate = 0,
					UARTOverSampling overSampling = UARTOverSampling::_16) {

					UARTBase_x::setTimming(
						reinterpret_cast<USART_TypeDef*>(_addr),
						baudMode,
						clockSource,
						rate,
						overSampling);
				}

				/// \brief Configura el protocol de comunicacio.
				/// \param work: Numero de bits de dades.
				/// \param parity: Opcions de paritat.
				/// \param stop: Numero dels bits de parada.
				/// \param handsake: El protocol hardware.
				///
				static void setProtocol(
					UARTWordBits wordBits,
					UARTParity parity,
					UARTStopBits stopBits,
					UARTHandsake handsake = UARTHandsake::none) {

					UARTBase_x::setProtocol(
						reinterpret_cast<USART_TypeDef*>(_addr),
						wordBits,
						parity,
						stopBits,
						handsake);
				}

				/// \brief Configura el timeout per recepcio.
				/// \param bits: Nombre de bits perduts per generar timeout
				///
				static void setRxTimeout(
					uint32_t lostBits) {

					if constexpr (Trait::supportedRxTimeout) {
						USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
						if (lostBits > 0) {
							regs->RTOR |= (lostBits << USART_RTOR_RTO_Pos) & USART_RTOR_RTO_Msk;
							regs->CR2 |= USART_CR2_RTOEN;
						}
						else
							regs->CR2 &= ~USART_CR2_RTOEN;
					}
				}

				/// \brief Inicialitza el pin TX
				///
				template <typename gpio_>
				static void initTXPin() {

					gpio_::initAlt(
						htl::gpio::OutDriver::pushPull,
						htl::gpio::Speed::fast,
						UARTPinTrait<channel_, gpio_, UARTPin::TX>::alt);
				}

				/// \brief Inicialitza el pin RX
				///
				template <typename gpio_>
				static void initRXPin() {

					gpio_::initAlt(
						htl::gpio::OutDriver::pushPull,
						htl::gpio::Speed::fast,
						UARTPinTrait<channel_, gpio_, UARTPin::RX>::alt);
				}

				/// \brief Inicialitza el pin CTS
				///
				template <typename gpio_>
				static void initCTSPin() {

					gpio_::initAlt(
						htl::gpio::OutDriver::pushPull,
						htl::gpio::Speed::fast,
						UARTPinTrait<channel_, gpio_, UARTPin::CTS>::alt);
				}

				/// \brief Inicialitza el pin RTS
				///
				template <typename gpio_>
				static void initRTSPin() {

					gpio_::initAlt(
						htl::gpio::OutDriver::pushPull,
						htl::gpio::Speed::fast,
						UARTPinTrait<channel_, gpio_, UARTPin::RTS>::alt);
				}

				/// \brief Escriu un byte en el buffer de transmissio.
				/// \param data: El byte.
				///
				static void write(
					uint8_t data) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					regs->TDR = data;
				}

				/// \brief Llegeix un byte del buffer de recepcio.
				/// \return El byte.
				///
				static uint8_t read() {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					return regs->RDR;
				}

				/// \brief Habilita les interrupcions
				/// \param interrupt: La interrupcio.
				///
				static void enableInterrupt(
					UARTInterrupt interrupt) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					switch (interrupt) {
						case UARTInterrupt::cts:
							ATOMIC_SET_BIT(regs->CR3, USART_CR3_CTSIE);
							break;

						#if HTL_UART_LINMODE_SUPPORT == 1
							case UARTInterrupt::linBrk:
								ATOMIC_SET_BIT(regs->CR2, USART_CR2_LBDIE);
								break;
						#endif

						case UARTInterrupt::idle:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_IDLEIE);
							break;

						case UARTInterrupt::txEmpty:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_TXEIE);
							break;

						case UARTInterrupt::txComplete:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_TCIE);
							break;

						case UARTInterrupt::rxNotEmpty:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_RXNEIE);
							break;

						case UARTInterrupt::parity:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_PEIE);
							break;

						case UARTInterrupt::rxTimeout:
							if constexpr (Trait::supportedRxTimeout)
								ATOMIC_SET_BIT(regs->CR1, USART_CR1_RTOIE);
							break;

						case UARTInterrupt::endOfBlock:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_EOBIE);
							break;

						case UARTInterrupt::match:
							ATOMIC_SET_BIT(regs->CR1, USART_CR1_CMIE);
							break;

						case UARTInterrupt::error:
							ATOMIC_SET_BIT(regs->CR3, USART_CR3_EIE);
							break;
					}
				}

				/// \brief Deshabilita les interrupcions
				/// \param event: El event.
				///
				static bool disableInterrupt(
					UARTInterrupt interrupt) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);

					bool state = false;
					switch (interrupt) {
						case UARTInterrupt::cts:
							state = (regs->CR3 & USART_CR3_CTSIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR3, USART_CR3_CTSIE);
							break;

						#if HTL_UART_LINMODE_SUPPORT == 1
							case UARTInterrupt::linBrk:
								state = (regs->CR2 & USART_CR2_LBDIE) != 0;
								ATOMIC_CLEAR_BIT(regs->CR2, USART_CR2_LBDIE);
								break;
						#endif

						case UARTInterrupt::idle:
							state = (regs->CR1 & USART_CR1_IDLEIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_IDLEIE);
							break;

						case UARTInterrupt::txEmpty:
							state = (regs->CR1 & USART_CR1_TXEIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TXEIE);
							break;

						case UARTInterrupt::txComplete:
							state = (regs->CR1 & USART_CR1_TCIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_TCIE);
							break;

						case UARTInterrupt::rxNotEmpty:
							state = regs->CR1 & USART_CR1_RXNEIE;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RXNEIE);
							break;

						case UARTInterrupt::parity:
							state = (regs->CR1 & USART_CR1_PEIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_PEIE);
							break;

						case UARTInterrupt::rxTimeout:
							if constexpr (Trait::supportedRxTimeout) {
								state = (regs->CR1 & USART_CR1_RTOIE) != 0;
								ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_RTOIE);
							}
							break;

						#ifdef USART_CR1_EOBIE
							case UARTInterrupt::endOfBlock:
								state = (regs->CR1 & USART_CR1_EOBIE) != 0;
								ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_EOBIE);
								break;
						#endif

						case UARTInterrupt::match:
							state = (regs->CR1 & USART_CR1_CMIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR1, USART_CR1_CMIE);
							break;

						case UARTInterrupt::error:
							state = (regs->CR3 & USART_CR3_EIE) != 0;
							ATOMIC_CLEAR_BIT(regs->CR3, USART_CR3_EIE);
							break;
					}

					return state;
				}

				/// \brief Comprova si la interrupcio esta habilidata
				// \param interrupt: La interrupcio.
				// \return True si esta habilitada, false en cas conmtrari
				//
				static bool isInterruptEnabled(
					UARTInterrupt interrupt) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);

					bool state = false;
					switch (interrupt) {
						case UARTInterrupt::cts:
							state = (regs->CR3 & USART_CR3_CTSIE) != 0;
							break;

						#if HTL_UART_LINMODE_SUPPORT == 1
							case UARTInterrupt::linBrk:
								state = (regs->CR2 & USART_CR2_LBDIE) != 0;
								break;
						#endif

						case UARTInterrupt::idle:
							state = (regs->CR1 & USART_CR1_IDLEIE) != 0;
							break;

						case UARTInterrupt::txEmpty:
							state = (regs->CR1 &USART_CR1_TXEIE) != 0;
							break;

						case UARTInterrupt::txComplete:
							state = (regs->CR1 & USART_CR1_TCIE) != 0;
							break;

						case UARTInterrupt::rxNotEmpty:
							state = (regs->CR1 & USART_CR1_RXNEIE) != 0;
							break;

						case UARTInterrupt::parity:
							state = (regs->CR1 & USART_CR1_PEIE) != 0;
							break;

						case UARTInterrupt::rxTimeout:
							if constexpr (Trait::supportedRxTimeout)
								state = (regs->CR1 & USART_CR1_RTOIE) != 0;
							break;

						case UARTInterrupt::endOfBlock:
							state = (regs->CR1 & USART_CR1_EOBIE) != 0;
							break;

						case UARTInterrupt::match:
							state = (regs->CR1, USART_CR1_CMIE) != 0;
							break;

						case UARTInterrupt::error:
							state = (regs->CR3 & USART_CR3_EIE) != 0;
							break;
					}

					return state;
				}

				/// \brief Obte un flag.
				/// \param flag: El flag.
				///
				static bool getFlag(
					UARTFlag flag) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					switch (flag) {
						case UARTFlag::framming:
							return (regs->ISR & USART_ISR_FE) != 0;

						case UARTFlag::idle:
							return (regs->ISR & USART_ISR_IDLE) != 0;

						case UARTFlag::noise:
							return (regs->ISR & USART_ISR_NE) != 0;

						case UARTFlag::overrun:
							return (regs->ISR & USART_ISR_ORE) != 0;

						case UARTFlag::parity:
							return (regs->ISR & USART_ISR_PE) != 0;

						case UARTFlag::txComplete:
							return (regs->ISR & USART_ISR_TC) != 0;

						case UARTFlag::txEmpty:
							return (regs->ISR & USART_ISR_TXE) != 0;

						case UARTFlag::rxNotEmpty:
							return (regs->ISR & USART_ISR_RXNE) != 0;

						case UARTFlag::rxTimeout:
							if constexpr (Trait::supportedRxTimeout)
								return (regs->ISR & USART_ISR_RTOF) != 0;
							else
								return false;

						case UARTFlag::cts:
							return (regs->ISR & USART_ISR_CTSIF) != 0;

						default:
							return false;
					}
				}

				static bool isTxEmpty()  {

					return  getFlag(UARTFlag::txEmpty);
				}

				static bool isTxComplete()  {

					return  getFlag(UARTFlag::txComplete);
				}

				static bool isRxNotEmpty() {

					return getFlag(UARTFlag::rxNotEmpty);
				}

				static bool isRxTimeout() {

					if constexpr (Trait::suportedRxTimeout)
						return getFlag(UARTFlag::rxTimeout);
					else
						return false;
				}

				/// \brief Borra el flag.
				/// \param flag: El flag.
				///
				static void clearFlag(
					UARTFlag flag) {

					USART_TypeDef *regs = reinterpret_cast<USART_TypeDef*>(_addr);
					switch (flag) {
						case UARTFlag::cts:
							regs->ICR = USART_ICR_CTSCF;
							break;

						#ifdef USART_ICR_EOBCF
							case UARTFlag::endOfBlock:
								regs->ICR = USART_ICR_EOBCF;
								break;
						#endif

						case UARTFlag::framming:
							regs->ICR = USART_ICR_FECF;
							break;

						case UARTFlag::idle:
							regs->ICR = USART_ICR_IDLECF;
							break;

						case UARTFlag::noise:
							regs->ICR = USART_ICR_NCF;
							break;

						case UARTFlag::overrun:
							regs->ICR = USART_ICR_ORECF;
							break;

						case UARTFlag::parity:
							regs->ICR = USART_ICR_PECF;
							break;

						case UARTFlag::rxTimeout:
							if constexpr (Trait::supportedRxTimeout)
								regs->ICR = USART_ICR_RTOCF;
							break;

						case UARTFlag::txComplete:
							regs->ICR = USART_ICR_TCCF;
							break;

						#if HTL_UART_LINMODE_SUPPORT == 1
							case UARTFlag::linBrk:
								regs->ICR = USART_ICR_LBDCF;
								break;
						#endif

						case UARTFlag::match:
							regs->ICR = USART_ICR_CMCF;
							break;

						default:
							break;
					}
				}

				/// \brief Asigna la funcio d'interrupcio.
				/// \param function: La funcio.
				/// \param param: El parametre.
				///
				static void setInterruptFunction(
					UARTInterruptFunction function,
					UARTInterruptParam param) {

					_isrFunction = function;
					_isrParam = param;
				}

				/// \brief Invoca la funcio d'interrupcio.
				/// \param event: L'event.
				//
				static void interruptHandler() {

					if (_isrFunction != nullptr)
						_isrFunction(_isrParam);
				}
		};*/


		#ifdef HTL_UART1_EXIST
			using UARTDevice1 = UARTDeviceX<DeviceID::_1>;
		#endif
		#ifdef HTL_UART2_EXIST
			using UARTDevice2 = UARTDeviceX<DeviceID::_2>;
		#endif
		#ifdef HTL_UART3_EXIST
			using UARTDevice3 = UARTDeviceX<DeviceID::_3>;
		#endif
		#ifdef HTL_UART4_EXIST
			using UARTDevice4 = UARTDeviceX<DeviceID::_4>;
		#endif
		#ifdef HTL_UART5_EXIST
			using UARTDevice5 = UARTDeviceX<DeviceID::_5>;
		#endif
		#ifdef HTL_UART6_EXIST
			using UARTDevice6 = UARTDeviceX<DeviceID::_6>;
		#endif
		#ifdef HTL_UART7_EXIST
			using UARTDevice7 = UART_x<UARTChannel::_7>;
		#endif
		#ifdef HTL_UART8_EXIST
			using UARTDevice8 = UART_x<UARTChannel::_8>;
		#endif

		namespace internal {

			#ifdef HTL_UART1_EXIST
			template <>
			struct HardwareInfo<DeviceID::_1> {
				static constexpr uint32_t usartAddr = USART1_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR2);
				static constexpr uint32_t rccEnablePos = RCC_APBENR2_USART1EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR2);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR2_USART1RST_Pos;
				#endif
				static constexpr INTVector vector = INTVector::uart1;
			};
			#endif

			#ifdef HTL_UART2_EXIST
			template <>
			struct HardwareInfo<DeviceID::_2> {
				static constexpr uint32_t usartAddr = USART2_BASE;
				#if defined(EOS_PLATFORM_STM32G0)
				static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
				static constexpr uint32_t rccEnablePos = RCC_APBENR1_USART2EN_Pos;
				static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
				static constexpr uint32_t rccResetPos = RCC_APBRSTR1_USART2RST_Pos;
				static constexpr bool supportedRxTimeout = false;
				#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
				static constexpr bool supportedRxTimeout = true;
				#elif defined(EOS_PLATFORM_STM32G0)
				static constexpr bool supportedRxTimeout = false;
				#else
				#error Plataforma no soportada
				#endif
				static constexpr INTVector vector = INTVector::uart2;
			};
			#endif

			#ifdef HTL_UART3_EXIST
			template <>
			struct HardwareInfo<DeviceID::_3> {
				static constexpr uint32_t usartAddr = USART3_BASE;
				static constexpr INTVector vector = INTVector::uart3;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART4_EXIST
			template <>
			struct HardwareInfo<DeviceID::_4> {
				static constexpr uint32_t usartAddr = UART4_BASE;
				static constexpr INTVector vector = INTVector::uart4;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART5_EXIST
			template <>
			struct HardwareInfo<DeviceID::_5> {
				static constexpr uint32_t usartAddr = UART5_BASE;
				static constexpr INTVector vector = INTVector::uart5;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART6_EXIST
			template <>
			struct HardwareInfo<DeviceID::_6> {
				static constexpr uint32_t usartAddr = USART6_BASE;
				static constexpr INTVector vector = INTVector::uart6;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART7_EXIST
			template <>
			struct HardwareInfo<DeviceID::_7> {
				static constexpr uint32_t usartAddr = UART7_BASE;
				static constexpr INTVector vector = INTVector::uart7;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif

			#ifdef HTL_UART8_EXIST
			template <>
			struct HardwareInfo<DeviceID::_8> {
				static constexpr uint32_t usartAddr = UART8_BASE;
				static constexpr INTVector vector = INTVector::uart8;
				static constexpr bool supportedRxTimeout = true;
			};
			#endif
		}
	}
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/G0/htlUART_AF_G030.h"
    
#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/G0/htlUART_AF_G031.h"
    
#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/F0/htlUART_AF_F030.h"
    
#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/F4/htlUART_AF_F4.h"
    
#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/F7/htlUART_AF_F7.h"
    
#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlUART__

