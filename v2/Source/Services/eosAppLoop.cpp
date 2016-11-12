#include "Services/eosAppLoop.hpp"


using namespace eos;


static const char *serviceName = "AppLoopService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio a la que pertany el servei.
///
AppLoopService::AppLoopService(
    Application *application):

    Service(application, serviceName, stackSize, priority),
	initialized(false) {
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void AppLoopService::initialize() {

	if (!initialized) {
		onSetup();
		initialized = true;
	}
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
/// \param task: Punter a la tasca.
///
void AppLoopService::run(
    Task *task) {

	initialize();

    while (true) {
        onRun();

#if configUSE_TIME_SLICING == 0
        Task::delay(100);
#endif
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio.
///
void AppLoopService::onSetup() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa l'execucio. Es crida continuament.
///
void AppLoopService::onRun() {

}

