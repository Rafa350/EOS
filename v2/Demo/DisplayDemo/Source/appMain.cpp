#include "eos.h"
#include "System/eosApplication.h"
#include "appApplication.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void AppMain() {

	MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
