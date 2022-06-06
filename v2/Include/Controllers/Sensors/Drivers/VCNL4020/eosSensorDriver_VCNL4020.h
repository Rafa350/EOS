#ifndef __eosSensorDriver_VCLN4020__
#define __eosSensorDriver_VCLN4020__


#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halGPIO_ex.h"
#include "HAL/halI2C.h"
#include "HAL/halI2C_ex.h"
#ifdef EOS_STM32
#include "HAL/STM32/halEXTI.h"
#include "HAL/STM32/halEXTI_ex.h"
#endif


#define VCNL4020_I2C_ADDR              0x26 // Adressa I2C

// Identificadors dels registres
#define VCNL4020_REG_COMMAND           0x80 // Comanda
#define VCNL4020_REG_ID                0x81 // Identificador
#define VCNL4020_REG_PROX_RATE         0x82 // Velocitat de mostres per segon
#define VCNL4020_REG_PROX_CURRENT      0x83 // Current del led IR
#define VCNL4020_REG_AMBI_PARAMETER    0x84 // Parameters del sensor de llum ambiental
#define VCNL4020_REG_AMBI_VALUE        0x85 // Valor del sensor de llum ambiental
#define VCNL4020_REG_PROX_VALUE        0x87 // Valor del sensor de proximitat
#define VCNL4020_REG_INT_CONTROL       0x89 // Registre de control de les interrupcions
#define VCNL4020_REG_INT_LOWER_THRES   0x8A // Limit inferior per interrupcio
#define VCNL4020_REG_INT_UPPER_THRES   0x8C // Limit superior per interrupcio
#define VCNL4020_REG_INT_STATUS        0x8E // Registre d'estat de les interrupcions

// Lectures consecutives per generar la interrupcio threshold
#define VCNL4020_INT_COUNT_pos         5
#define VCNL4020_INT_COUNT_bits        0b111
#define VCNL4020_INT_COUNT_mask        (VCNL4020_INT_COUNT_bits << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_1           (0 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_2		   (1 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_4		   (2 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_8		   (3 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_16		   (4 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_32	       (5 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_64	       (6 << VCNL4020_INT_COUNT_pos)
#define VCNL4020_INT_COUNT_128	       (7 << VCNL4020_INT_COUNT_pos)

// Activa o desactiva la interrupcio per lectura de proximitat disponible
#define VCNL4020_INT_PROX_pos          3
#define VCNL4020_INT_PROX_bits         0b1
#define VCNL4020_INT_PROX_mask         (VCNL4020_INT_PROX_bits << VCNL4020_INT_PROX_pos)
#define VCNL4020_INT_PROX_DISABLE      (0 << VCNL4020_INT_PROX_pos)
#define VCNL4020_INT_PROX_ENABLE       (1 << VCNL4020_INT_PROX_pos)

// Activa o desactiva la interrupcio per lectura d'ambient disponible
#define VCNL4020_INT_AMBI_pos          2
#define VCNL4020_INT_AMBI_bits         0b1
#define VCNL4020_INT_AMBI_mask         (VCNL4020_INT_AMBI_bits << VCNL4020_INT_AMBI_pos)
#define VCNL4020_INT_AMBI_DISABLE      (0 << VCNL4020_INT_AMBI_pos)
#define VCNL4020_INT_AMBI_ENABLE       (1 << VCNL4020_INT_AMBI_pos)

// Activa o desactiva la interrupcio per superar el threshold
#define VCNL4020_INT_THRES_pos         1
#define VCNL4020_INT_THRES_bits        0b1
#define VCNL4020_INT_THRES_mask        (VCNL4020_INT_THRES_bits << VCNL4020_INT_THRES_pos)
#define VCNL4020_INT_THRES_DISABLE     (0 << VCNL4020_INT_THRES_pos)
#define VCNL4020_INT_THRES_ENABLE      (1 << VCNL4020_INT_THRES_pos)

// Indicadors d'estat d'interrupcio
//
#define VCNL4020_INT_STATUS_PROX       0x08
#define VCNL4020_INT_STATUS_AMBI       0x04
#define VCNL4020_INT_STATUS_THLO       0x02
#define VCNL4020_INT_STATUS_THHI       0x01


namespace eos {

	class SensorDriver_VCNL4020 {
		private:
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_INT_PORT), GPIOPin(VCNL4020_INT_PIN)> PinINT;
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_I2C_SCL_PORT), GPIOPin(VCNL4020_I2C_SCL_PIN)> PinSCL;
			typedef GPIOPinAdapter<GPIOPort(VCNL4020_I2C_SDA_PORT), GPIOPin(VCNL4020_I2C_SDA_PIN)> PinSDA;
			typedef I2CModule<I2CChannel(VCNL4020_I2C_CHANNEL), PinSCL, PinSDA> I2C;

		public:
			enum class Mode {
				continous,
				demand
			};

		private:
			Mode _mode;
			PinINT _pinINT;
			I2C &_i2c;

		private:
			void writeRegister8(uint8_t reg, uint8_t value);
			void writeRegister16(uint8_t reg, uint16_t value);
			uint8_t readRegister8(uint8_t reg);
			uint16_t readRegister16(uint8_t reg);

		public:
			SensorDriver_VCNL4020();

			void initialize(Mode mode, uint8_t current);
			void shutdown();

			inline uint8_t getID() {
				return readRegister8(VCNL4020_REG_ID);
			}

			inline uint8_t getLedCurrent() {
				return readRegister8(VCNL4020_REG_PROX_CURRENT);
			}

			int getProximityValue();

			int getAmbientValue();

			inline unsigned getUpperThreshold() {
				return readRegister16(VCNL4020_REG_INT_UPPER_THRES);
			}

			inline unsigned getLowerThreshold() {
				return readRegister16(VCNL4020_REG_INT_LOWER_THRES);
			}

			inline void setLedCurrent(uint8_t value) {
				writeRegister8(VCNL4020_REG_PROX_CURRENT, value);
			}

			inline void setProximityRate(uint8_t value) {
				writeRegister8(VCNL4020_REG_PROX_RATE, value);
			}

			inline void setUpperThreshold(uint16_t value) {
				writeRegister16(VCNL4020_REG_INT_UPPER_THRES, value);
			}

			inline void setLowerThreshold(uint16_t value) {
				writeRegister16(VCNL4020_REG_INT_LOWER_THRES, value);
			}

			bool waitProximityValue(unsigned blockTime = 0xFFFF);
			bool waitAmbientValue(unsigned blockTime = 0xFFFF);

			inline void configureInterrupts(uint8_t options) {
				writeRegister8(VCNL4020_REG_INT_CONTROL, options);
			}

			inline uint8_t getInterruptStatus() {
				return readRegister8(VCNL4020_REG_INT_STATUS) & 0x0F;
			}

			inline void clearInterruptFlags(uint8_t flags) {
				writeRegister8(VCNL4020_REG_INT_STATUS, flags & 0x0F);
			}
	};
}


#endif // __eosSensorDriver_VCNL4020__
