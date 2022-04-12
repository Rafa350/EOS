#include "eos.h"
#include "Controllers/Sensors/VCNL4020/eosVCNL4020Driver.h"
#include "Controllers/Sensors/VCNL4020/VCNL40x0.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2CTpl.h"
#ifdef EOS_STM32
#include "HAL/STM32/halEXTI.h"
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
VCNL4020Driver::VCNL4020Driver() {

	_i2c.setSCLPin(_pinSCL);
	_i2c.setSDAPin(_pinSDA);
	_i2c.initMaster();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void VCNL4020Driver::initialize() {

	// Desactiva tot
	//
	write8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);

	// Asigna el valor de la current del emisor
	//
	write8(REGISTER_PROX_CURRENT, 15);

	// Asigna la velocitat de mesura.
	//
	write8(REGISTER_PROX_RATE, PROX_MEASUREMENT_RATE_2);

	// Asigna el modus d'operacio del sensor de llum ambiental
	//
	write8(REGISTER_AMBI_PARAMETER, 0x1D);

	// Asigna els parametres de mesura
	//
	write8(REGISTER_INTERRUPT_CONTROL, 0x42);

	// Inicia la lectura periodica
	//
	write8(REGISTER_COMMAND, COMMAND_PROX_ENABLE | COMMAND_AMBI_ENABLE | COMMAND_SELFTIMED_MODE_ENABLE);
}


/// ----------------------------------------------------------------------
/// \brief Desinicialitza el driver.
///
void VCNL4020Driver::shutdown() {

	// Desactiva tot
	//
	write8(REGISTER_COMMAND, COMMAND_ALL_DISABLE);
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un registre de 8 bits.
/// \param    reg: El numero de registre.
/// \return   El valor del registre.
///
uint8_t VCNL4020Driver::read8(
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
uint16_t VCNL4020Driver::read16(
	uint8_t reg) {

	uint8_t data[2];

    data[0] = reg;
    _i2c.send(VCNL40x0_ADDRESS, data, 1);
    _i2c.receive(VCNL40x0_ADDRESS, data, 2);

	return (data[0] << 8) | data[1];
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en un registre de 16 bits.
/// \param    reg: El numero de registre.
/// \param    value: El valor a escriure.
///
void VCNL4020Driver::write8(
	uint8_t reg,
	uint8_t value) {

	uint8_t data[2];

	data[0] = reg;
	data[1] = value;
	_i2c.send(VCNL40x0_ADDRESS, data, 2);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre de control d'interrupcions.
/// \param    value: El valor a escriure.
///
void VCNL4020Driver::setIntControl(
	uint8_t value) {

	write8(REGISTER_INTERRUPT_CONTROL, value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu en el registre d'estat d'interrupcions.
/// \param    value: El valor a escriure.
///
void VCNL4020Driver::setIntStatus(
	uint8_t value) {

	write8(REGISTER_INTERRUPT_STATUS, value);
}


/// ---------------------------------------------------------------------
/// \build    Asigna el valor del limit superior per la interrupcio.
/// \param    value: El valor.
///
void VCNL4020Driver::setIntUpperThreshold(
	int value) {

	write16(REGISTER_INTERRUPT_HIGH_THRES, value);
}


/// ---------------------------------------------------------------------
/// \build    Asigna el valor del limit inferior per la interrupcio.
/// \param    value: El valor.
///
void VCNL4020Driver::setIntLowerThreshold(
	int value) {

	write16(REGISTER_INTERRUPT_LOW_THRES, value);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de proximitat
/// \return   El valor.
///
int VCNL4020Driver::getProximityValue() {

	const int measures = 4;
	int av = 0;

	for (int i = 0; i < measures; i++) {

		uint8_t cr;
		do {
			cr = read8(REGISTER_COMMAND);
		} while ((cr & COMMAND_MASK_PROX_DATA_READY) != COMMAND_MASK_PROX_DATA_READY);

		av += read16(REGISTER_PROX_VALUE);
	}

	return av / measures;
}
