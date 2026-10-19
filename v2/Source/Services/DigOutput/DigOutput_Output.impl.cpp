module Eos.Services.DigOutput;

import Eos.Types;


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
/// @param    tag : Etiqueta d'identificadio del pin.
///
DigOutput::DigOutput(
	UInt32 tag):

	_tag {tag} {

}


/// ----------------------------------------------------------------------
/// @brief    Obte l'etiqueta d'identificacio del pin.
/// \return   El resultat.
///
UInt32 DigOutput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// @brief    Contructor
/// @param    dev: El driver del pin.
///
DigOutputImpl::DigOutputImpl(
	PinDriver *drv,
	UInt32 tag):

	DigOutput {tag},
	_drv {drv},
	_value {drv->read()},
	_state{State::idle} {
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el valor true en la sortida.
///
void DigOutputImpl::set() {

	if (!_value) {
		_value = true;
		_drv->write(true);
	}
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Escriu el valor false en la sortida.
///
void DigOutputImpl::clear() {

	if (_value) {
		_value = false;
		_drv->write(false);
	}
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Inverteix el valor de la sortida.
///
void DigOutputImpl::toggle() {

	_value = !_value;
	_drv->write(_value);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// @brief    Genera un puls en la sortida.
/// @param    time: El temps actual.
/// @param    pulse: Durada del puls.
///
void DigOutputImpl::pulse(
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
void DigOutputImpl::delayedSet(
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
void DigOutputImpl::delayedClear(
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
void DigOutputImpl::delayedToggle(
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
void DigOutputImpl::delayedPulse(
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
bool DigOutputImpl::tick() {

	auto result = false;

	if (_state != State::idle) {

		auto endTime = _state == State::pulse ? _pulseEndTime : _delayEndTime;
		if (endTime.hasExpiredNow()) {

			bool oldValue = _value;
			switch (_state) {
				case State::pulse:
					_value = !_value;
					_state = State::idle;
					break;

				case State::delayedSet:
					_value = true;
					_state = State::idle;
					break;

				case State::delayedClear:
					_value = false;
					_state = State::idle;
					break;

				case State::delayedToggle:
					_value = !_value;
					_state = State::idle;
					break;

				case State::delayedPulse:
					_value = !_value;
					_state = State::pulse;
					break;
			}

			if (oldValue != _value) {
				_drv->write(_value);
				result = true;
			}
		}
	}

	return result;
}
