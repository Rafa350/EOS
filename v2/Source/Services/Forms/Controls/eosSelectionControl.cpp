module;


#include "eos.h"


export module Eos.Services.Forms.Controls.Selection;


import Eos.Services.Forms;
import Eos.System.Graphics;
import Eos.System.Graphics.Point;
impirt Eos.System.Graphics.Size;


export namespace eos {

	class SelectionControl: public Control {
		private:
			const char **_values;
			uint32_t _numValues;
			uint32_t _index;

		protected:
            void onMessage(FormMessage &message) override;
            void onRender(Graphics *graphics) override;

		public:
            SelectionControl(const Point &position, const Size &size);

            inline void setValues(const char **values, uint32_t numValues) {
            	_numValues = numValues;
            	setProperty(_values, values);
            }
            inline uint32_t getIndex() const {
            	return _index;
            }
            inline const char* getValue() const {
            	return _index < 0 ? nullptr : _values[_index];
            }
	};
}


eos::SelectionControl::SelectionControl(
	const Point &position,
	const Size &size):

	Control {position, size},
	_values {nullptr},
	_numValues {0},
	_index {(uint32_t)-1} {


}
