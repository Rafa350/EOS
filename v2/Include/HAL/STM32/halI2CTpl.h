#ifndef __STM32_halI2CTpl__
#define __STM32_halI2CTpl__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/STM32/halI2C.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class I2CChannel: halI2CChannel {
		channel1 = HAL_I2C_CHANNEL_1,
		channel2 = HAL_I2C_CHANNEL_2,
		channel3 = HAL_I2C_CHANNEL_3,
		channel4 = HAL_I2C_CHANNEL_4
	};

	template <I2CChannel channel_>
	class I2CAdapter {
		private:
			constexpr static const unsigned _defaultBlockTime = 1000;

		private:
			halI2CData _data;
			halI2CHandler _handler;

		public:
			constexpr static const I2CChannel channel = channel_;

		public:
			inline void initMaster() {
				halI2CMasterInitializeInfo initInfo;
				initInfo.channel = halI2CChannel(channel_);
				_handler = halI2CMasterInitialize(&_data, &initInfo);
			}

			inline void enable() {
				halI2CEnable(_handler);
			}

			inline void disable() {
				halI2CDisable(_handler);
			}

			inline void send(uint8_t addr, uint16_t reg, const uint8_t *buffer, uint16_t length, unsigned blockTime = _defaultBlockTime) {
				halI2CMasterSend(
					_handler,
					addr,
					buffer,
					length,
					blockTime);
			}

			inline void send(uint8_t addr, uint16_t reg, uint8_t data, unsigned blockTime = _defaultBlockTime) {
				halI2CMasterSend(
					_handler,
					addr,
					&data,
					sizeof(data),
					blockTime);
			}

			inline void send(uint8_t addr, uint16_t reg, uint16_t memAddress, const uint8_t *buffer, uint16_t length) {
				halI2CMasterWriteMultiple(
					_handler,
					addr,
					reg,
					memAddress,
					buffer,
					length);
			}

			inline void read(uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t *buffer, uint16_t length) {
				halI2CMasterReadMultiple(
					_handler,
					addr,
					reg,
					I2C_MEMADD_SIZE_8BIT,
					buffer,
					sizeof(buffer));
			}

			template <typename pinAdapter_>
			inline static void setSCLPin(pinAdapter_ pinAdapter) {
				if constexpr (channel_ == I2CChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c1_SCL);

				if constexpr (channel_ == I2CChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c2_SCL);

				if constexpr (channel_ == I2CChannel::channel3)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c3_SCL);

				if constexpr (channel_ == I2CChannel::channel4)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c4_SCL);
			}

			template <typename pinAdapter_>
			inline static void setSDAPin(pinAdapter_ pinAdapter) {
				if constexpr (channel_ == I2CChannel::channel1)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c1_SDA);

				if constexpr (channel_ == I2CChannel::channel2)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c2_SDA);

				if constexpr (channel_ == I2CChannel::channel3)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c3_SDA);

				if constexpr (channel_ == I2CChannel::channel4)
					pinAdapter_::initAlt(
						GPIOSpeed::fast,
						GPIODriver::openDrain,
						pinAdapter_::GPIOAlt::i2c4_SDA);
			}
	};

	typedef I2CAdapter<I2CChannel::channel1> I2C_1;
	typedef I2CAdapter<I2CChannel::channel2> I2C_2;
	typedef I2CAdapter<I2CChannel::channel3> I2C_3;
	typedef I2CAdapter<I2CChannel::channel4> I2C_4;
}


#endif // __cplusplus

#endif // __STM32_halI2CTpl__

