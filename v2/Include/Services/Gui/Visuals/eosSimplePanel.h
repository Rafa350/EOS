#ifndef __eosSimplePanel__
#define __eosSimplePanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosPanel.h"


namespace eos {

	class SimplePanel: public Panel {
		protected:
			void onRender(RenderContext &context) override;
	};
}


#endif // __eosSimplePanel__
