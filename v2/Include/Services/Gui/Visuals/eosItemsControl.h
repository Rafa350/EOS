#ifndef __eosItemsControl__
#define __eosItemsControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"
#include "System/Collections/eosIntrusiveList.h"


namespace eos {

    class ControlItem;
    using ControlItemList = IndirectIntrusiveForwardList<ControlItem, 0>;
    using ControlItemListNode = IndirectIntrusiveForwardListNode<ControlItem, 0>;

    class ControlItem: public ControlItemListNode {
    };

    class ItemsControl: public Control {
		private:
			ControlItemList _items;
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
