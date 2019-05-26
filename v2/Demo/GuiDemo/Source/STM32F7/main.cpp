#include "eos.h"


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

	// Inicialitzacio del hardware
	//
	AppInitialize();

	// Inicia l'aplicacio EOS
	//
	AppMain();

	return 0;
}
