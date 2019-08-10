#include "eos.h"
#include "Services/Gui/eosGuiTouchPad.h"
#include "appApplication.h"
#include "appLedService.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
MyApplication::MyApplication():

	Application() {

	ledService = new LedService(this);
	displayService = new DisplayService(this);

	touchPadService = new GuiTouchPadService(this);
	touchPadService->setNotifyEvent<MyApplication>(this, &MyApplication::touchPadNotification);
}


/// ----------------------------------------------------------------------
/// \brief Reb les notificacions del touch pad
/// \para, args: Parametres de la notificacio.
///
void MyApplication::touchPadNotification(
	eos::TouchPadEventArgs *args) {

}
