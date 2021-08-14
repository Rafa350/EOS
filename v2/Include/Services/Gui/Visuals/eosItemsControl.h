#ifndef __eosItemsControl__
#define __eosItemsControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class ItemsControl: public Control {
		private:
            Thickness _padding;
            Visual* _active;

		public:
			ItemsControl();

			void setPadding(const Thickness& value);
            void setActive(Visual* item);
			void addItem(Visual* item);

			inline const Thickness& getPadding() const { return _padding; }
	};
}


#endif // __eosItemsControl__
