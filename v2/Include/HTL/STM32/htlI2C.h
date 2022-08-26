#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "HTL/htl.h"
#include "HTL/STM32/htlGPIO.h"


#ifndef DISCOVERY_I2Cx_TIMING
#define DISCOVERY_I2Cx_TIMING     ((uint32_t)0x40912732)
#endif


namespace htl {

	enum class I2CChannel {
		#ifdef I2C1_BASE
			_1,
		#endif
		#ifdef I2C2_BASE
			_2,
		#endif
		#ifdef I2C3_BASE
			_3,
		#endif
		#ifdef I2C4_BASE
			_4
		#endif
	};

	enum class I2CEvent {
	};

	enum class I2CError {
		none
	};

	enum class I2CPin {
		SCL,
		SDA
	};

	using I2CInterruptParam = void*;
	using I2CInterruptFunction = void (*)(I2CEvent, I2CInterruptParam);

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

			static I2CInterruptParam _isrParam;
			static I2CInterruptFunction _isrFunction;

		protected:
			static I2C_HandleTypeDef _handle;

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

				#ifdef I2C1_BASE
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2_BASE
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3_BASE
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4_BASE
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
				#endif
            }

			/// \brief Desactiva el modul
			///
            static void deactivate() {

				#ifdef I2C1_BASE
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2_BASE
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3_BASE
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4_BASE
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C4EN;
				#endif
            }

		protected:
            /// \brief Inicialitza edl modul en modus master
            ///
			static bool initMaster() {

				activate();
				disable();

				I2C_TypeDef *regs= reinterpret_cast<I2C_TypeDef*>(_addr);

				_handle.Instance = regs;
				_handle.Init.Timing           = DISCOVERY_I2Cx_TIMING;
			    _handle.Init.OwnAddress1      = 0;
			    _handle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
			    _handle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
			    _handle.Init.OwnAddress2      = 0;
			    _handle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
			    _handle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
				if (HAL_I2C_Init(&_handle) != HAL_OK)
					return false;

				enable();

				return true;
			}
            
		public:
			/// \brief Desinicialitza el modul.
			///
            static void deinitialize() {
                
            	disable();

            	HAL_I2C_DeInit(&_handle);

            	deactivate();
            }

            /// \brief Obte el codi de l'ultime error i el reseteja
            /// \return El codi d'error.
            ///
            static I2CError getError() {

            	return I2CError::none;
            }

            /// \brief Activa la comunicacio
            //
			static void enable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 |= I2C_CR1_PE;
			}

			/// \brief Desactiva la comunicacio
			///
			static void disable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
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

            /// \brief Asigna la funcio d'interrupcio.
            ///
            static void setInterruptFunction(
            	I2CInterruptFunction function,
				I2CInterruptParam param) {

            	_isrFunction = function;
            	_isrParam = param;
            }

            /// \brief Invoca la funcio d'interrupcio.
            /// \param event: L'event.
            /// \param param: El parametre.
            ///
            static void interruptHandler(
            	I2CEvent event) {

            	if (_isrFunction != nullptr)
            		_isrFunction(event, _isrParam);
            }
	};

	template <I2CChannel channel_> I2C_HandleTypeDef I2C_x<channel_>::_handle;
	template <I2CChannel channel_> I2CInterruptFunction I2C_x<channel_>::_isrFunction;
	template <I2CChannel channel_> I2CInterruptParam I2C_x<channel_>::_isrParam;

	template <I2CChannel channel_>
	class I2CMaster_x final: public I2C_x<channel_> {
		public:
			static void initialize() {

				I2C_x<channel_>::initMaster();
			}

			/// \brief Envia un bloc de dades al esclau
			/// \param addr: Adressa I2C.
			/// \param data: Buffer de dades.
			/// \param dataLength: Numero de bytes en el buffer.
			/// \param timeout: Temps maxim de bloqueig.
			///
			static bool send(
				uint8_t addr,
				const uint8_t *data,
				unsigned dataLength,
				unsigned timeout = 1000) {

				if (HAL_I2C_Master_Transmit(
					&I2C_x<channel_>::_handle,
					addr,
					(uint8_t*) data,
					dataLength,
					timeout) != HAL_OK)
					return false;

				return true;
			}

			/// \brief Reb un bloc de dades del esclau.
			/// \param addr: Adressa I2C.
			/// \param data: Buffer de dades.
			/// \param dataSize: Tamany del buffer de dades.
			/// \param timeout: Temps maxim de bloqueig.
			///
			static bool receive(
				uint8_t addr,
				uint8_t *data,
				unsigned dataSize,
				unsigned timeout = 1000) {

				if (HAL_I2C_Master_Receive(
					&I2C_x<channel_>::_handle,
					addr,
					data,
					dataSize,
					timeout) != HAL_OK)
					return false;

				return true;
			}
	};

	template <I2CChannel channel_>
	class I2CSlave_x final: public I2C_x<channel_> {
		public:
			static bool send() {

				return false;
			}

			static bool reveive() {

				return false;
			}
	};

	#ifdef I2C1_BASE
		using I2CMaster_1 = I2CMaster_x<I2CChannel::_1>;
		using I2CSlave_1 = I2CSlave_x<I2CChannel::_1>;
	#endif

	#ifdef I2C2_BASE
		using I2CMaster_2 = I2CMaster_x<I2CChannel::_2>;
		using I2CSlave_2 = I2CSlave_x<I2CChannel::_2>;
	#endif

	#ifdef I2C3_BASE
		using I2CMaster_3 = I2CMaster_x<I2CChannel::_3>;
		using I2CSlave_3 = I2CSlave_x<I2CChannel::_3>;
	#endif

	#ifdef I2C4_BASE
		using I2CMaster_4 = I2CMaster_x<I2CChannel::_4>;
		using I2CSlave_4 = I2CSlave_x<I2CChannel::_4>;
	#endif

	#ifdef I2C1_BASE
		template <>
		struct I2CTrait<I2CChannel::_1> {
			static constexpr uint32_t addr = I2C1_BASE;
		};

		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B6, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
		template<>
		struct I2CPinTrait<I2CChannel::_1, GPIO_B7, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
	#endif

	#ifdef I2C2_BASE
		template <>
		struct I2CTrait<I2CChannel::_2> {
			static constexpr uint32_t addr = I2C2_BASE;
		};
	#endif

	#ifdef I2C3_BASE
		template <>
		struct I2CTrait<I2CChannel::_3> {
			static constexpr uint32_t addr = I2C3_BASE;
		};

		template <>
		struct I2CPinTrait<I2CChannel::_3, GPIO_H7, I2CPin::SCL> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
		template <>
		struct I2CPinTrait<I2CChannel::_3, GPIO_H8, I2CPin::SDA> {
			static constexpr GPIOAlt alt = GPIOAlt::_4;
		};
	#endif

	#ifdef I2C4_BASE
		template <>
		struct I2CTrait<I2CChannel::_4> {
			static constexpr uint32_t addr = I2C4_BASE;
		};
	#endif
}


#endif // __STM32_htlI2C__

