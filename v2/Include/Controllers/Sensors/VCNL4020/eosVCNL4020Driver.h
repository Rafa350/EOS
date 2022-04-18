#ifndef __eosVCLN4020Driver__
#define __eosVCLN4020Driver__


#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2C.h"
#include "HAL/halI2CTpl.h"
#ifdef EOS_STM32
#include "HAL/STM32/halEXTI.h"
#include "HAL/STM32/halEXTITpl.h"
#endif


namespace eos {

	class VCNL4020Driver {
		private:
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_I2C_SCL_PORT), GPIOPin(VCNL4020_I2C_SCL_PIN)> PinSCL;
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_I2C_SDA_PORT), GPIOPin(VCNL4020_I2C_SDA_PIN)> PinSDA;
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_INT_PORT), GPIOPin(VCNL4020_INT_PIN)> PinINT;
			typedef EXTIAdapter<EXTILine(VCNL4020_INT_EXTI_LINE) > LineINT;
			typedef I2CModule<I2CChannel(VCNL4020_I2C_CHANNEL)> I2C;

		public:
			enum class Mode {
				continous,
				onDemand
			};

		private:
			Mode _mode;
			I2C _i2c;

		private:
			static void interruptHandler(halEXTILine line, void *params);
			void writeRegister8(uint8_t reg, uint8_t value);
			void writeRegister16(uint8_t reg, uint16_t value);
			uint8_t readRegister8(uint8_t reg);
			uint16_t readRegister16(uint8_t reg);

		public:
			VCNL4020Driver();

			void initialize(Mode mode);
			void shutdown();

			void setIRCurrent(uint8_t value);
			void setIntUpperThreshold(int value);
			void setIntLowerThreshold(int value);
			uint8_t getIRCurrent();
			int getProximityValue();
			int getAmbientValue();
	};
}


#endif // __eosVCNL4020Driver__
