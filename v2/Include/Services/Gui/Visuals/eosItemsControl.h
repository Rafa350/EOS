#ifndef __eosItemsControl__
#define __eosItemsControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "Services/Gui/Visuals/eosControlItem.h"


namespace eos {

	class ItemsControl: public Control {
		private:
			typedef Vector<ControlItem*> ItemList;

		private:
			ItemList _items;
            Thickness _padding;
            ControlItem* _activeItem;

		protected:
			virtual void onItemAdded(ControlItem* item);
			virtual void onItemRemoved(ControlItem* item);
			virtual void onActiveItemChanged(ControlItem* item);

		public:
			ItemsControl();

			void addItem(ControlItem* item);
			void removeItem(ControlItem* item);

			void setPadding(const Thickness& value);
            void setActiveItem(ControlItem* item);

			inline const Thickness& getPadding() const { return _padding; }
	};
}


#endif // __eosItemsControl__
