module;

#include <charconv>


export module Eos.Services.Forms.Controls.Numeric;

import Eos.Math;
import Eos.Services.Forms;
import Eos.Services.Forms.Controls.TextBox;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


export namespace eos {

	class NumericControl: public TextBoxControl {
		private:
			Int32 _value;
			Int32 _minValue;
			Int32 _maxValue;
			Int32 _delta;

		protected:
			void setText(Int32 value);
            void onPropertyChanged(void *property) override;
            void onMessage(FormMessage &message) override;
            virtual void onValueChanged();

		public:
            NumericControl(const Point &position, const Size &size);

			inline void setValue(Int32 value) { setProperty(_value, value); }
			inline void setMinValue(Int32 value) { setProperty(_minValue, value); }
			inline void setMaxValue(Int32 value) { setProperty(_maxValue, value); }
			inline void setDelta(Int32 value) { setProperty(_delta, value); }

			inline Int32 getValue() const { return _value;	}

			void increment();
            void decrement();
	};
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    position: Posicio del control.
/// @param    size: Tamany del control.
///
NumericControl::NumericControl(
	const Point &position,
	const Size &size):

	TextBoxControl {position, size, nullptr},
	_value {0},
	_minValue {-1000},
	_maxValue {1000},
	_delta {1} {
}


void NumericControl::onPropertyChanged(
	void *property) {

	// Comprova si ha canviar la propietat 'MinValue'
	//
	if (property == &_minValue) {
		setValue(Math::max(_value, _minValue));

	// Comprova si ha canviar la propietat 'MaxValue'
	//
	else if (property == &_maxValue) {
		setValue(Math::min(_value, _maxValue))

	// Comprova si ha canviar la propietat 'Value'
	//
	else if (property == &_value)
		onValueChanged();

	// Continua amb les comprovacions
	//
    else
		TextBoxControl::onPropertyChanged(property);
}


void NumericControl::setText(
	Int32 value) {

	static char buffer[10];

	auto r = std::to_chars(buffer, buffer + sizeof(buffer), value, 10);
	if (r.ec != std::errc())
		TextBoxControl::setText(buffer);
}


void NumericControl::onValueChanged() {

	TextBoxControl::setText("12345");
	//setText(_value);
}


void NumericControl::onMessage(
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


void NumericControl::increment() {

	if ((_value + _delta)< _maxValue) {
		_value += _delta;
		onValueChanged();
	}
}


void NumericControl::decrement() {

	if ((_value - _delta) > _minValue) {
		_value -= _delta;
		onValueChanged();
	}

}
