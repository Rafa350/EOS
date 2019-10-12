#ifndef __eosProgressBar__
#define __eosProgressBar__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/Graphics/eosColor.h"


namespace eos {

	class RenderContext;

	class ProgressBar: public Control {
		private:
			Color backgroundColor;
			Color borderColor;
			Color barColor;
			int minValue;
			int maxValue;
			int value;

		protected:
			void onRender(RenderContext *context) override;
			Size measureOverride(const Size &availableSize) const override;

		public:
			ProgressBar();

			void setBackgroundColor(const Color &value);
			void setBarColor(const Color &value);
			void setBorderColor(const Color &value);

			void setMaxValue(int value);
			void setMinValue(int value);
			void setValue(int value);

			inline int getMaxValue() const { return maxValue; }
			inline int getMinValue() const { return minValue; }
			inline int getValue() const { return value; }
	};
}


#endif // __eosProgressBar__
