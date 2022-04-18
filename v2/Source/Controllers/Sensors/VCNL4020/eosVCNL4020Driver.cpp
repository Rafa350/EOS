#include "eos.h"
#include "Controllers/Sensors/VCNL4020/eosVCNL4020Driver.h"
#include "Controllers/Sensors/VCNL4020/VCNL40x0.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2CTpl.h"
#ifdef EOS_STM32
#include "HAL/STM32/halEXTITpl.h"
#include "HAL/STM32/halINT.h"
#endif
#include "System/eosMath.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
VCNL4020Driver::VCNL4020Driver():
	_mode(Mode::onDemand) {

	// Configura la linia d'interrupcio externa
	//
	//PinINT::initInput(GPIOSpeed::fast, GPIOPull::up);
	//LineINT::init(EXTIPort(VCNL4020_INT_EXTI_PORT), EXTIMode::interrupt, EXTITrigger::rissing);
    //LineINT::setInterruptFunction(interruptHandler, this);

    // Configura el modul I2C
    //
    _i2c.initSCLPin<PinSCL>();
	_i2c.initSDAPin<PinSDA>();
	_i2c.initMaster();

	// Configura les interrupcions
	//
	//halINTSetInterruptVectorPriority(VCNL4020_INT_IRQ, VCNL4020_INT_PRIORITY, VCNL4020_INT_SUBPRIORITY);
	//halINTEnableInterruptVector(VCNL4020_INT_IRQ);
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
	writeRegister8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);

	// Asigna el valor de la current del emisor
	//
	setIRCurrent(10);

	// Asigna la velocitat de mesura.
	//
	writeRegister8(REGISTER_PROX_RATE, PROX_MEASUREMENT_RATE_2);

	// Asigna el modus d'operacio del sensor de llum ambiental
	//
	writeRegister8(REGISTER_AMBI_PARAMETER, 0x1D);

	// Asigna els parametres de mesura
	//
	//write8(REGISTER_INTERRUPT_CONTROL, 0x42);
	writeRegister16(REGISTER_INTERRUPT_LOW_THRES, 0);
	writeRegister16(REGISTER_INTERRUPT_HIGH_THRES, 0xFFFF);

	// Inicia la lectura periodica
	//
	if (mode == Mode::continous)
		writeRegister8(REGISTER_COMMAND, COMMAND_PROX_ENABLE | COMMAND_AMBI_ENABLE | COMMAND_SELFTIMED_MODE_ENABLE);
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
/// \param    params: Parametres de la interrupcio.
///
void VCNL4020Driver::interruptHandler(
	halEXTILine line,
	void *params) {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna el valor de current del emisor IR.
/// \param    value: El valor 0..20.
///
void VCNL4020Driver::setIRCurrent(
	uint8_t value) {

	writeRegister8(REGISTER_PROX_CURRENT, Math::min((uint8_t)20, value));
}


/// ---------------------------------------------------------------------
/// \build    Asigna el valor del limit superior per la interrupcio.
/// \param    value: El valor.
///
void VCNL4020Driver::setIntUpperThreshold(
	int value) {

	writeRegister16(REGISTER_INTERRUPT_HIGH_THRES, value);
}


/// ---------------------------------------------------------------------
/// \build    Asigna el valor del limit inferior per la interrupcio.
/// \param    value: El valor.
///
void VCNL4020Driver::setIntLowerThreshold(
	int value) {

	writeRegister16(REGISTER_INTERRUPT_LOW_THRES, value);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de current del emisor IR.
/// \return   El valor.
///
uint8_t VCNL4020Driver::getIRCurrent() {

	return readRegister8(REGISTER_PROX_CURRENT) & 0b00111111;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de proximitat
/// \return   El valor.
///
int VCNL4020Driver::getProximityValue() {

	if (_mode == Mode::onDemand)
		writeRegister8(REGISTER_COMMAND, COMMAND_PROX_ENABLE | COMMAND_PROX_ON_DEMAND);

	uint8_t cr;
	do {
		cr = readRegister8(REGISTER_COMMAND);
	} while ((cr & COMMAND_MASK_PROX_DATA_READY) != COMMAND_MASK_PROX_DATA_READY);

	int result = readRegister16(REGISTER_PROX_VALUE);

	if (_mode == Mode::onDemand)
		writeRegister8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de ambient
/// \return   El valor.
///
int VCNL4020Driver::getAmbientValue() {

	if (_mode == Mode::onDemand)
		writeRegister8(REGISTER_COMMAND, COMMAND_AMBI_ENABLE | COMMAND_AMBI_ON_DEMAND);

	uint8_t cr;
	do {
		cr = readRegister8(REGISTER_COMMAND);
	} while ((cr & COMMAND_MASK_AMBI_DATA_READY) != COMMAND_MASK_AMBI_DATA_READY);

	int result = readRegister16(REGISTER_AMBI_VALUE);

	if (_mode == Mode::onDemand)
		writeRegister8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);

	return result;
}
