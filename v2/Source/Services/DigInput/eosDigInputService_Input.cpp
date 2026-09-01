module;


#include "eos.h"
#include "Controllers/Pin/eosPinDriver.h"


module Eos.Services.DigInput;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    tag: Etiqueta d'identificacio.
///
eos::DigInput::DigInput(
	uint32_t tag):

	_tag {tag} {

}


/// ----------------------------------------------------------------------
/// \brief    Obte l'etiqueta d'identificacio de l'entrada.
/// \return   El valor de l'etiqueta.
///
uint32_t eos::DigInput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    drv: Driver del pin.
///
eos::DigInputImpl::DigInputImpl(
	PinDriver *drv,
	uint32_t tag):

	DigInput {tag},
	_drv {drv} {

	_value = _drv->read();
	_pattern = _value ? _patternActive : _patternIdle;
	_count = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Escaneja la entrada i comprova si hi han canvis.
/// \return   True si hi han canvis, false en cas contrari.
///
bool eos::DigInputImpl::scan() {

	uint32_t oldCount = _count;

	// Actualitza el patro de lectura
	//
	_pattern <<= 1;
	if (_drv->read())
		_pattern |= 1;

	// Analitza el patro per detectar un flanc positiu.
	//
	if ((_pattern & _patternMask) == _patternPosEdge) {
		_value = true;
		_count += 1;
	}

	// Analitza el patro per detectar un flanc negatiu.
	//
	else if ((_pattern & _patternMask) == _patternNegEdge) {
		_value = false;
		_count += 1;
	}

	return oldCount != _count;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor de l'entrada.
/// \return   True per estat actiu.
///
bool eos::DigInputImpl::getValue() const {

	return _value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de canvis.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El valor del contador.
///
uint32_t eos::DigInputImpl::getCount(
	bool clear) {

	uint32_t count = _count;
	if (clear)
		_count = 0;
	return count;
}
