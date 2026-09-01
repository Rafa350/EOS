module;


#include "eos.h"
#include "eosTime.h"
#include "Controllers/Pin/eosPinDriver.h"


module Eos.Services.DigOutput;


eos::DigOutput::DigOutput(
	uint32_t tag):

	_tag {tag} {

}


uint32_t eos::DigOutput::getTag() const {

	return _tag;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor
/// \param    dev: El driver del pin.
///
eos::DigOutputImpl::DigOutputImpl(
	eos::PinDriver *drv,
	uint32_t tag):

	eos::DigOutput {tag},
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
	eos::Time time,
	eos::Time pulse) {

	if (_state == State::idle)
		write(!_value);

	_pulseEndTime = time + pulse;
	_state = State::pulse;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor true despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedSet(
	eos::Time time,
	eos::Time delay) {

	_delayEndTime = time + delay;
	_state = State::delayedSet;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor false despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedClear(
	eos::Time time,
	eos::Time delay) {

	_delayEndTime = time + delay;
	_state = State::delayedClear;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el valor despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void eos::DigOutputImpl::delayedToggle(
	eos::Time time,
	eos::Time delay) {

	_delayEndTime = time + delay;
	_state = State::delayedToggle;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls retardat en la sortida.
/// \param    time: El temps actual.
/// \brief    delay: Durada del retard.
/// \param    pulse: Durada del puls.
///
void eos::DigOutputImpl::delayedPulse(
	eos::Time time,
	eos::Time delay,
	eos::Time pulse) {

	_delayEndTime = time + delay;
	_pulseEndTime = time + delay + pulse;
	_state = State::delayedPulse;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els temps.
/// \param    time: El temps actual.
///
void eos::DigOutputImpl::tick(
	eos::Time time) {

	switch (_state) {
		case State::idle:
			break;

		case State::pulse:
			if (hasExpired(time, _pulseEndTime)) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedSet:
			if (hasExpired(time, _delayEndTime)) {
				write(true);
				_state = State::idle;
			}
			break;

		case State::delayedClear:
			if (hasExpired(time, _delayEndTime)) {
				write(false);
				_state = State::idle;
			}
			break;

		case State::delayedToggle:
			if (hasExpired(time, _delayEndTime)) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedPulse:
			if (hasExpired(time, _delayEndTime)) {
				write(!_value);
				_state = State::pulse;
			}
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temps ha expirat.
/// \param    time: Temp actual.
/// \param    endTime: Temps limit.
/// \return   True si el temps actual es posterior al temps limit.
///
bool eos::DigOutputImpl::hasExpired(
	eos::Time time,
	eos::Time endTime) {

	auto delta = endTime - time;
	return static_cast<int>(delta.toMiliseconds()) <= 0;
}
