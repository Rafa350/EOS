#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/htlGPIO.h"


namespace htl {

	enum class I2CChannel {
		#ifdef HTL_I2C1_EXIST
		_1,
		#endif
		#ifdef HTL_I2C2_EXIST
		_2,
		#endif
		#ifdef HTL_I2C3_EXIST
		_3,
		#endif
		#ifdef HTL_I2C4_EXIST
		_4
		#endif
	};

	enum class I2CClockSource {
		sysclk,
		#if defined(EOS_PLATFORM_STM32F4)
		hsi,
		pclk1,
		#elif defined(EOS_PLATFORM_STM32G0)
		hsi16,
		pclk,
		#endif
	};

	enum class I2CInterrupt {
        rx,
        tx,
        stop,
        tc,
        addr,
        nack,
        err
	};

	enum class I2CFlag {
        rxne,
        txis,
        stop,
        tcr,
        tc,
        addr,
        nack,
        berr,
        arlo,
        pecerr,
        timeout,
        alert
	};

	enum class I2CPin {
		SCL,
		SDA
	};

	enum class I2CInterruptNotify {
		undefined,
		addrMatch,
		rxNotEmpty,
		txEmpty,
		nack,
		completted
	};
	using I2CInterruptParam = void*;
	using I2CInterruptFunction = void (*)(I2CInterruptNotify, I2CInterruptParam);

	struct I2CTransferContext {
		uint8_t *buffer;
		uint16_t size;
		uint16_t count;
	};

	template <I2CChannel>
	class I2CTrait {
	};

	template <I2CChannel, typename, I2CPin>
	struct I2CPinTrait {
	};

	template <I2CChannel channel_>
	class I2CBase_x {
		private:
			using Trait = I2CTrait<channel_>;
			static constexpr uint32_t _i2cAddr = Trait::i2cAddr;
			static constexpr uint32_t _rccEnableAddr = Trait::rccEnableAddr;
			static constexpr uint32_t _rccEnablePos = Trait::rccEnablePos;
			static constexpr uint32_t _rccResetAddr = Trait::rccResetAddr;
			static constexpr uint32_t _rccResetPos = Trait::rccResetPos;

		public:
			static constexpr I2CChannel channel = channel_;

		public:

			/// \brief Activa el modul I2Cx
			///
			static void activate() {

				uint32_t *ptr = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*ptr |= 1 << _rccEnablePos;
			}

			/// \brief Desactiva el modul I2Cx
			///
			static void deactivate() {

				uint32_t *ptr = reinterpret_cast<uint32_t*>(_rccEnableAddr);
				*ptr &= ~(1 << _rccEnablePos);
			}

			/// \brief Reseteja el modul I2Cx
			///
			static void reset() {

            	volatile uint32_t *ptr = reinterpret_cast<volatile uint32_t*>(_rccResetAddr);
            	*ptr |= 1 << _rccResetPos;
            	*ptr &= ~(1 << _rccResetPos);
			}

			/// \brief Habilita el modul I2Cx
			///
			static void enable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
				regs->CR1 |= I2C_CR1_PE;
			}

			/// \brief Deshabilita el modul I2Cx
			///
			static void disable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
				regs->CR1 &= ~I2C_CR1_PE;
			}
			/// \brief Inicialitza el pin SCL
			///
            template <typename gpio_>
			static void initSCLPin() {

            	gpio_::initAlt(
            		GPIODriver::openDrain,
					GPIOSpeed::fast,
					I2CPinTrait<channel_, gpio_, I2CPin::SCL>::alt);
			}

            /// \brief Inicialitza el pin SDA
            ///
            template <typename gpio_>
			static void initSDAPin() {

            	gpio_::initAlt(
            		GPIODriver::openDrain,
					GPIOSpeed::fast,
					I2CPinTrait<channel_, gpio_, I2CPin::SDA>::alt);
			}

            /// \brief Habilita una interrupcio.
            /// \param interrupt: L'interrupcio a habilitar.
            ///
            static void enableInterrupt(
                I2CInterrupt interrupt) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);

                switch (interrupt) {
                	case I2CInterrupt::addr:
                		regs->CR1 |= I2C_CR1_ADDRIE;
                		break;
                	case I2CInterrupt::rx:
                		regs->CR1 |= I2C_CR1_RXIE;
                		break;
                	case I2CInterrupt::tx:
                		regs->CR1 |= I2C_CR1_TXIE;
                		break;
                	case I2CInterrupt::err:
                        regs->CR1 |= I2C_CR1_ERRIE;
                        break;
                    case I2CInterrupt::stop:
                        regs->CR1 |= I2C_CR1_STOPIE;
                        break;
                    case I2CInterrupt::tc:
                        regs->CR1 |= I2C_CR1_TCIE;
                        break;
                    default:
                    	break;
                }
            }

            /// \brief Deshabilita una interrupcio.
            /// \param interrupt: L'interrupcio a deshabilitar.
            /// \return True si la interrupcio estava habilitada, false en cas contrari.
            ///
            static bool disableInterrupt(
                I2CInterrupt interrupt) {

            	bool state = false;

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	switch (interrupt) {
            		case I2CInterrupt::addr:
            			state = (regs->CR1 & I2C_CR1_ADDRIE) != 0;
                		regs->CR1 &= ~I2C_CR1_ADDRIE;
            			break;
            		case I2CInterrupt::rx:
            			state = (regs->CR1 & I2C_CR1_RXIE) != 0;
                		regs->CR1 &= ~I2C_CR1_RXIE;
            			break;
            		case I2CInterrupt::tx:
            			state = (regs->CR1 & I2C_CR1_TXIE) != 0;
                		regs->CR1 &= ~I2C_CR1_TXIE;
            			break;
            		case I2CInterrupt::stop:
            			state = (regs->CR1 & I2C_CR1_STOPIE) != 0;
                		regs->CR1 &= ~I2C_CR1_STOPIE;
            			break;
            		default:
            			break;
            	}

            	return state;
            }

            /// \brief Comproba si una interrupcio esta habilitada.
            /// \para interrupt: L'interrupcio.
            /// \return True si esta habilitada, false en cas contrari.
            ///
            static bool isInterruptEnabled(
                I2CInterrupt interrupt) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);

            	switch (interrupt) {
            		case I2CInterrupt::addr:
            			return (regs->CR1 & I2C_CR1_ADDRIE) != 0;
            		case I2CInterrupt::rx:
            			return (regs->CR1 & I2C_CR1_RXIE) != 0;
            		case I2CInterrupt::tx:
            			return (regs->CR1 & I2C_CR1_TXIE) != 0;
            		case I2CInterrupt::stop:
            			return (regs->CR1 & I2C_CR1_STOPIE) != 0;
            		default:
            			return false;
            	}
            }

            /// \brief Obte el valor d'un flag.
            /// \param flag: El flag;
            /// \return El valor del flag.
            ///
            static bool getFlag(
                I2CFlag flag) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);

            	switch (flag) {
            		case I2CFlag::addr:
            			return (regs->ISR & I2C_ISR_ADDR) != 0;
            		case I2CFlag::rxne:
            			return (regs->ISR & I2C_ISR_RXNE) != 0;
            		case I2CFlag::txis:
            			return (regs->ISR & I2C_ISR_TXIS) != 0;
            		case I2CFlag::nack:
            			return (regs->ISR & I2C_ISR_NACKF) != 0;
            		case I2CFlag::stop:
            			return (regs->ISR & I2C_ISR_STOPF) != 0;
            		default:
            			return false;
            	}
            }

            /// \brief Borra un flag.
            /// \param flag: El flag.
            ///
            static void clearFlag(
                I2CFlag flag) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);

            	switch (flag) {
            		case I2CFlag::addr:
            			regs->ICR |= I2C_ICR_ADDRCF;
            			break;
            		case I2CFlag::stop:
            			regs->ICR |= I2C_ICR_STOPCF;
            			break;
            		case I2CFlag::nack:
            			regs->ICR |= I2C_ICR_NACKCF;
            			break;
            		default:
            			break;
            	}
            }
	};

	template <I2CChannel channel_>
	class I2CMaster_x: public I2CBase_x<channel_> {
		private:
			using Trait = I2CTrait<channel_>;
			static constexpr uint32_t _i2cAddr = Trait::i2cAddr;
	};

	template <I2CChannel channel_>
	class I2CSlave_x: public I2CBase_x<channel_> {
		private:
			using Trait = I2CTrait<channel_>;
			static constexpr uint32_t _i2cAddr = Trait::i2cAddr;

		private:
			static I2CInterruptParam _isrParam;
			static I2CInterruptFunction _isrFunction;

		private:
			I2CSlave_x() = delete;
			I2CSlave_x(const I2CSlave_x &) = delete;
			I2CSlave_x(const I2CSlave_x &&) = delete;
            ~I2CSlave_x() = delete;
            
			I2CSlave_x & operator = (const I2CSlave_x &) = delete;
			I2CSlave_x & operator = (const I2CSlave_x &&) = delete;

		public:

			/// \brief Inicialitza el modul
			/// \param addr: Adressa I2C.
			///
			static void initialize(
				uint8_t addr) {

				I2CBase_x<channel_>::activate();
				I2CBase_x<channel_>::disable();

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);

				regs->OAR1 = I2C_OAR1_OA1EN | ((addr << I2C_OAR1_OA1_Pos) & I2C_OAR1_OA1_Msk);
				regs->OAR2 = 0;
				regs->CR1 &= ~(I2C_CR1_NOSTRETCH | I2C_CR1_SBC);
				//regs->CR1 |= I2C_CR1_SBC;
				//regs->CR2 |= I2C_CR2_RELOAD;

				_isrFunction = nullptr;
				_isrParam = nullptr;
			}

			/// \brief Desinicialitza el modul.
			///
            static void deinitialize() {

            	I2CBase_x<channel_>::disable();
            	I2CBase_x<channel_>::deactivate();
            }

            /// \brief Selecciona el clock
			/// \param source: Clock origen
			///
			static void setClockSource(
				I2CClockSource source) {

				#ifdef HTL_I2C1_EXIST
				#if defined(EOS_PLATFORM_STM32G0)
				if constexpr (channel_ == I2CChannel::_1) {
					uint32_t tmp = RCC->CCIPR;
					tmp &= ~RCC_CCIPR_I2C1SEL_Msk;
					switch (source) {
						case I2CClockSource::hsi16:
							tmp |= 0b10 << RCC_CCIPR_I2C1SEL_Pos;
							break;
						case I2CClockSource::sysclk:
							tmp |= 0b01 << RCC_CCIPR_I2C1SEL_Pos;
							break;
						default:
							break;
					}
					RCC->CCIPR = tmp;
				}
				#endif
				#endif
			}

			/// \brief Configuracio del timing
			/// \param prescaler:
			/// \param scldel:
			/// \param sdadel:
			/// \param sclh:
			/// \param scll:
			///
			static void setTimming(
				uint8_t prescaler,
				uint8_t scldel,
				uint8_t sdadel,
				uint8_t sclh,
				uint8_t scll) {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
				regs->TIMINGR =
					((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
					((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
					((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
					((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
					((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);
			}
            
            /// \brief Asigna la funcio d'interrupcio.
            ///
            static void setInterruptFunction(
            	I2CInterruptFunction function,
				I2CInterruptParam param) {

            	_isrFunction = function;
            	_isrParam = param;
            }

            /// \brief Funcio d'interrupcio.
            /// \remarks Aquesta funcio correspon al vector d'interrupcio I2C
            ///
            static void interruptHandler() {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	uint32_t cr1 = regs->CR1;
            	uint32_t isr = regs->ISR;
            	uint32_t icr = regs->ICR;

    			if ((cr1 & I2C_CR1_ADDRIE) && (isr & I2C_ISR_ADDR)) {

                	cr1 &= ~I2C_CR1_ADDRIE;
                	if (isr & I2C_ISR_DIR)
                		cr1 |= I2C_CR1_TXIE;
                	else
                		cr1 |= I2C_CR1_RXIE | I2C_CR1_NACKIE;
            		cr1 |= I2C_CR1_STOPIE;

                	icr |= I2C_ICR_ADDRCF;

                	// _context->count = 0;

                	if (_isrFunction != nullptr)
                		_isrFunction(I2CInterruptNotify::addrMatch, _isrParam);
    			}

    			if ((cr1 & I2C_CR1_RXIE) &&	(isr & I2C_ISR_RXNE)) {

    				//if (_context->count < _context->size)
    					//_context->buffer[_context->count++] = regs->RXDR;

                	if (_isrFunction != nullptr)
                		_isrFunction(I2CInterruptNotify::rxNotEmpty, _isrParam);
    			}

    			if ((cr1 & I2C_CR1_TXIE) && (isr & I2C_ISR_TXE)) {

    				//if (_context->count < _context->size)
    					//regs->TXDR = _context->buffer[_context->count++];

    				if (_isrFunction != nullptr)
                		_isrFunction(I2CInterruptNotify::txEmpty, _isrParam);
    			}

    			if ((cr1 & I2C_CR1_NACKIE) && (isr & I2C_ISR_NACKF)) {

                	if (_isrFunction != nullptr)
                		_isrFunction(I2CInterruptNotify::nack, _isrParam);
    			}

    			if ((cr1 & I2C_CR1_STOPIE) && (isr & I2C_ISR_STOPF)) {

                	cr1 &= ~(I2C_CR1_RXIE | I2C_CR1_TXIE | I2C_CR1_STOPIE | I2C_CR1_NACKIE);
                	cr1 |= I2C_CR1_ADDRIE;

                	icr |= I2C_ICR_STOPCF;

                	if (_isrFunction != nullptr)
                		_isrFunction(I2CInterruptNotify::completted, _isrParam);
    			}

    			regs->CR1 = cr1;
    			regs->ICR = icr;
            }

            /// \brief Llegeix un byte.
            /// \return El byte lleigit.
            ///
            static uint8_t read() {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	return regs->RXDR;
            }

            /// \brief Escriu un byte
            /// \return El byte lleigit.
            ///
            static void write(uint8_t data) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	regs->TXDR = data;
            }

            /// \brief Genera NACK
            ///
            static void nack() {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	regs->CR2 |= I2C_CR2_NACK;
            }

            /// \brief Genera ACK
            ///
            static void ack() {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
            	regs->CR2 &= ~I2C_CR2_NACK;
            }

            static uint16_t read(uint8_t *buffer, uint16_t size, uint32_t timeout) {

            	return 0;
            }

            static void readIT(uint8_t *buffer, uint16_t size, I2CTransferContext *context) {

            	//_context = context;
            }

            /*static bool listenIT(uint8_t *buffer, uint16_t size, I2CTransferContext *context) {

            	_context = context;
            	_context->buffer = buffer;
            	_context->size = size;

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_i2cAddr);
        		regs->CR1 |= I2C_CR1_ADDRIE;
            }*/
	};

	//template <I2CChannel channel_> I2CSlaveContext I2CSlave_x<channel_>::_context;
	template <I2CChannel channel_> I2CInterruptFunction I2CSlave_x<channel_>::_isrFunction;
	template <I2CChannel channel_> I2CInterruptParam I2CSlave_x<channel_>::_isrParam;

	#ifdef HTL_I2C1_EXIST
	using I2CMaster_1 = I2CMaster_x<I2CChannel::_1>;
	using I2CSlave_1 = I2CSlave_x<I2CChannel::_1>;
	#endif
	#ifdef HTL_I2C2_EXIST
	using I2CMaster_2 = I2CMaster_x<I2CChannel::_2>;
	using I2CSlave_2 = I2CSlave_x<I2CChannel::_2>;
	#endif
	#ifdef HTL_I2C3_EXIST
	using I2CMaster_3 = I2CMaster_x<I2CChannel::_3>;
	using I2CSlave_3 = I2CSlave_x<I2CChannel::_3>;
	#endif
	#ifdef HTL_I2C4_EXIST
	using I2CMaster_4 = I2CMaster_x<I2CChannel::_4>;
	using I2CSlave_4 = I2CSlave_x<I2CChannel::_4>;
	#endif

	#ifdef HTL_I2C1_EXIST
	template <>
	struct I2CTrait<I2CChannel::_1> {
		static constexpr uint32_t i2cAddr = I2C1_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
		static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C1EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
		static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C1RST_Pos;
		#elif defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C1RST_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C1EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C1RST_Pos;
		#endif
	};
	#endif

	#ifdef HTL_I2C2_EXIST
	template <>
	struct I2CTrait<I2CChannel::_2> {
		static constexpr uint32_t i2cAddr = I2C2_BASE;
		#if defined(EOS_PLATFORM_STM32G0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APBENR1);
		static constexpr uint32_t rccEnablePos = RCC_APBENR1_I2C2EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APBRSTR1);
		static constexpr uint32_t rccResetPos = RCC_APBRSTR1_I2C2RST_Pos;
		#elif defined(EOS_PLATFORM_STM32F0)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C2RST_Pos;
		#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C2EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C2RST_Pos;
		#endif
	};
	#endif

	#ifdef HTL_I2C3_EXIST
	template <>
	struct I2CTrait<I2CChannel::_3> {
		static constexpr uint32_t i2cAddr = I2C3_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C3EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C3RST_Pos;
		#endif
	};
	#endif

	#ifdef HTL_I2C4_EXIST
	template <>
	struct I2CTrait<I2CChannel::_4> {
		static constexpr uint32_t i2cAddr = I2C4_BASE;
		#if defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)
		static constexpr uint32_t rccEnableAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1ENR);
		static constexpr uint32_t rccEnablePos = RCC_APB1ENR_I2C4EN_Pos;
		static constexpr uint32_t rccResetAddr = RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR);
		static constexpr uint32_t rccResetPos = RCC_APB1RSTR_I2C4RST_Pos;
		#endif
	};
	#endif
}


#if defined(EOS_PLATFORM_STM32G030)
    #include "htl/STM32/htlI2C_AF_G030.h"

#elif defined(EOS_PLATFORM_STM32G031)
    #include "htl/STM32/htlI2C_AF_G031.h"

#elif defined(EOS_PLATFORM_STM32F030)
    #include "htl/STM32/htlI2C_AF_F030.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlI2C_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlI2C_AF_F7.h"

#else
    #error "Unknown platform"
#endif


#endif // __STM32_htlI2C__

