#ifndef __STM32_halI2CTpl__
#define __STM32_halI2CTpl__

#ifdef __cplusplus


// EOS includes
//
#include "HAL/STM32/halI2C.h"
#include "HAL/STM32/halGPIOTpl.h"


namespace eos {

	enum class I2cChannel: I2CChannel {
		channel1 = HAL_I2C_CHANNEL_1,
		channel2 = HAL_I2C_CHANNEL_2,
		channel3 = HAL_I2C_CHANNEL_3,
		channel4 = HAL_I2C_CHANNEL_4
	};

	template <I2cChannel channel>
	class I2cAdapter {
		private:
			I2CData _data;
			I2CHandler _handler;

		public:
			inline void initMaster() {

				I2CMasterInitializeInfo initInfo;
				initInfo.channel = I2CChannel(channel);
				_handler = halI2CMasterInitialize(&_data, &initInfo);
			}

			inline void send(uint8_t addr, uint16_t reg, uint16_t memAddress, const uint8_t* buffer, uint16_t length) {
				halI2CMasterWriteMultiple(
					_handler,
					addr,
					reg,
					memAddress,
					buffer,
					length);
			}

			inline void read(uint8_t addr, uint16_t reg, uint16_t memAddress, uint8_t* buffer, uint16_t length) {
				halI2CMasterReadMultiple(
					_handler,
					addr,
					reg,
					I2C_MEMADD_SIZE_8BIT,
					buffer,
					sizeof(buffer));
			}

			template <GpioPort port, GpioPin pin>
			inline static void setSCLPin(GpioPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == I2cChannel::channel1)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c1_SCL);

				if constexpr (channel == I2cChannel::channel2)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c2_SCL);

				if constexpr (channel == I2cChannel::channel3)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c3_SCL);

				if constexpr (channel == I2cChannel::channel4)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c4_SCL);
			}

			template <GpioPort port, GpioPin pin>
			inline static void setSDAPin(GpioPinAdapter<port, pin> pinAdapter) {
				if constexpr (channel == I2cChannel::channel1)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c1_SDA);

				if constexpr (channel == I2cChannel::channel2)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c2_SDA);

				if constexpr (channel == I2cChannel::channel3)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c3_SDA);

				if constexpr (channel == I2cChannel::channel4)
					pinAdapter.initAlt(
						GpioSpeed::fast,
						GpioDriver::openDrain,
						GpioPinAdapter<port, pin>::GpioAlt::i2c4_SDA);
		}
	};
}


#endif // __cplusplus

#endif // __STM32_halI2CTpl__

