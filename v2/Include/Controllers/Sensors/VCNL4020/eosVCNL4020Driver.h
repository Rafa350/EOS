#ifndef __eosVCLN4020Driver__
#define __eosVCLN4020Driver__


#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2C.h"
#include "HAL/halI2CTpl.h"


namespace eos {

	class VCNL4020Driver {
		private:
			typedef GPIOPinAdapter<GPIOPort(ARDUINO_I2C_SCL_PORT), GPIOPin(ARDUINO_I2C_SCL_PIN)> PinSCL;
			typedef GPIOPinAdapter<GPIOPort(ARDUINO_I2C_SDA_PORT), GPIOPin(ARDUINO_I2C_SDA_PIN)> PinSDA;
			typedef I2CAdapter<I2CChannel(ARDUINO_I2C_CHANNEL)> I2C;

		private:
			PinSCL _pinSCL;
			PinSDA _pinSDA;
			I2C _i2c;

		public:
			VCNL4020Driver();

			void initialize();
			void shutdown();
	};
}


#endif // __eosVCNL4020Driver__
