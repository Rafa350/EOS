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
Tick htl::getTick() {

	return TickGenerator::pInst->getTick();
}



/// ----------------------------------------------------------------------
/// \brief    Espera el nombre especificat de ticks.
/// \param    ticks: El nombre de ticks.
///
void htl::waitTicks(
	Tick ticks) {

    TickGenerator::pInst->wait(ticks);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tick ha expirar.
/// \param    ticks: El tick.
/// \return   true si ja ha expirat.
///
bool htl::hasTickExpired(
    Tick tick) {

    return static_cast<int>(tick - getTick()) <= 0;
}

