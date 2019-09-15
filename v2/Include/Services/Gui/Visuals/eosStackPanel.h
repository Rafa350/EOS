#ifndef __eosStackPanel__
#define __eosStackPanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class RenderContext;

	class StackPanel: public Panel {
		private:
			Orientation orientation;

		protected:
			Size measureCore(const Size &availableSize) const override;

		public:
			StackPanel();

			void setOrientation(Orientation orientation);
			Orientation getOrientation() const { return orientation; }
	};
}


#endif // __eosStackPanel__
