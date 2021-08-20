#ifndef __eosTabControlItem__
#define __eosTabControlItem__


#include "eos.h"
#include "Services/Gui/eosVisual.h"
#include "Services/Gui/Visuals/eosControlItem.h"


namespace eos {

	class TabControlItem: public ControlItem {
		private:
			Visual* _header;
			Visual* _content;

		public:
			TabControlItem(Visual* header, Visual* _content);

			Visual* getHeader() const { return _header; }
			Visual* getContent() const { return _content; }
	};
}



#endif // __eosTabControlItem__
