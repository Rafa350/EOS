module Eos.Services.DigInput;

import Eos.Types;


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    tag: Etiqueta d'identificacio.
///
DigInput::DigInput(
	UInt32 tag):

	_tag {tag} {

}


/// ----------------------------------------------------------------------
/// \brief    Obte l'etiqueta d'identificacio de l'entrada.
/// \return   El valor de l'etiqueta.
///
UInt32 DigInput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    drv: Driver del pin.
///
DigInputImpl::DigInputImpl(
	PinDriver *drv,
	UInt32 tag):

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
bool DigInputImpl::scan() {

	UInt32 oldCount = _count;

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
bool DigInputImpl::getValue() const {

	return _value;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el contador de canvis.
/// \param    clear: Indica si cal borrar el contador.
/// \return   El valor del contador.
///
UInt32 eos::DigInputImpl::getCount(
	bool clear) {

	UInt32 count = _count;
	if (clear)
		_count = 0;
	return count;
}
