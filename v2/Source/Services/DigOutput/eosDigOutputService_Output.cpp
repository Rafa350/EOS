module;


#include "eos.h"
#include "eosTime.h"


module Eos.Services.DigOutput;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    tag : Etiqueta d'identificadio del pin.
///
eos::DigOutput::DigOutput(
	uint32_t tag):

	_tag {tag} {

}


/// ----------------------------------------------------------------------
/// \brief    Obte l'etiqueta d'identificacio del pin.
/// \return   El resultat.
///
uint32_t eos::DigOutput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor
/// \param    dev: El driver del pin.
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
/// \brief    Obte el valor actual de la sortida.
/// \return   El valor.
///
bool eos::DigOutputImpl::getValue() const {

	return _value;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un nou valor en la sortida.
/// \param    value: El nou valor.
///
void eos::DigOutputImpl::write(
	bool value) {

	if (_value != value) {
		_value = value;
		_drv->write(value);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el valor true en la sortida.
///
void eos::DigOutputImpl::set() {

	write(true);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el valor false en la sortida.
///
void eos::DigOutputImpl::clear() {

	write(false);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el valor de la sortida.
///
void eos::DigOutputImpl::toggle() {

	write(!_value);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls en la sortida.
/// \param    time: El temps actual.
/// \param    pulse: Durada del puls.
///
void eos::DigOutputImpl::pulse(
	Ticks now,
	Ticks pulse) {

	if (_state == State::idle)
		write(!_value);

	_pulseEndTime = now + pulse;
	_state = State::pulse;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor true despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedSet(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedSet;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor false despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedClear(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedClear;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el valor despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedToggle(
	Ticks now,
	Ticks delay) {

	_delayEndTime = now + delay;
	_state = State::delayedToggle;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls retardat en la sortida.
/// \param    time: El temps actual.
/// \brief    delay: Durada del retard.
/// \param    pulse: Durada del puls.
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
/// \brief    Procesa els temps.
///
void eos::DigOutputImpl::tick() {

	switch (_state) {
		case State::idle:
			break;

		case State::pulse:
			if (_pulseEndTime.hasExpired()) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedSet:
			if (_delayEndTime.hasExpired()) {
				write(true);
				_state = State::idle;
			}
			break;

		case State::delayedClear:
			if (_delayEndTime.hasExpired()) {
				write(false);
				_state = State::idle;
			}
			break;

		case State::delayedToggle:
			if (_delayEndTime.hasExpired()) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedPulse:
			if (_delayEndTime.hasExpired()) {
				write(!_value);
				_state = State::pulse;
			}
			break;
	}
}
