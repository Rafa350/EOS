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
#ifdef USE_TOUCHPAD
			TouchpadPressEventCallback<TabControl> _touchpadPressEventCallback;
#endif
		    Panel* _panel;
			Panel* _header;
			ContentControl* _content;

		private:
			Panel* createPanel();
			Panel* createHeaderPanel();
#ifdef USE_TOUCHPAD
			void touchpadPressEventHandler(const TouchpadPressEventArgs& args);
#endif

		protected:
			void onItemAdded(ControlItem* item) override;
			void onItemRemoved(ControlItem* item) override;
			void onActiveItemChanged(ControlItem* item) override;

		public:
			TabControl();
	};
}


#endif // __eosTabControl__
