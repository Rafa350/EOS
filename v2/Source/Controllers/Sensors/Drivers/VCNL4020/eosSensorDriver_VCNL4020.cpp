#include "eos.h"
#include "Controllers/Sensors/Drivers/VCNL4020/eosSensorDriver_VCNL4020.h"
#include "Controllers/Sensors/Drivers/VCNL4020/VCNL40x0.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2CTpl.h"
#ifdef EOS_STM32
#include "HAL/STM32/halINTTpl.h"
#include "HAL/STM32/halEXTITpl.h"
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
VCNL4020Driver::VCNL4020Driver():
	_mode(Mode::demand) {

	// Configura la linia d'interrupcio
	//
	PinINT::initInput(GPIOSpeed::fast, GPIOPull::none);

    // Configura el modul I2C
    //
    _i2c.initSCLPin<PinSCL>();
	_i2c.initSDAPin<PinSDA>();
	_i2c.initMaster();

	LineINT::init(EXTIPort(VCNL4020_INT_EXTI_PORT), EXTIMode::interrupt, EXTITrigger::falling);
    LineINT::setInterruptFunction(interruptHandler, this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
/// \param    mode: NModus de treball (Continu o sota demanda)
///
void VCNL4020Driver::initialize(
	Mode mode) {

	_mode = mode;

	// Desactiva tot
	//
	writeRegister8(VCNL4020_REG_COMMAND, COMMAND_ALL_DISABLE);

	// Asigna el valor de la current del emisor IR
	//
	setLedCurrent(15);

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
void VCNL4020Driver::shutdown() {

	// Desactiva tot
	//
	writeRegister8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un registre de 8 bits.
/// \param    reg: El numero de registre.
/// \return   El valor del registre.
///
uint8_t VCNL4020Driver::readRegister8(
	uint8_t reg) {

	uint8_t data[1];

    data[0] = reg;

    _i2c.send(VCNL40x0_ADDRESS, data, 1);
    _i2c.receive(VCNL40x0_ADDRESS, data, 1);

    return data[0];
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un registre de 16 bits.
/// \param    reg: El numero de registre.
/// \return   El valor del registre.
///
uint16_t VCNL4020Driver::readRegister16(
	uint8_t reg) {

	uint8_t data[2];

    data[0] = reg;

    _i2c.send(VCNL40x0_ADDRESS, data, 1);
    _i2c.receive(VCNL40x0_ADDRESS, data, 2);

	return (data[0] << 8) | data[1];
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en un registre de 8 bits.
/// \param    reg: El numero de registre.
/// \param    value: El valor a escriure.
///
void VCNL4020Driver::writeRegister8(
	uint8_t reg,
	uint8_t value) {

	uint8_t data[2];

	data[0] = reg;
	data[1] = value;
	_i2c.send(VCNL40x0_ADDRESS, data, 2);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en un registre de 16 bits.
/// \param    reg: El numero de registre.
/// \param    value: El valor a escriure.
///
void VCNL4020Driver::writeRegister16(
	uint8_t reg,
	uint16_t value) {

	uint8_t data[3];

	data[0] = reg;
	data[1] = (value & 0xFF00) >> 8;
	data[2] = value & 0x00FF;
	_i2c.send(VCNL40x0_ADDRESS, data, 3);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida en la interrupcio EXTI
/// \param    line: La linia que genera la interrupcio.
/// \param    param: Parametres de la interrupcio.
///
void VCNL4020Driver::interruptHandler(
	halEXTILine line,
	void *param) {

	VCNL4020Driver *driver = static_cast<VCNL4020Driver*>(param);

	uint8_t status = driver->getInterruptStatus();
	if ((status & INTERRUPT_STATUS_THRES_HI) == INTERRUPT_STATUS_THRES_HI) {

		driver->setUpperThreshold(0xFFFF);
	}

	if ((status & INTERRUPT_STATUS_THRES_LO) == INTERRUPT_STATUS_THRES_LO) {

	}

	driver->clearInterruptFlags(status);
	driver->writeRegister8(VCNL4020_REG_COMMAND, COMMAND_PROX_ENABLE | COMMAND_AMBI_ENABLE | COMMAND_SELFTIMED_MODE_ENABLE);
}


/// ----------------------------------------------------------------------
/// \brief    Espera que el valor de proximitat estigui disponible.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si esta disponible, false en cas contrari.
///
bool VCNL4020Driver::waitProximityValue(
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
int VCNL4020Driver::getProximityValue() {

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_PROX_ENABLE | COMMAND_PROX_ON_DEMAND);

	uint8_t cr;
	do {
		cr = readRegister8(VCNL4020_REG_COMMAND);
	} while ((cr & COMMAND_MASK_PROX_DATA_READY) != COMMAND_MASK_PROX_DATA_READY);

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
bool VCNL4020Driver::waitAmbiendValue(
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
int VCNL4020Driver::getAmbientValue() {

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_AMBI_ENABLE | COMMAND_AMBI_ON_DEMAND);

	uint8_t cr;
	do {
		cr = readRegister8(VCNL4020_REG_COMMAND);
	} while ((cr & COMMAND_MASK_AMBI_DATA_READY) != COMMAND_MASK_AMBI_DATA_READY);

	int result = readRegister16(VCNL4020_REG_AMBI_VALUE);

	if (_mode == Mode::demand)
		writeRegister8(VCNL4020_REG_COMMAND, COMMAND_ALL_DISABLE);

	return result;
}
