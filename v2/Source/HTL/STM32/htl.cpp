#include "HTL/htl.h"
#include "HTL/htlTick.h"


using namespace htl;
using namespace htl::tick;



/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void htl::initialize() {

	TickGenerator::pInst->initialize(1000000);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void htl::deinitialize() {

	TickGenerator::pInst->deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de tick.
/// \return   El numero de tick.
///
uint32_t htl::getTick() {

	return TickGenerator::pInst->getTick();
}



/// ----------------------------------------------------------------------
/// \brief    Espera el nombre especificat de ticks.
/// \param    ticks: El nombre de ticks.
///
void htl::waitTicks(
	uint32_t ticks) {

    TickGenerator::pInst->wait(ticks);
}

