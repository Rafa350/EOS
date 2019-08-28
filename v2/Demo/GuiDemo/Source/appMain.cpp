#include "eos.h"
#include "eosAssert.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

    MyApplication *pApplication = new MyApplication();
    pApplication->run();
    delete pApplication;
}
