module;


#include "eos.h"


module Eos.Services.DigOutput;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    tag : Etiqueta d'identificadio del pin.
///
eos::DigOutput::DigOutput(
	uint32_t tag):

	_tag {tag} {

}


/// ----------------------------------------------------------------------
/// @brief    Obte l'etiqueta d'identificacio del pin.
/// \return   El resultat.
///
uint32_t eos::DigOutput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// @brief    Contructor
/// @param    dev: El driver del pin.
///
eos::DigOutputImpl::DigOutputImpl(
	PinDriver *drv,
	uint32_t tag):

	DigOutput {tag},
	_drv {drv},
	_value {drv->read()},
	_state{State::idle} {
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el valor true en la sortida.
///
void eos::DigOutputImpl::set() {

	if (!_value) {
		_value = true;
		_drv->write(true);
	}
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el valor false en la sortida.
///
void eos::DigOutputImpl::clear() {

	if (_value) {
		_value = false;
		_drv->write(false);
	}
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Inverteix el valor de la sortida.
///
void eos::DigOutputImpl::toggle() {

	_value = !_value;
	_drv->write(_value);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Genera un puls en la sortida.
/// @param    time: El temps actual.
/// @param    pulse: Durada del puls.
///
void eos::DigOutputImpl::pulse(
	Ticks now,
	Ticks pulse) {

	if (_state == State::idle) {
		_value = !_value;
		_drv->write(_value);
	}

	_pulseEndTime = now + pulse;
	_state = State::pulse;
}


/// ----------------------------------------------------------------------
/// @brief    Posa la sortida al valor true despres d'un retard.
/// @param    time: El temps actual.
/// @param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedSet(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedSet;
}


/// ----------------------------------------------------------------------
/// @brief    Posa la sortida al valor false despres d'un retard.
/// @param    time: El temps actual.
/// @param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedClear(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedClear;
}


/// ----------------------------------------------------------------------
/// @brief    Inverteix el valor despres d'un retard.
/// @param    time: El temps actual.
/// @param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedToggle(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedToggle;
}


/// ----------------------------------------------------------------------
/// @brief    Genera un puls retardat en la sortida.
/// @param    time: El temps actual.
/// @brief    delay: Durada del retard.
/// @param    pulse: Durada del puls.
///
void eos::DigOutputImpl::delayedPulse(
	Ticks now,
	Ticks delay,
	Ticks pulse) {

	_delayEndTime = now + delay;
	_pulseEndTime = now + delay + pulse;
	_state = State::delayedPulse;
}


/// ----------------------------------------------------------------------
/// @brief    Procesa els temps.
/// @return   True si el valor ha canviat.
///
bool eos::DigOutputImpl::tick() {

	bool changed = false;

	if (_state != State::idle) {

		auto end = _state == State::pulse ? _pulseEndTime : _delayEndTime;
		if (end.hasExpired()) {

			bool newValue = _value;

			switch (_state) {
				case State::pulse:
					newValue = !_value;
					_state = State::idle;
					break;

				case State::delayedSet:
					newValue = true;
					_state = State::idle;
					break;

				case State::delayedClear:
 					newValue = false;
					_state = State::idle;
					break;

				case State::delayedToggle:
					newValue = !_value;
					_state = State::idle;
					break;

				case State::delayedPulse:
					newValue = !_value;
					_state = State::pulse;
					break;
			}

			if (newValue != _value) {
				_value = newValue;
				_drv->write(newValue);
				changed = true;
			}
		}
	}

	return changed;
}
