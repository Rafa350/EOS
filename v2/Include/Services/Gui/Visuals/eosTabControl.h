#ifndef __eosTabControl__
#define __eosTabControl__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "Services/Gui/Visuals/eosItemsControl.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class TabControlItem;

	class TabControl: public ItemsControl {
		private:
			TouchpadPressEventCallback<TabControl> _touchpadPressEventCallback;
		    Panel* _panel;
			Panel* _header;
			ContentControl* _content;

		private:
			Panel* createPanel();
			Panel* createHeaderPanel();
			void touchpadPressEventHandler(const TouchpadPressEventArgs& args);

		protected:
			void onItemAdded(ControlItem* item) override;
			void onItemRemoved(ControlItem* item) override;
			void onActiveItemChanged(ControlItem* item) override;

		public:
			TabControl();
	};
}


#endif // __eosTabControl__
