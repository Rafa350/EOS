module;

#include "HTL/htl.h"


export module Htl.Atomic;


export namespace htl {

	uint32_t startAtomic();
	void endAtomic(uint32_t pm);

}


uint32_t htl::startAtomic() {

	uint32_t pm =  __get_PRIMASK();
	__set_PRIMASK(1);

	return pm;
}


void htl::endAtomic(
	uint32_t pm) {

	__set_PRIMASK(pm);
}
