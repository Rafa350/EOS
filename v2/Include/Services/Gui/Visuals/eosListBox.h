#ifndef __eosListBox__
#define __eosListBox__


#include "eos.h"
#include "Services/Gui/Visuals/eosItemsControl.h"


namespace eos {

	class Panel;

	class ListBox: public ItemsControl {
		private:
			Panel *panel;

		public:
			void addItem();
			void addItems();
	};
}


#endif // __eosListBox__
