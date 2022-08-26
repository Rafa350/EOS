#include "eos.h"
#include "appApplication.h"
#include "appLoopService.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

	_loopService = new MyAppLoopService(this);
}
