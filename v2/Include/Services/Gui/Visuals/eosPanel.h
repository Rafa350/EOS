#ifndef __eosPanel__
#define __eosPanel__


#include "eos.h"
#include "Services/Gui/Visuals/eosControl.h"


namespace eos {

	class RenderContext;

	class Panel: public Control {
		protected:
			void onRender(RenderContext* context) override;

		public:
			Panel();

			inline void addChild(Visual* visual) { addVisual(visual); }
	};
}


#endif // __eosPanel__
