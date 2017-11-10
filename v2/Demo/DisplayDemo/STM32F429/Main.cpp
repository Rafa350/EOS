extern void AppMain();
extern void InitializeHardware();

#include "stm32f429i_discovery_sdram.h"

/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main(void) {

	// Inicialitzacio del hardware
	//
	InitializeHardware();

	// Inicia l'aplicacio EOS
	//
	AppMain();

	return 0;
}
