#ifndef __eosTemplate__
#define __eosTemplate__


#include "eos.h"


namespace eos {

	class ITemplate {
		public:
			virtual void applyTemplate() = 0;
	};

}


#endif
