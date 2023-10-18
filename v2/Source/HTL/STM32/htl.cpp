#include "HTL/htl.h"
#include "HTL/htlTick.h"


using namespace htl;



/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
///
void htl::initialize() {

	auto hTick = htl::tick::Tick::getHandler();

	hTick->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void htl::deinitialize() {

	auto hTick = htl::tick::Tick::getHandler();

	hTick->deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el numero de tick.
/// \return   El numero de tick.
///
uint32_t htl::getTick() {

	auto hTick = htl::tick::Tick::getHandler();

	return hTick->getTickCount();
}



/// ----------------------------------------------------------------------
/// \brief    Espera el nombre especificat de ticks.
/// \param    ticks: El nombre de ticks.
///
void htl::waitTicks(
	uint32_t ticks) {

	auto hTick = htl::tick::Tick::getHandler();

	uint32_t startTick = hTick->getTickCount();
	while (hTick->getTickCount() - startTick < ticks)
		continue;
}

