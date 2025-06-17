#include "eos.h"
#include "appApplication.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

	auto app = new MyApplication();
    app->run();
}
