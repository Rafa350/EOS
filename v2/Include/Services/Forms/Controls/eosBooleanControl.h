#pragma once


#include "eos.h"
#include "Services/Forms/eosControl.h"


namespace eos {

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
