module;

#include "eos.h"

export module htl.atomic;

namespace htl {

	export inline unsigned startAtomic() {
		unsigned pm =  __get_PRIMASK();
		__set_PRIMASK(1);
		return pm;
	}

	export inline void endAtomic(unsigned pm) {
		__set_PRIMASK(pm);
	}

}
