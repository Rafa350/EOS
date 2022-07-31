#pragma once
#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halI2C.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class I2CChannel: halI2CChannel {
		#ifdef I2C1
			channel1 = HAL_I2C_CHANNEL_1,
		#endif
		#ifdef I2C2
			channel2 = HAL_I2C_CHANNEL_2,
		#endif
		#ifdef I2C3
			channel3 = HAL_I2C_CHANNEL_3,
		#endif
		#ifdef I2C4
			channel4 = HAL_I2C_CHANNEL_4
		#endif
	};

	enum class I2CEvent {

	};

	enum class I2CPin {
		pinSCL,
		pinSDA
	};

	enum class I2CResult: halI2CResult {
		ok = HAL_I2C_OK,
	    error = HAL_I2C_ERR,
		timeout = HAL_I2C_ERR_TIMEOUT,
		busy = HAL_I2C_ERR_BUSY
	};

	using I2CInterruptParam = void*;
	using I2CInterruptFunction = void (*)(I2CEvent, I2CInterruptParam);

	template <I2CChannel channel_>
	class I2CTrait {
	};

	template <I2CChannel channel_, typename gpio_, I2CPin>
	struct I2CPinTrait {
	};

	template <I2CChannel channel_>
	class I2C_x final {
		private:
			using Trait = I2CTrait<channel_>;
			static constexpr unsigned _defaultBlockTime = 1000;
			static constexpr uint32_t _addr = Trait::addr;

			static halI2CHandler _handler;
			static halI2CData _data;
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

			inline static void activate() {

				#ifdef I2C1
					if constexpr (channel_ == I2CChannel::channel1)
						RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2
					if constexpr (channel_ == I2CChannel::channel2)
						RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3
					if constexpr (channel_ == I2CChannel::channel3)
						RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4
					if constexpr (channel_ == I2CChannel::channel4)
						RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
				#endif
            }

            inline static void deactivate() {

				#ifdef I2C1
					if constexpr (channel_ == I2CChannel::channel1)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
				#endif
				#ifdef I2C2
					if constexpr (channel_ == I2CChannel::channel2)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
				#endif
				#ifdef I2C3
					if constexpr (channel_ == I2CChannel::channel3)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
				#endif
				#ifdef I2C4
					if constexpr (channel_ == I2CChannel::channel4)
						RCC->APB1ENR &= ~RCC_APB1ENR_I2C4EN;
				#endif
            }

		public:
			static I2CResult initMaster() {

				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}
            
            inline static void deInit() {
                
            	deactivate();
            }

			inline static void enable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 |= I2C_CR1_PE;
			}

			inline static void disable() {

				I2C_TypeDef *regs = reinterpret_cast<I2C_TypeDef*>(_addr);
				regs->CR1 &= ~I2C_CR1_PE;
			}

			inline static I2CResult send(
				uint8_t addr,
				const void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				return I2CResult(halI2CMasterSend(_handler, addr, data, size, blockTime));
			}

			inline static I2CResult receive(
				uint8_t addr,
				void *data,
				int size,
				unsigned blockTime = _defaultBlockTime) {

				return I2CResult(halI2CMasterReceive(_handler, addr, data, size, blockTime));
			}

			/// \brief Inicialitza el pin SCL
			///
            template <typename gpio_>
			static void initSCLPin() {
				gpio_::initAlt(htl::GPIODriver::openDrain, htl::GPIOSpeed::fast, I2CPinTrait<channel_, gpio_, I2CPin::pinSCL>::alt);
			}

            /// \brief Inicialitza el pin SDA
            ///
            template <typename gpio_>
			static void initSDAPin() {
				gpio_::initAlt(htl::GPIODriver::openDrain, htl::GPIOSpeed::fast, I2CPinTrait<channel_, gpio_, I2CPin::pinSDA>::alt);
			}

            /// \brief Asigna la funcio d'interrupcio.
            ///
            static void setInterruptFunction(
            	I2CInterruptFunction function,
				I2CInterruptParam param) {

            	_isrFunction = function;
            	_isrParam = param;
            }
	};

	template <I2CChannel channel_> halI2CHandler I2C_x<channel_>::_handler;
	template <I2CChannel channel_> halI2CData I2C_x<channel_>::_data;
	template <I2CChannel channel_> I2CInterruptFunction I2C_x<channel_>::_isrFunction;
	template <I2CChannel channel_> I2CInterruptParam I2C_x<channel_>::_isrParam;

	#ifdef I2C1
		using I2C_1 = I2C_x<I2CChannel::channel1>;
	#endif

	#ifdef I2C2
		using I2C_2 = I2C_x<I2CChannel::channel2>;
	#endif

	#ifdef I2C3
		using I2C_3 = I2C_x<I2CChannel::channel3>;
	#endif

	#ifdef I2C4
		using I2C_4 = I2C_x<I2CChannel::channel4>;
	#endif

	#ifdef I2C1
		template <>
		struct I2CTrait<I2CChannel::channel1> {
			static constexpr uint32_t addr = I2C1_BASE;
		};

		template<>
		struct I2CPinTrait<I2CChannel::channel1, GPIO_B6, I2CPin::pinSCL> {
			static constexpr GPIOAlt alt = GPIOAlt::alt4;
		};
		template<>
		struct I2CPinTrait<I2CChannel::channel1, GPIO_B7, I2CPin::pinSDA> {
			static constexpr GPIOAlt alt = GPIOAlt::alt4;
		};
	#endif

	#ifdef I2C2
		template <>
		struct I2CTrait<I2CChannel::channel2> {
			static constexpr uint32_t addr = I2C2_BASE;
		};
	#endif

	#ifdef I2C3
		template <>
		struct I2CTrait<I2CChannel::channel3> {
			static constexpr uint32_t addr = I2C3_BASE;
		};

		template <>
		struct I2CPinTrait<I2CChannel::channel3, GPIO_H7, I2CPin::pinSCL> {
			static constexpr GPIOAlt alt = GPIOAlt::alt4;
		};
		template <>
		struct I2CPinTrait<I2CChannel::channel3, GPIO_H8, I2CPin::pinSDA> {
			static constexpr GPIOAlt alt = GPIOAlt::alt4;
		};
	#endif

	#ifdef I2C4
		template <>
		struct I2CTrait<I2CChannel::channel4> {
			static constexpr uint32_t addr = I2C4_BASE;
		};
	#endif
}


#endif // __STM32_htlI2C__

