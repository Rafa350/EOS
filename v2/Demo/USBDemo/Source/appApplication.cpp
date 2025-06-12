#include "eos.h"
#include "System/Core/eosTask.h"
#include "Services/eosLedService.h"

#include "appApplication.h"


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


	auto ledService = new eos::LedService(LED1_Instance, nullptr);
	addService(ledService);

	//auto mainService = new MainService();
	//addService(mainService);

	while (true)
		eos::Task::delay(1000);
}
