#ifndef __eosPanel__
#define __eosPanel__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class RenderContext;

	class Panel: public Visual {
		protected:
			void onRender(RenderContext &context) override;

		public:
			inline void addChild(Visual *pVisual) { addVisual(pVisual); }
	};
}


#endif // __eosPanel__
