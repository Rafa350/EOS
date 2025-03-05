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
void MyApplication::onExecute() {

	auto mainService = new MainService();
	addService(mainService);

	while (true)
		eos::Task::delay(1000);
}
