module;


#include "eos.h"


export module Eos.Services.Forms.Controls.Numeric;


import Eos.Math;
import Eos.Services.Forms;
import Eos.System.Graphics;


export namespace eos {

	class NumericControl: public Control {
		private:
			int32_t _value;
			int32_t _minValue;
			int32_t _maxValue;
			int32_t _delta;

		protected:
            void onPropertyChanged(void *property) override;
            void onMessage(FormMessage &message) override;
            void onRender(Graphics *graphics) override;
            virtual void onValueChanged();

		public:
            NumericControl(const Point &position, const Size &size);

			inline void setValue(int32_t value) {
				setProperty(_value, value);
			}
			inline void setMinValue(int32_t value) {
				setProperty(_minValue, value);
			}
			inline void setMaxValue(int32_t value) {
				setProperty(_maxValue, value);
			}
			inline void setDelta(int32_t value) {
				setProperty(_delta, value);
			}

			inline int32_t getValue() const {
				return _value;
			}

			void increment();
            void decrement();
	};
}


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
