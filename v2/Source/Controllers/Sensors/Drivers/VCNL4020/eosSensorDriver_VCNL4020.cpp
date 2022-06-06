#include "eos.h"
#include "Controllers/Sensors/Drivers/VCNL4020/eosSensorDriver_VCNL4020.h"
#include "Controllers/Sensors/Drivers/VCNL4020/VCNL40x0.h"
#include "HAL/halGPIO_ex.h"
#include "HAL/halI2C_ex.h"
#ifdef EOS_STM32
#include "HAL/STM32/halINT_ex.h"
#include "HAL/STM32/halEXTI_ex.h"
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
SensorDriver_VCNL4020::SensorDriver_VCNL4020():
	_mode(Mode::demand),
	_i2c(I2C::instance()) {

	// Configura la linia d'interrupcio
	//
	_pinINT.initInput(GPIOSpeed::fast, GPIOPull::none);

    // Configura el modul I2C
    //
	_i2c.initMaster();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
/// \param    mode: NModus de treball (Continu o sota demanda)
///
void SensorDriver_VCNL4020::initialize(
	Mode mode,
	uint8_t current) {

	_mode = mode;

	// Desactiva tot
	//
	writeRegister8(VCNL4020_REG_COMMAND, COMMAND_ALL_DISABLE);

	// Asigna el valor de la current del emisor IR
	//
	if (current >= 0)
		setLedCurrent(current);

	// Asigna la velocitat de mesura.
	//
	writeRegister8(VCNL4020_REG_PROX_RATE, PROX_MEASUREMENT_RATE_31);

	// Asigna el modus d'operacio del sensor de llum ambiental
	//
	writeRegister8(VCNL4020_REG_AMBI_PARAMETER, 0x1D);

	// Asigna els limits de mesura
	//
	setLowerThreshold(0);
	setUpperThreshold(0xFFFF);

	// Inicia la lectura periodica
	//
	if (mode == Mode::continous)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_PROX_ENABLE | COMMAND_AMBI_ENABLE | COMMAND_SELFTIMED_MODE_ENABLE);
}


/// ----------------------------------------------------------------------
/// \brief Desinicialitza el driver.
///
void SensorDriver_VCNL4020::shutdown() {

	// Desactiva tot
	//
	writeRegister8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un registre de 8 bits.
/// \param    reg: El numero de registre.
/// \return   El valor del registre.
///
uint8_t SensorDriver_VCNL4020::readRegister8(
	uint8_t reg) {

	uint8_t value;

    _i2c.send(VCNL40x0_ADDRESS, &reg, 1);
    _i2c.receive(VCNL40x0_ADDRESS, &value, sizeof(value));

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un registre de 16 bits.
/// \param    reg: El numero de registre.
/// \return   El valor del registre.
///
uint16_t SensorDriver_VCNL4020::readRegister16(
	uint8_t reg) {

	uint8_t data[2];

    _i2c.send(VCNL40x0_ADDRESS, &reg, 1);
    _i2c.receive(VCNL40x0_ADDRESS, data, sizeof(data));

	return (data[0] << 8) | data[1];
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en un registre de 8 bits.
/// \param    reg: El numero de registre.
/// \param    value: El valor a escriure.
///
void SensorDriver_VCNL4020::writeRegister8(
	uint8_t reg,
	uint8_t value) {

	uint8_t data[2];

	data[0] = reg;
	data[1] = value;
	_i2c.send(VCNL40x0_ADDRESS, data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en un registre de 16 bits.
/// \param    reg: El numero de registre.
/// \param    value: El valor a escriure.
///
void SensorDriver_VCNL4020::writeRegister16(
	uint8_t reg,
	uint16_t value) {

	uint8_t data[3];

	data[0] = reg;
	data[1] = (value & 0xFF00) >> 8;
	data[2] = value & 0x00FF;
	_i2c.send(VCNL40x0_ADDRESS, data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el valor de proximitat estigui disponible.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si esta disponible, false en cas contrari.
///
bool SensorDriver_VCNL4020::waitProximityValue(
	unsigned blockTime) {

	uint8_t cr;
	do {
		cr = readRegister8(VCNL4020_REG_COMMAND);
	} while ((cr & COMMAND_MASK_PROX_DATA_READY) != COMMAND_MASK_PROX_DATA_READY);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de proximitat.
/// \return   El valor.
///
int SensorDriver_VCNL4020::getProximityValue() {

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_PROX_ENABLE | COMMAND_PROX_ON_DEMAND);

	waitProximityValue();

	int result = readRegister16(VCNL4020_REG_PROX_VALUE);

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_ALL_DISABLE);

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el valor de llum ambiental estigui disponible.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si esta disponible, false en cas contrari.
///
bool SensorDriver_VCNL4020::waitAmbientValue(
	unsigned blockTime) {

	uint8_t cr;
	do {
		cr = readRegister8(VCNL4020_REG_COMMAND);
	} while ((cr & COMMAND_MASK_AMBI_DATA_READY) != COMMAND_MASK_AMBI_DATA_READY);

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de llum ambiental.
/// \return   El valor.
///
int SensorDriver_VCNL4020::getAmbientValue() {

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_AMBI_ENABLE | COMMAND_AMBI_ON_DEMAND);

	waitAmbientValue();

	int result = readRegister16(VCNL4020_REG_AMBI_VALUE);

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_ALL_DISABLE);

	return result;
}
