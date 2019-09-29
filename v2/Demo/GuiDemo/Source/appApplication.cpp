#include "eos.h"
#include "eosAssert.h"
#include "Services/eosGuiService.h"
#include "appApplication.h"
#include "appLedService.h"


using namespace eos;
using namespace app;


///-----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication():

	Application() {

	ledService = new LedService(this);
	guiService = new GuiService(this);
}
