#ifndef __eosVirtualKbd__
#define __eosVirtualKbd__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class renderContext;

	class VirtualKeyboard: public Panel {
		protected:
			void initializePanel() override;

		public:
			VirtualKeyboard();
	};
}


#endif //__eosVirtualKbd__
