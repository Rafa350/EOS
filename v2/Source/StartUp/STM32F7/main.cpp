#include "eos.h"
#include "System/eosDebug.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

    // Enable Debug
	//
#ifdef EOS_DEBUG
	//Debug::initialize();
	//while (true)
	//	Debug::print("Hola");
#endif

	// Inicialitzacio del hardware
	//
	appInitialize();

	// Inicia l'aplicacio EOS
	//
	appMain();

	return 0;
}
