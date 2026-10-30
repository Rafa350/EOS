module;

#include <charconv>


export module Eos.Services.Forms.Controls.Numeric;

import Eos.Math;
import Eos.Services.Forms;
import Eos.Services.Forms.Controls.TextBox;
import Eos.System.Graphics;
import Eos.Types;


export namespace eos {

	class NumericControl: public TextBoxControl {
		private:
			static constexpr Int32 _defMinValue = -1000;
			static constexpr Int32 _defMaxValue = 1000;
			static constexpr Int32 _defValue = 0;
			static constexpr Int32 _defDelta = 1;

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
	_value {_defValue},
	_minValue {_defMinValue},
	_maxValue {_defMaxValue},
	_delta {_defDelta} {
}


void NumericControl::onPropertyChanged(
	void *property) {

	// Comprova si ha canviar la propietat 'MinValue'
	//
	if (property == &_minValue)
		setValue(Math::max(_value, _minValue));

	// Comprova si ha canviar la propietat 'MaxValue'
	//
	else if (property == &_maxValue)
		setValue(Math::min(_value, _maxValue));

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


/// ---------------------------------------------------------------------------
/// @brief    Es crida quant canvia el valor.
///
void NumericControl::onValueChanged() {

	setText(_value);
}


/// ---------------------------------------------------------------------------
/// @brief    Es crida quant arriva un missatge.
/// @param    message: El missatge.
///
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


/// ---------------------------------------------------------------------------
/// @brief    Incrementa el valor.
///
void NumericControl::increment() {

	if ((_value + _delta)< _maxValue) {
		_value += _delta;
		onValueChanged();
	}
}


/// ---------------------------------------------------------------------------
/// @brief    Decrementa el valor.
///
void NumericControl::decrement() {

	if ((_value - _delta) > _minValue) {
		_value -= _delta;
		onValueChanged();
	}

}
