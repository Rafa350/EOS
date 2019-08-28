#include "eos.h"
#include "eosAssert.h"


/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

    // Enable ITM
	//
#ifdef xEOS_DEBUG
	ITM->LAR = 0xC5ACCE55;
    ITM->TCR |= 1 << ITM_TCR_ITMENA_Pos;
    ITM->TER = 1U;
    eosAssert(false);
#endif


	// Inicialitzacio del hardware
	//
	appInitialize();

	// Inicia l'aplicacio EOS
	//
	appMain();

	return 0;
}
