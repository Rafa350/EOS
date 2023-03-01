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

	using I2CInterruptParam = void*;
	using I2CInterruptFunction = void (*)(I2CInterruptParam);

	template <I2CChannel>
	class I2CTrait {
	};

	template <I2CChannel, typename, I2CPin>
	struct I2CPinTrait {
	};

	template <I2CChannel channel_>
	class I2C_x {
		private:
			using Trait = I2CTrait<channel_>;
			static constexpr uint32_t _addr = Trait::addr;

		private:
			static I2CInterruptParam _isrParam;
			static I2CInterruptFunction _isrFunction;

		public:
			static constexpr I2CChannel channel = channel_;

		private:
			I2C_x() = delete;
			I2C_x(const I2C_x &) = delete;
			I2C_x(const I2C_x &&) = delete;
            ~I2C_x() = delete;
            
			I2C_x & operator = (const I2C_x &) = delete;
			I2C_x & operator = (const I2C_x &&) = delete;

		private:

			/// \brief Activa el modul
			///
			static void activate() {

				#ifdef HTL_I2C1_EXIST
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef HTL_I2C2_EXIST
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef HTL_I2C3_EXIST
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef HTL_I2C4_EXIST
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
				#endif
            }

			/// \brief Desactiva el modul
			///
            static void deactivate() {

				#ifdef HTL_I2C1_EXIST
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef HTL_I2C2_EXIST
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef HTL_I2C3_EXIST
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef HTL_I2C4_EXIST
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C4EN;
				#endif
            }

		public:
            /// \brief Inicialitza edl modul en modus master
            ///
			static bool initMaster() {

				activate();
				disable();

				I2C_TypeDef *regs= reinterpret_cast<I2C_TypeDef*>(_addr);

				/*_handle.Instance = regs;
				_handle.Init.Timing           = (uint32_t)0x40912732;
			    _handle.Init.OwnAddress1      = 0;
			    _handle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
			    _handle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
			    _handle.Init.OwnAddress2      = 0;
			    _handle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
			    _handle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
				if (HAL_I2C_Init(&_handle) != HAL_OK)
					return false;

				enable();
*/
				return true;
			}

			/// \brief Inicialitza el modul com escalu
			// \param addr: Adressa.
			//
			static void initSlave(
				uint8_t addr) {

				activate();
				disable();

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->OAR1 = I2C_OAR1_OA1EN | (addr & 0x3FF);
				regs->OAR2 = 0;
				regs->CR1 &= ~(I2C_CR1_SBC | I2C_CR1_NOSTRETCH);
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

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->TIMINGR =
					((prescaler << I2C_TIMINGR_PRESC_Pos) & I2C_TIMINGR_PRESC_Msk) |
					((scldel << I2C_TIMINGR_SCLDEL_Pos) & I2C_TIMINGR_SCLDEL_Msk) |
					((sdadel << I2C_TIMINGR_SDADEL_Pos) & I2C_TIMINGR_SDADEL_Msk) |
					((sclh << I2C_TIMINGR_SCLH_Pos) & I2C_TIMINGR_SCLH_Msk) |
					((scll << I2C_TIMINGR_SCLL_Pos) & I2C_TIMINGR_SCLL_Msk);
			}
            
			/// \brief Desinicialitza el modul.
			///
            static void deinitialize() {
                
            	disable();
            	deactivate();
            }

            /// \brief Activa lel dispositiu
            //
			static void enable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 |= I2C_CR1_PE;
			}

			/// \brief Desactiva el dispositiu
			///
			static void disable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 &= ~I2C_CR1_PE;
			}
            
            /// \brief Reset per software del dispositiu.
            ///
            static void reset() {
				#ifdef HTL_I2C1_EXIST
					if constexpr (channel_ == I2CChannel::_1) {
						RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
					}
				#endif
				#ifdef HTL_I2C2_EXIST
					if constexpr (channel_ == I2CChannel::_2) {
						RCC->APB1RSTR |= RCC_APB1RSTR_I2C2RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C2RST;
					}
				#endif
				#ifdef HTL_I2C3_EXIST
					if constexpr (channel_ == I2CChannel::_3) {
						RCC->APB1RSTR |= RCC_APB1RSTR_I2C3RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C3RST;
					}
				#endif
				#ifdef HTL_I2C4_EXIST
					if constexpr (channel_ == I2CChannel::_4) {
						RCC->APB1RSTR |= RCC_APB1RSTR_I2C4RST;
						RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C4RST;
					}
				#endif

				_isrFunction = nullptr;
				_isrParam = nullptr;
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

            /// \brief Asigna la funcio d'interrupcio.
            ///
            static void setInterruptFunction(
            	I2CInterruptFunction function,
				I2CInterruptParam param) {

            	_isrFunction = function;
            	_isrParam = param;
            }

            /// \brief Invoca la funcio d'interrupcio.
            ///
            static void interruptHandler() {

            	if (_isrFunction != nullptr)
            		_isrFunction(_isrParam);
            }
            
            /// \brief Habilita una interrupcio.
            /// \param interrupt: L'interrupcio a habilitar.
            ///
            static void enableInterrupt(
                I2CInterrupt interrupt) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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
            ///
            static bool disableInterrupt(
                I2CInterrupt interrupt) {

            	bool state = false;

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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
            /// \return True si esta habiolitada.
            ///
            static bool isInterruptEnabled(
                I2CInterrupt interrupt) {

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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

            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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

            /// \brief Llegeix un byte.
            /// \return El byte lleigit.
            ///
            static uint8_t read() {
            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
            	return regs->RXDR;
            }

            /// \brief Escriu un byte
            /// \return El byte lleigit.
            ///
            static void write(uint8_t data) {
            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
            	regs->TXDR = data;
            }

            /// \brief Genera NACK
            ///
            static void nack() {
            	I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
            	regs->CR2 |= I2C_CR2_NACK;
            }
	};

	template <I2CChannel channel_> I2CInterruptFunction I2C_x<channel_>::_isrFunction;
	template <I2CChannel channel_> I2CInterruptParam I2C_x<channel_>::_isrParam;

	#ifdef HTL_I2C1_EXIST
	    using I2C_1 = I2C_x<I2CChannel::_1>;
	#endif
	#ifdef HTL_I2C2_EXIST
	    using I2C_2 = I2C_x<I2CChannel::_2>;
	#endif
	#ifdef HTL_I2C3_EXIST
	    using I2C_3 = I2C_x<I2CChannel::_3>;
	#endif
	#ifdef HTL_I2C4_EXIST
	    using I2C_4 = I2C_x<I2CChannel::_4>;
	#endif

	#ifdef HTL_I2C1_EXIST
		template <>
		struct I2CTrait<I2CChannel::_1> {
			static constexpr uint32_t addr = I2C1_BASE;
		};
	#endif

	#ifdef HTL_I2C2_EXIST
		template <>
		struct I2CTrait<I2CChannel::_2> {
			static constexpr uint32_t addr = I2C2_BASE;
		};
	#endif

	#ifdef HTL_I2C3_EXIST
		template <>
		struct I2CTrait<I2CChannel::_3> {
			static constexpr uint32_t addr = I2C3_BASE;
		};
	#endif

	#ifdef HTL_I2C4_EXIST
		template <>
		struct I2CTrait<I2CChannel::_4> {
			static constexpr uint32_t addr = I2C4_BASE;
		};
	#endif
}


#if defined(EOS_PLATFORM_STM32G031Fx)
    #include "htl/STM32/htlI2C_AF_G031F.h"
#elif defined(EOS_PLATFORM_STM32G031Jx)
    #include "htl/STM32/htlUART_AF_G031J.h"
#elif defined(EOS_PLATFORM_STM32G031Kx)
    #include "htl/STM32/htlI2C_AF_G031K.h"

#elif defined(EOS_PLATFORM_STM32F030R8)
    #include "htl/STM32/htlI2C_AF_F030R.h"

#elif defined(EOS_PLATFORM_STM32F4)
    #include "htl/STM32/htlI2C_AF_F4.h"

#elif defined(EOS_PLATFORM_STM32F7)
    #include "htl/STM32/htlI2C_AF_F7.h"

#else
    #error Plataforma no soportada
#endif


#endif // __STM32_htlI2C__

