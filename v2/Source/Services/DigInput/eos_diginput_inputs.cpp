#include "eos_diginput_inputs.h"
#include "Controllers/Pin/eosPinDriver.h"
#include "Services/DigInput/eosDigInputService.h"


using namespace eos;


static constexpr uint32_t patternMask    = 0x000000FF;
static constexpr uint32_t patternPosEdge = 0x0000007F;
static constexpr uint32_t patternNegEdge = 0x00000080;
static constexpr uint32_t patternActive  = 0x000000FF;
static constexpr uint32_t patternIdle    = 0x00000000;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    drv: Driver del pin.
///
Input::Input(
	PinDriver *drv,
	unsigned tag):

	DigInput {tag},
	_drv {drv} {

	_value = _drv->read();
	_pattern = _value ? patternActive : patternIdle;
	_count = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Escaneja la entrada i comprova si hi han canvis.
/// \return   True si hi han canvis, false en cas contrari.
///
bool Input::scan() {

	unsigned oldCount = _count;

	// Actualitza el patro de lectura
	//
	_pattern <<= 1;
	if (_drv->read())
		_pattern |= 1;

	// Analitza el patro per detectar un flanc positiu.
	//
	if ((_pattern & patternMask) == patternPosEdge) {
		_value = true;
		_count += 1;
	}

	// Analitza el patro per detectar un flanc negatiu.
	//
	else if ((_pattern & patternMask) == patternNegEdge) {
		_value = false;
		_count += 1;
	}

	return oldCount != _count;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de l'entrada.
/// \return   True per estat actiu.
///
bool Input::getValue() const {

	return _value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de canvis.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El valor del contador.
///
unsigned Input::getCount(
	bool clear) {

	unsigned count = _count;
	if (clear)
		_count = 0;
	return count;
}
