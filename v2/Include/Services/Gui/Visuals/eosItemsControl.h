#ifndef __eosItemsControl__
#define __eosItemsControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ItemsControl: public Control {

		public:
			ItemsControl();

			void addItem(Visual *pNewItem);
	};
}


#endif // __eosItemsControl__
