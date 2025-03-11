#include "HTL/htl.h"
#include "HTL/htlTick.h"

//import htl.tick;


using namespace htl;



/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void htl::initialize() {

	tick::TickGenerator::pInst->initialize(1000000);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void htl::deinitialize() {

	tick::TickGenerator::pInst->deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de tick.
/// \return   El numero de tick.
///
unsigned htl::getTick() {

	return tick::TickGenerator::pInst->getTick();
}



/// ----------------------------------------------------------------------
/// \brief    Espera el nombre especificat de ticks.
/// \param    ticks: El nombre de ticks.
///
void htl::waitTicks(
	unsigned ticks) {

    tick::TickGenerator::pInst->wait(ticks);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tick ha expirar.
/// \param    ticks: El tick.
/// \return   true si ja ha expirat.
///
bool htl::hasTickExpired(
    unsigned tick) {

    return static_cast<int>(tick - htl::getTick()) <= 0;
}

