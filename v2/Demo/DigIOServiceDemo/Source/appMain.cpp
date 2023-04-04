#include "eos.h"
#include "appApplication.h"
#include "HTL/PIC32/htlRegisters.h"

using namespace eos;
using namespace app;


uint32_t reg, a, b, c;

/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {

	ApplicationBase *app = new MyApplication();
	app->run();
	delete app;
}

