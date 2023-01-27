#include "eos.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

    MyApplication *application = new MyApplication();
    if (application) {
    	application->run();
    	delete application;
    }
}
