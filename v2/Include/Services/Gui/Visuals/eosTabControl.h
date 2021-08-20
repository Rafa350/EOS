#ifndef __eosTabControl__
#define __eosTabControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "Services/Gui/Visuals/eosItemsControl.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "System/Collections/eosVector.h"


namespace eos {

	class TabControlItem;

	class TabControl: public ItemsControl {
		private:
			Panel* _header;
			ContentControl* _content;

		private:
			Panel* createHeaderPanel();

		protected:
			void onItemAdded(ControlItem* item) override;
			void onItemRemoved(ControlItem* item) override;
			void onActiveItemChanged(ControlItem* item) override;

		public:
			TabControl();
	};
}


#endif // __eosTabControl__
