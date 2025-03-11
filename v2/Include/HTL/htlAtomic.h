#pragma once


#include "HTL/htl.h"


namespace htl {

	inline unsigned startAtomic() {
		unsigned pm =  __get_PRIMASK();
		__set_PRIMASK(1);
		return pm;
	}

	inline void endAtomic(unsigned pm) {
		__set_PRIMASK(pm);
	}

}

