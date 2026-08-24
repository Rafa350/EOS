#include "eos.h"
#include "Services/Forms/eosForm.h"
#include "Services/Forms/Controls/eosNumericControl.h"


import Eos.Math;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    position: Posicio del control.
/// \param    size: Tamany del control.
///
eos::NumericControl::NumericControl(
	const Point &position,
	const Size &size):

	Control {position, size},
	_value {0},
	_minValue {-1000},
	_maxValue {1000},
	_delta {1} {

}


void eos::NumericControl::onPropertyChanged(
	void *property) {

	if (property == &_minValue)
		_value = eos::Math::max(_value, _minValue);
	else if (property == &_maxValue)
		_value = eos::Math::min(_value, _maxValue);
}



void eos::NumericControl::onMessage(
	FormMessage &message) {

	switch (message.id) {
		case FormMessageID::keyboard:
			switch (message.keyboard.id) {
				case KeyboardMessageID::up:
					increment();
					break;

				case KeyboardMessageID::down:
					decrement();
					break;

				case KeyboardMessageID::enter:
					break;
			}
			break;

		case FormMessageID::selector:
			break;
	}
}


void eos::NumericControl::onRender(
	Graphics *graphics) {

}


void eos::NumericControl::increment() {

	if ((_value + _delta)< _maxValue) {
		_value += _delta;
		onValueChanged();
	}
}


void eos::NumericControl::decrement() {

	if ((_value - _delta) > _minValue) {
		_value -= _delta;
		onValueChanged();
	}

}
