#include "eos.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

    MyApplication *app = new MyApplication();
    app->run();
    delete app;
}
