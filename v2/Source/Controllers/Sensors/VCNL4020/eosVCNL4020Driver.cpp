#include "eos.h"
#include "Controllers/Sensors/VCNL4020/eosVCNL4020Driver.h"
#include "HAL/halGPIOTpl.h"
#include "HAL/halI2CTpl.h"


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

	uint8_t data;

	// Asigna el valor de la current del emisor
	//
	data = 0x0A;
	_i2c.send(0x26, 0x83, &data, sizeof(data), 1000);

	// Asigna la velocitat de mesura.
	///
	data = 0x02;
	_i2c.send(0x26, 0x82, &data, sizeof(data), 1000);
}


/// ----------------------------------------------------------------------
/// \brief Desinicialitza el driver.
///
void VCNL4020Driver::shutdown() {

}
