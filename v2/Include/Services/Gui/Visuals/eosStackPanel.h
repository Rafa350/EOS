#ifndef __eosStackPanel__
#define __eosStackPanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class RenderContext;

	class StackPanel: public Panel {
		private:
			Orientation _orientation;

		protected:
			Size measureOverride(const Size& availableSize) const override;
			Size arrangeOverride(const Size& finalSize) const override;

		public:
			StackPanel();

			void setOrientation(Orientation value);
			inline Orientation getOrientation() const { return _orientation; }
	};
}


#endif // __eosStackPanel__
