#pragma once


#include "eos.h"
#include "Services/Forms/eosControl.h"


namespace eos {

	class Graphics;

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
