#ifndef __STM32_halI2C_ex__
#define __STM32_halI2C_ex__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/STM32/halI2C.h"
#include "HAL/STM32/halGPIO_ex.h"


namespace eos {

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

	template <I2CChannel channel_, typename sclPin_, typename sdaPin_, bool initPins_ = true>
	class I2CModule {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;

		private:
			halI2CHandler _handler;
			halI2CData _data;

		public:
			constexpr static const I2CChannel channel = channel_;

		private:
			I2CModule() = default;
			I2CModule(const I2CModule &) = delete;
			I2CModule(const I2CModule &&) = delete;
			I2CModule & operator = (const I2CModule &) = delete;
			I2CModule & operator = (const I2CModule &&) = delete;

		public:
			inline static auto & instance() {
				static I2CModule module;
				return module;
			}

			inline I2CResult initMaster() {

				if constexpr (initPins_) {
					initSCLPin();
					initSDAPin();
				}

				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				return I2CResult(halI2CMasterInitialize(&_data, &initInfo, &_handler));
			}

			inline I2CResult enable() {
				return I2CResult(halI2CEnable(_handler));
			}

			inline I2CResult disable() {
				return I2CResult(halI2CDisable(_handler));
			}

			inline I2CResult send(uint8_t addr, const void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterSend(_handler, addr, data, size, blockTime));
			}

			inline I2CResult receive(uint8_t addr, void *data, int size, unsigned blockTime = _defaultBlockTime) {
				return I2CResult(halI2CMasterReceive(_handler, addr, data, size, blockTime));
			}

			inline static void initSCLPin() {
				if constexpr (channel_ == I2CChannel::channel1)
					sclPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sclPin_::GPIOAlt::i2c1_SCL);

				if constexpr (channel_ == I2CChannel::channel2)
					sclPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sclPin_::GPIOAlt::i2c2_SCL);

				if constexpr (channel_ == I2CChannel::channel3)
					sclPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sclPin_::GPIOAlt::i2c3_SCL);

				if constexpr (channel_ == I2CChannel::channel4)
					sclPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sclPin_::GPIOAlt::i2c4_SCL);
			}

			inline static void initSDAPin() {
				if constexpr (channel_ == I2CChannel::channel1)
					sdaPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sdaPin_::GPIOAlt::i2c1_SDA);

				if constexpr (channel_ == I2CChannel::channel2)
					sdaPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sdaPin_::GPIOAlt::i2c2_SDA);

				if constexpr (channel_ == I2CChannel::channel3)
					sdaPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sdaPin_::GPIOAlt::i2c3_SDA);

				if constexpr (channel_ == I2CChannel::channel4)
					sdaPin_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						sdaPin_::GPIOAlt::i2c4_SDA);
			}
	};

	template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_1 = I2CModule<I2CChannel::channel1, sclPin_, sdaPin_, initPins_>;

	template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_2 = I2CModule<I2CChannel::channel2, sclPin_, sdaPin_, initPins_>;

	template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_3 = I2CModule<I2CChannel::channel3, sclPin_, sdaPin_, initPins_>;

	template <typename sclPin_, typename sdaPin_, bool initPins_ = true>
	using I2C_4 = I2CModule<I2CChannel::channel4, sclPin_, sdaPin_, initPins_>;
}


#endif // __cplusplus

#endif // __STM32_halI2C_ex__

