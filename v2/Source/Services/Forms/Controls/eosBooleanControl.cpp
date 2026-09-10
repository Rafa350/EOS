module;


#include "eos.h"


export module Eos.Services.Forms.Controls.Boolean;


import Eos.Services.Forms;
import Eos.System.Graphics.Canvas;
import Eos.System.Graphics.Point;
import Eos.System.Graphics.Size;


export namespace eos {

	class BooleanControl: public Control {
		private:
			bool _value;

		protected:
            void onMessage(FormMessage &message) override;
            void onRender(Graphics *graphics) override;

		public:
            BooleanControl(const Point &position, const Size &size);

			inline void setValue(bool value) {
				setProperty(_value, value);
			}

			inline bool getValue() const {
				return _value;
			}

	};
}

eos::BooleanControl::BooleanControl(
	const Point &position,
	const Size &size):

	Control {position, size} {

}
