#include "HTL/htl.h"
#include "HTL/htlTick.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void htl::initialize() {

	tick::TickGenerator::pInst->initialize(
		1000000,  // Frequencia del timer a 1MHz
		1000);    // Divisor per generar els tiks cada 1ms
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
	uint32_t ticks) {

    tick::TickGenerator::pInst->wait(ticks);
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el tick ha expirar.
/// \param    ticks: El tick.
/// \return   true si ja ha expirat.
///
bool htl::hasTickExpired(
    uint32_t tick) {

    return static_cast<int>(tick - getTick()) <= 0;
}

