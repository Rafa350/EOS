#ifndef __STM32_htlI2C__
#define __STM32_htlI2C__


// EOS includes
//
#include "eos.h"
#include "HAL/STM32/halI2C.h"
#include "HTL/STM32/htlGPIO.h"


namespace htl {

	enum class I2CChannel: halI2CChannel {
		channel1 = HAL_I2C_CHANNEL_1,
		channel2 = HAL_I2C_CHANNEL_2,
		channel3 = HAL_I2C_CHANNEL_3,
		channel4 = HAL_I2C_CHANNEL_4
	};

	enum class I2CResult: halI2CResult {
		ok = HAL_I2C_OK,
	    error = HAL_I2C_ERR,
		timeout = HAL_I2C_ERR_TIMEOUT,
		busy = HAL_I2C_ERR_BUSY
	};

	template <I2CChannel channel_>
	class I2C_x {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;

		private:
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

		public:
			static I2CResult initMaster() {

				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}
            
            inline static void deInit() {
                
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
				if constexpr (channel_ == I2CChannel::channel1)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c1_SCL);

				if constexpr (channel_ == I2CChannel::channel2)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c2_SCL);

				if constexpr (channel_ == I2CChannel::channel3)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c3_SCL);

				if constexpr (channel_ == I2CChannel::channel4)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c4_SCL);
			}

            template <typename gpio_>
			static void initSDAPin() {
				if constexpr (channel_ == I2CChannel::channel1)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c1_SDA);

				if constexpr (channel_ == I2CChannel::channel2)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c2_SDA);

				if constexpr (channel_ == I2CChannel::channel3)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c3_SDA);

				if constexpr (channel_ == I2CChannel::channel4)
					gpio_::initAlt(
						htl::GPIODriver::openDrain,
						htl::GPIOSpeed::fast,
						gpio_::GPIOAlt::i2c4_SDA);
			}
	};

	template <I2CChannel channel_> halI2CHandler I2C_x<channel_>::_handler;
	template <I2CChannel channel_> halI2CData I2C_x<channel_>::_data;

	using I2C_1 = I2C_x<I2CChannel::channel1>;
	using I2C_2 = I2C_x<I2CChannel::channel2>;
	using I2C_3 = I2C_x<I2CChannel::channel3>;
	using I2C_4 = I2C_x<I2CChannel::channel4>;
}


#endif // __STM32_htlI2C__

