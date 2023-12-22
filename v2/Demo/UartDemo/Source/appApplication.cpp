#include "eos.h"
#include "System/Core/eosTask.h"

#include "appApplication.h"
#include "appMainService.h"


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

	auto mainService = new MainService();
	addService(mainService, eos::Task::Priority::normal, 512, "MAINP");
}
