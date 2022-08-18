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
		#ifdef I2C1
			_1,
		#endif
		#ifdef I2C2
			_2,
		#endif
		#ifdef I2C3
			_3,
		#endif
		#ifdef I2C4
			_4
		#endif
	};

	enum class I2CEvent {
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

			static constexpr unsigned _defaultBlockTime = 1000;
			static constexpr uint32_t _addr = Trait::addr;

			static I2C_HandleTypeDef _handle;
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
			inline static void activate() {

				#ifdef I2C1
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
				#endif
            }

			/// \brief Desactiva el modul
			///
            inline static void deactivate() {

				#ifdef I2C1
					if constexpr (channel_ == I2CChannel::_1)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2
					if constexpr (channel_ == I2CChannel::_2)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3
					if constexpr (channel_ == I2CChannel::_3)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4
					if constexpr (channel_ == I2CChannel::_4)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C4EN;
				#endif
            }

		protected:
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
            inline static void deInit() {
                
            	disable();

            	HAL_I2C_DeInit(&_handle);

            	deactivate();
            }

            /// \brief Activa la comunicacio
            //
			inline static void enable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 |= I2C_CR1_PE;
			}

			/// \brief Desactiva la comunicacio
			///
			inline static void disable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 &= ~I2C_CR1_PE;
			}

			/// \brief Envia un bloc de dades al esclau
			/// \param addr: Adressa I2C.
			/// \param data: Les dades a transmetre.
			/// \param size: Numero de bytes a transmetre.
			/// \param blockTime: Temps maxim de bloqueig.
			///
			inline static bool send(
				uint8_t addr,
				const void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				return HAL_I2C_Master_Transmit(
					&_handle,
					addr,
					(uint8_t*)data,
					size,
					blockTime) == HAL_OK;
			}

			inline static bool receive(
				uint8_t addr,
				void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				return HAL_I2C_Master_Receive(
					&_handle,
					addr,
					(uint8_t*) data,
					size,
					blockTime) == HAL_OK;
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
			static void init() {

				I2C_x<channel_>::initMaster();
			}
	};

	template <I2CChannel channel_>
	class I2CSlave_x final: public I2C_x<channel_> {

	};

	#ifdef I2C1
		using I2C_1 = I2C_x<I2CChannel::_1>;
		using I2CMaster_1 = I2CMaster_x<I2CChannel::_1>;
		using I2CSlave_1 = I2CSlave_x<I2CChannel::_1>;
	#endif

	#ifdef I2C2
		using I2C_2 = I2C_x<I2CChannel::_2>;
		using I2CMaster_2 = I2CMaster_x<I2CChannel::_2>;
		using I2CSlave_2 = I2CSlave_x<I2CChannel::_2>;
	#endif

	#ifdef I2C3
		using I2C_3 = I2C_x<I2CChannel::_3>;
		using I2CMaster_3 = I2CMaster_x<I2CChannel::_3>;
		using I2CSlave_3 = I2CSlave_x<I2CChannel::_3>;
	#endif

	#ifdef I2C4
		using I2C_4 = I2C_x<I2CChannel::_4>;
		using I2CMaster_4 = I2CMaster_x<I2CChannel::_4>;
		using I2CSlave_4 = I2CSlave_x<I2CChannel::_4>;
	#endif

	#ifdef I2C1
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

	#ifdef I2C2
		template <>
		struct I2CTrait<I2CChannel::_2> {
			static constexpr uint32_t addr = I2C2_BASE;
		};
	#endif

	#ifdef I2C3
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

	#ifdef I2C4
		template <>
		struct I2CTrait<I2CChannel::_4> {
			static constexpr uint32_t addr = I2C4_BASE;
		};
	#endif
}


#endif // __STM32_htlI2C__

