#include "eos.h"
#include "HAL/halGPIO.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

	LEDS_Led1Initialize();

    MyApplication *application = new MyApplication();
    application->run();
    delete application;
}
