#ifndef __eosMenu__
#define __eosMenu__


#include "eos.h"
#include "Services/Gui/Visuals/eosItemsControl.h"


namespace eos {

	class Size;

	class Menu: public ItemsControl {

		protected:
			Size measureOverride(const Size &availableSize) const override;
			Size arrangeOverride(const Size &finalSize) const override;
	};
}


#endif // __eosMenu__
