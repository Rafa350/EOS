#include "eos.h"
#include "appApplication.h"

using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {
    
	auto *app = new MyApplication();
	app->run();
	delete app;
}

