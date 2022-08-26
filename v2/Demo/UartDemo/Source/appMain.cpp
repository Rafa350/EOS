#include "eos.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


// -----------------------------------------------------------------------
// Conexions cable FTDI a conector d'expansio arduino.
//
//    FTDI                AINO
//	  ----------------    ----
//    1 - BLACK  - GND    GND
//    4 - ORANGE - TX     D0
//    5 - YELLOW - RX     D1
//
// -----------------------------------------------------------------------


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {

	Application *app = new MyApplication();
    app->run();
    delete app;
}
