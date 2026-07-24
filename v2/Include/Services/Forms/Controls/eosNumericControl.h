#pragma once


#include "eos.h"
#include "Services/Forms/eosControl.h"


namespace eos {

	class Graphics;

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
