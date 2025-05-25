#include "eos.h"


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

	// Inicialitzacio del hardware
	//
	appInitialize();

	// Inicia l'aplicacio EOS
	//
	appMain();

	return 0;
}
