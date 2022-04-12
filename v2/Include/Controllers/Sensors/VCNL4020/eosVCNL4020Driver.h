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

		private:
			void write8(uint8_t reg, uint8_t value);
			void write16(uint8_t reg, uint16_t value);
			uint8_t read8(uint8_t reg);
			uint16_t read16(uint8_t reg);

		public:
			VCNL4020Driver();

			void initialize();
			void shutdown();

			void setIntControl(uint8_t value);
			void setIntStatus(uint8_t value);
			void setIntUpperThreshold(int value);
			void setIntLowerThreshold(int value);
			int getProximityValue();
			int getAmbientValue();
	};
}


#endif // __eosVCNL4020Driver__
