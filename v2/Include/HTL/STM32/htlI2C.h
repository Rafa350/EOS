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
		#ifdef SPI1
			channel1 = HAL_I2C_CHANNEL_1,
		#endif
		#ifdef SPI2
			channel2 = HAL_I2C_CHANNEL_2,
		#endif
		#ifdef SPI3
			channel3 = HAL_I2C_CHANNEL_3,
		#endif
		#ifdef SPI4
			channel4 = HAL_I2C_CHANNEL_4
		#endif
	};

	enum class I2CResult: halI2CResult {
		ok = HAL_I2C_OK,
	    error = HAL_I2C_ERR,
		timeout = HAL_I2C_ERR_TIMEOUT,
		busy = HAL_I2C_ERR_BUSY
	};

	template <I2CChannel channel_>
	class I2CTrait {
	};

	template <I2CChannel channel_>
	class I2C_x {
		private:
			using Trait = I2CTrait<channel_>;
			constexpr static const unsigned _defaultBlockTime = 1000;
			constexpr static const uint32_t _addr = Trait::addr;
			constexpr static const uint32_t _rccen = Trait::rccen;

			static halI2CHandler _handler;
			static halI2CData _data;

		public:
			constexpr static const I2CChannel channel = channel_;

		private:
			I2C_x() = delete;
			I2C_x(const I2C_x &) = delete;
			I2C_x(const I2C_x &&) = delete;
            ~I2C_x() = delete;
            
			I2C_x & operator = (const I2C_x &) = delete;
			I2C_x & operator = (const I2C_x &&) = delete;

			inline static void enableClock() {
                RCC->APB1ENR |= _rccen;
            }

            inline static void disableClock() {
            	RCC->APB1ENR &= ~_rccen;
            }

		public:
			static I2CResult initMaster() {

				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}
            
            inline static void deInit() {
                
            	disableClock();
            }

			inline static I2CResult enable() {
				return I2CResult(halI2CEnable(_handler));
			}

			inline static I2CResult disable() {
				return I2CResult(halI2CDisable(_handler));
			}

			inline static I2CResult send(uint8_t addr, const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterSend(_handler, addr, data, size, blockTime));
			}

			inline static I2CResult receive(uint8_t addr, void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterReceive(_handler, addr, data, size, blockTime));
			}

            template <typename gpio_>
			static void initSCLPin() {
				#ifdef SPI1
					if constexpr (channel_ == I2CChannel::channel1)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c1_SCL);
				#endif
				#ifdef SPI2
					if constexpr (channel_ == I2CChannel::channel2)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c2_SCL);
				#endif
				#ifdef SPI3
					if constexpr (channel_ == I2CChannel::channel3)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c3_SCL);
				#endif
				#ifdef SPI4
					if constexpr (channel_ == I2CChannel::channel4)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c4_SCL);
				#endif
			}

            template <typename gpio_>
			static void initSDAPin() {
				#ifdef SPI1
					if constexpr (channel_ == I2CChannel::channel1)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c1_SDA);
				#endif
				#ifdef SPI2
					if constexpr (channel_ == I2CChannel::channel2)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c2_SDA);
				#endif
				#ifdef SPI3
					if constexpr (channel_ == I2CChannel::channel3)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c3_SDA);
				#endif
				#ifdef SPI4
					if constexpr (channel_ == I2CChannel::channel4)
						gpio_::initAlt(
							htl::GPIODriver::openDrain,
							htl::GPIOSpeed::fast,
							gpio_::GPIOAlt::i2c4_SDA);
				#endif
			}
	};

	template <I2CChannel channel_> halI2CHandler I2C_x<channel_>::_handler;
	template <I2CChannel channel_> halI2CData I2C_x<channel_>::_data;

	#ifdef SPI1
		using I2C_1 = I2C_x<I2CChannel::channel1>;
	#endif
	#ifdef SPI2
		using I2C_2 = I2C_x<I2CChannel::channel2>;
	#endif
	#ifdef SPI3
		using I2C_3 = I2C_x<I2CChannel::channel3>;
	#endif
	#ifdef SPI4
		using I2C_4 = I2C_x<I2CChannel::channel4>;
	#endif

	#ifdef SPI1
		template <>
		struct I2CTrait<I2CChannel::channel1> {
			static const uint32_t addr = I2C1_BASE;
			static const uint32_t rccen = RCC_APB1ENR_I2C1EN;
		};
	#endif
	#ifdef SPI1
		template <>
		struct I2CTrait<I2CChannel::channel2> {
			static const uint32_t addr = I2C2_BASE;
			static const uint32_t rccen = RCC_APB1ENR_I2C2EN;
		};
	#endif
	#ifdef SPI1
		template <>
		struct I2CTrait<I2CChannel::channel3> {
			static const uint32_t addr = I2C3_BASE;
			static const uint32_t rccen = RCC_APB1ENR_I2C3EN;
		};
	#endif
	#ifdef SPI1
		template <>
		struct I2CTrait<I2CChannel::channel4> {
			static const uint32_t addr = I2C4_BASE;
			static const uint32_t rccen = RCC_APB1ENR_I2C4EN;
		};
	#endif
}


#endif // __STM32_htlI2C__

