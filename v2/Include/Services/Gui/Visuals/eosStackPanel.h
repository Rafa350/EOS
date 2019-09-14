#ifndef __eosStackPanel__
#define __eosStackPanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class RenderContext;

	class StackPanel: public Panel {
		private:
			Orientation orientation;
			Size desiredSize;

		public:
			StackPanel();

			void setOrientation(Orientation orientation);
			Orientation getOrientation() const { return orientation; }


			void measure(const Size &availableSize) override;

	};
}


#endif // __eosStackPanel__
