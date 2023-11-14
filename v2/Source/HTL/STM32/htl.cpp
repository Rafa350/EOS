#include "HTL/htl.h"
#include "HTL/htlTick.h"


using namespace htl;



/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void htl::initialize() {

	auto hTick = tick::TickGenerator::getHandler();
	hTick->initialize(1000000);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void htl::deinitialize() {

	auto hTick = tick::TickGenerator::getHandler();
	hTick->deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de tick.
/// \return   El numero de tick.
///
uint32_t htl::getTick() {

	auto hTick = tick::TickGenerator::getHandler();
	return hTick->getTickCount();
}



/// ----------------------------------------------------------------------
/// \brief    Espera el nombre especificat de ticks.
/// \param    ticks: El nombre de ticks.
///
void htl::waitTicks(
	uint32_t ticks) {

	auto hTick = tick::TickGenerator::getHandler();
	hTick->wait(ticks);
}

