#ifndef __eosControl__
#define __eosControl__


#include "eos.h"
#include "Services/Gui/eosVisual.h"


namespace eos {

	class Control: public Visual {
		protected:
			virtual void initializeControl();
	};
}


#endif // __eosControl__