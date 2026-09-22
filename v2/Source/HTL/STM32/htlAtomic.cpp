module;


#include "HTL/htl.h"


export module Htl.Atomic;


export namespace htl {

	uint32_t startAtomic();
	void endAtomic(uint32_t pm);

}


/// ---------------------------------------------------------------------------
/// @brief    Inicia les operacions atomiques.
/// @return   L'estat de les interrupcions.
///
uint32_t htl::startAtomic() {

	uint32_t pm =  __get_PRIMASK();
	__set_PRIMASK(1);

	return pm;
}


/// ---------------------------------------------------------------------------
/// @brief    Finalitza les operacions atimiques.
/// @param    pm: Estat de les interrupcions.
///
void htl::endAtomic(
	uint32_t pm) {

	__set_PRIMASK(pm);
}
