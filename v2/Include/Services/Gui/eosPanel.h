#ifndef __eosPanel__
#define __eosPanel__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Panel: public Visual {
		public:
			inline void addChild(Visual *visual) { addVisual(visual); }
	};
}


#endif // __eosPanel__