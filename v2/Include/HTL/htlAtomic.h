#pragma once


#include "HTL/htl.h"


namespace htl {

	inline unsigned startAtomic() {
		uint32_t pm =  __get_PRIMASK();
		__set_PRIMASK(1);
		return pm;
	}

	inline void endAtomic(uint32_t pm) {
		__set_PRIMASK(pm);
	}

}

