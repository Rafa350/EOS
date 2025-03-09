module;


#include "HTL/htl.h"


export module htl.atomic;


export namespace htl {

	unsigned startAtomic();
	void endAtomic(unsigned pm);

}


/// ---------------------------------------------------------------------------
/// \brief    Inicia un bloc d'operacions atomiques.
/// \return   El estat intern.
///
unsigned htl::startAtomic() {
	unsigned pm =  __get_PRIMASK();
	__set_PRIMASK(1);
	return pm;
}


/// ---------------------------------------------------------------------------
/// \brief    Finalitza un bloc d'operacions atomiques.
/// \param    pm: El estat intern obtingut de 'startAtomic'
///
void htl::endAtomic(unsigned pm) {
	__set_PRIMASK(pm);
}
